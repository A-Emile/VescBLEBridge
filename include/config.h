#pragma once

// ============================================================================
//  VescBLEBridge - user configuration
//
//  Everything you might want to tweak lives in this file. Edit the values
//  below, then re-flash the firmware. main.cpp reads from here.
// ============================================================================

// ---------------------------------------------------------------------------
//  BLE device
// ---------------------------------------------------------------------------

// Name shown when scanning for Bluetooth devices (and in the VESC Tool app).
#define BLE_DEVICE_NAME "Iphone 10"

// Transmit power. One of ESP_PWR_LVL_N24 ... ESP_PWR_LVL_P9 (P9 = maximum).
#define BLE_TX_POWER ESP_PWR_LVL_P9

// Default MTU size. Negotiated higher with the client on connect if supported.
#define DEFAULT_MTU_SIZE 128

// ---------------------------------------------------------------------------
//  UART (link to the VESC)
// ---------------------------------------------------------------------------

#define VESC_UART_BAUD 115200

// UART pins. Board-specific defaults below; override if your wiring differs.
#if defined(ARDUINO_SEEED_XIAO_ESP32C6)
  #define VESC_RX_PIN D10
  #define VESC_TX_PIN D9
#else
  // Original ESP32-C3 pins.
  #define VESC_RX_PIN 20
  #define VESC_TX_PIN 21
#endif

// ---------------------------------------------------------------------------
//  BLE service / characteristic UUIDs
//
//  These are the Nordic UART Service UUIDs the VESC Tool app expects, so you
//  normally should NOT change them. Generate new ones at
//  https://www.uuidgenerator.net/ only if you know what you are doing.
// ---------------------------------------------------------------------------

#define VESC_SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define VESC_CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define VESC_CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// ---------------------------------------------------------------------------
//  Optional: BLE security (passkey / "password" pairing)
//
//  By default anyone in range can connect to the bridge. Uncomment the line
//  below to require pairing with a fixed 6-digit passkey: the client (e.g.
//  your phone) is prompted for BLE_SECURITY_PASSKEY when it first connects,
//  and the bond is remembered afterwards.
//
//  Note: the connecting app must support BLE passkey entry.
// ---------------------------------------------------------------------------

//#define ENABLE_BLE_SECURITY

// The 6-digit passkey (000000 - 999999) required when ENABLE_BLE_SECURITY is set.
#define BLE_SECURITY_PASSKEY 123456
