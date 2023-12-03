#include <Arduino.h>
#include <NimBLEDevice.h>

int MTU_SIZE = 128;
int PACKET_SIZE = MTU_SIZE - 3;
NimBLEServer *pServer = nullptr;
NimBLEService *pServiceVesc = nullptr;
NimBLEService *pServiceRescue = nullptr;
NimBLECharacteristic *pCharacteristicVescTx = nullptr;
NimBLECharacteristic *pCharacteristicVescRx = nullptr;

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define VESC_SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define VESC_CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define VESC_CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

/**  None of these are required as they will be handled by the library with defaults. **
 **                       Remove as you see fit for your needs                        */
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(NimBLEServer *pServer, ble_gap_conn_desc *desc)
  {
    ESP_LOGI(LOG_TAG_BLESERVER, "Client connected: %s", NimBLEAddress(desc->peer_ota_addr).toString().c_str());
    ESP_LOGI(LOG_TAG_BLESERVER, "Multi-connect support: start advertising");
    deviceConnected = true;
    NimBLEDevice::startAdvertising();
  }

  void onDisconnect(NimBLEServer *pServer)
  {
    ESP_LOGI(LOG_TAG_BLESERVER, "Client disconnected - start advertising");
    deviceConnected = false;
    NimBLEDevice::startAdvertising();
  }

  void onMTUChange(uint16_t MTU, ble_gap_conn_desc *desc)
  {
    ESP_LOGI(LOG_TAG_BLESERVER, "MTU changed - new size %d, peer %s", MTU, NimBLEAddress(desc->peer_ota_addr).toString().c_str());
    MTU_SIZE = MTU;
    PACKET_SIZE = MTU_SIZE - 3;
  }
};

char tmpbuf[1024]; // CAUTION: always use a global buffer, local buffer will flood the stack

void dumpBuffer(std::string header, std::string buffer)
{
  if (esp_log_level_get("BleServer") < ESP_LOG_DEBUG)
  {
    return;
  }
  int length = snprintf(tmpbuf, 50, "%s : len = %d / ", header.c_str(), buffer.length());
  for (char i : buffer)
  {
    length += snprintf(tmpbuf + length, 1024 - length, "%02x ", i);
  }
  ESP_LOGD(LOG_TAG_BLESERVER, "%s", tmpbuf);
}

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    ESP_LOGD(LOG_TAG_BLESERVER, "onWrite to characteristics: %s", pCharacteristic->getUUID().toString().c_str());
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0)
    {
      if (pCharacteristic->getUUID().equals(pCharacteristicVescRx->getUUID()))
      {
        dumpBuffer("BLE/UART => VESC: ", rxValue);
        for (int i = 0; i < rxValue.length(); i++)
        {
          Serial1.write(rxValue[i]);
        }
      }
    }
  }
};

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 20, 21); // RX=20, TX=21

  // Create the BLE Device
  NimBLEDevice::init("VescBLEBridge");
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);

  // Create the BLE Server
  pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  auto pSecurity = new NimBLESecurity();
  pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

  // Create the BLE Service
  BLEService *pService = pServer->createService(VESC_SERVICE_UUID);

  // Create a BLE TX Characteristic
  pCharacteristicVescTx = pService->createCharacteristic(
      VESC_CHARACTERISTIC_UUID_TX,
      NIMBLE_PROPERTY::NOTIFY |
          NIMBLE_PROPERTY::READ);

  // Create a BLE RX Characteristic
  pCharacteristicVescRx = pService->createCharacteristic(
      VESC_CHARACTERISTIC_UUID_RX,
      NIMBLE_PROPERTY::WRITE |
          NIMBLE_PROPERTY::WRITE_NR);

  pCharacteristicVescRx->setCallbacks(new MyCallbacks());

  // Start the VESC service
  pService->start();

  // Start advertising
  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(VESC_SERVICE_UUID);
  //    pAdvertising->setAppearance(0x00);
  //    pAdvertising->setScanResponse(true);
  //    pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter

  pAdvertising->start();
  ESP_LOGI(LOG_TAG_BLESERVER, "waiting a client connection to notify...");
}

std::string vescBuffer;
std::string updateBuffer;

void loop()
{

  if (Serial1.available())
  {
    int oneByte;
    while (Serial1.available())
    {
      oneByte = Serial1.read();
      vescBuffer.push_back(oneByte);
    }

    if (deviceConnected)
    {
      while (vescBuffer.length() > 0)
      {
        if (vescBuffer.length() > PACKET_SIZE)
        {
          dumpBuffer("VESC => BLE/UART", vescBuffer.substr(0, PACKET_SIZE));
          pCharacteristicVescTx->setValue(vescBuffer.substr(0, PACKET_SIZE));
          vescBuffer = vescBuffer.substr(PACKET_SIZE);
        }
        else
        {
          dumpBuffer("VESC => BLE/UART", vescBuffer);
          pCharacteristicVescTx->setValue(vescBuffer);
          vescBuffer.clear();
        }
        pCharacteristicVescTx->notify();
        delay(5); // bluetooth stack will go into congestion, if too many packets are sent
      }
    }
  }

  // disconnecting
  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);                  // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    ESP_LOGI(LOG_TAG_BLESERVER, "start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected)
  {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}