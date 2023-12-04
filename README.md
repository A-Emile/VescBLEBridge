# VescBLEBridge

![A picture of a cat](/assets/_MG_6227.JPG)

VescBLEBridge is a project that lets you add Bluetooth connectivity to your Vesc Controller for only 3€. It utilizes the ESP32 C3 microcontroller as a cost-effective BLE (Bluetooth Low Energy) module. It allows seamless communication between your Vesc controllers and the Vesc Tool App.

## Features

- **Compact Design:** The ESP32 C3's small form factor makes it an ideal choice for applications where space is a constraint.

- **Cost-Effective:** Utilizing the ESP32 C3 as a BLE module provides a budget-friendly alternative to an NRF module for integrating Bluetooth connectivity into Vesc controllers.

- **User-Friendly:** VescBLEBridge is designed to be easy to use, with straightforward setup and configuration. Prebuild versions with flashed firmware and soldered connectors are also planned.

## Getting Started

### Hardware Setup:
**What you need:**
- [ESP32 C3 Dev Board](https://de.aliexpress.com/item/1005005967641936.html)
- Some Wires
- Fitting connector for you Vesc Uart port (Most likely JST-PH2.0)
- USB C Cable

Connect the ESP32 C3 to your Vesc controller following the table below.

    | ESP32 C3    | VESC        |
    | ----------- | ----------- |
    | 5V          | 5V          |
    | GND         | GND         |
    | 20          | RX          |
    | 21          | TX          |

If it doesnt work you can try swapping rx and tx pins cause they are swapped on some vesc controllers.

### Flashing Firmware:
To flash the firmware to the esp you need the following prerequisites:
- [Visual Studio Code](https://code.visualstudio.com/)
- [PlattformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)  extension for VSCode

Once you have VSCode and its PlattformIO extension installed, you need to open this git repo in VSCode. Then connect the esp32 to you computer and hit upload.

If you have trouble you can read the official [PlattformIO docs](https://docs.platformio.org/en/latest/integration/ide/vscode.html#ide-vscode)

## Contributing

We welcome contributions from the community! If you have ideas for improvements, feature requests, or bug reports, please open an issue or submit a pull request.

## Support

For any questions or issues, feel free open an issue.

Happy riding!
