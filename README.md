# VescBLEBridge

![A picture of a cat](/assets/_MG_6227.JPG)

VescBLEBridge is a project that lets you add Bluetooth connectivity to your Vesc Controller for only 3€. It utilizes cheap, readily available microcontrollers like the ESP32-C3 and ESP32-C6 as cost-effective BLE (Bluetooth Low Energy) modules. It allows seamless communication between your VESC controllers and the official Vesc Tool App.

## Features

- **Compact Design:** The small form factor of ESP32 dev boards makes them an ideal choice for applications where space is a constraint (skateboards, e-bikes, e-SUPs).
- **Cost-Effective:** Utilizing an ESP32 as a BLE module provides a budget-friendly alternative to an NRF module for integrating Bluetooth connectivity.
- **Multi-Board Support:** Fully supports both the generic ESP32-C3 and the ultra-compact Seeed Studio XIAO ESP32-C6 out of the box.
- **User-Friendly:** Designed to be easy to use with straightforward setup and configuration via PlatformIO. 

## Getting Started

### Hardware Setup
**What you need:**
- An ESP32 Dev Board (e.g., [ESP32-C3](https://de.aliexpress.com/item/1005005967641936.html) or Seeed XIAO ESP32-C6)
- Some wires
- Fitting connector for your VESC UART port (Most likely JST-PH2.0)
- USB-C Cable

Connect the ESP32 to your VESC controller following the table below based on which board you are using. *(Remember: TX goes to RX, and RX goes to TX!)*

| VESC | ESP32-C3 (Generic) | ESP32-C6 (Seeed XIAO) |
| :--- | :--- | :--- |
| **5V** | 5V | 5V |
| **GND** | GND | GND |
| **RX** | TX (Pin 21) | TX (Pin D9) |
| **TX** | RX (Pin 20) | RX (Pin D10) |

*Note: If it doesn't work, try swapping the RX and TX pins, as the labeling convention can vary on some VESC controllers.*

### Flashing Firmware
To flash the firmware to the ESP, you need the following prerequisites:
- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension for VSCode

Once you have VSCode and its PlatformIO extension installed:
1. Open this git repo folder in VSCode. 
2. Connect the ESP32 to your computer via USB.
3. PlatformIO is configured with multiple environments. Select your target board (`esp32-c3-devkitm-1` or `seeed_xiao_esp32c6`) from the project tasks menu.
4. Hit **Upload**.

If you have trouble, you can read the official [PlatformIO docs](https://docs.platformio.org/en/latest/integration/ide/vscode.html#ide-vscode).

## Contributing

We welcome contributions from the community! If you have ideas for improvements, feature requests, or bug reports, please open an issue or submit a pull request.

## Support

For any questions or issues, feel free to open an issue.

Happy riding!