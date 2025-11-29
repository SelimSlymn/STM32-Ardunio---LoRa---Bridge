# 📡 STM32 & Arduino LoRa Wireless Communication Bridge

This project demonstrates a robust wireless data transmission system using **LoRa (Ebyte E22)** modules, bridging an **Arduino**-based transmitter and an **STM32F411RE**-based receiver.

The system captures analog joystick data, transmits it wirelessly via UART over LoRa, and displays the received data on a PC terminal through the STM32 microcontroller. This project highlights embedded systems concepts such as **UART communication**, **GPIO control**, **Logic Level Shifting**, and **Wireless Telemetry**.

---

## 🚀 Features

* **Transmitter (Tx):** Arduino reads analog joystick values, maps them to a drone protocol (1000-2000), and sends packets (e.g., `T1500`).
* **Wireless Link:** Long-range communication using 433MHz/900MHz LoRa modules (UART Interface).
* **Receiver (Rx):** STM32F411 captures the data packet and bridges it to the PC via USB (Virtual COM Port).
* **Visual Feedback:**
    * **Heartbeat LED:** STM32 onboard LED (PA5) toggles with every received packet.
    * **Activity LED:** External LED on the LoRa AUX pin indicates internal module status.

---

## 🛠️ Hardware Requirements

1.  **STM32 Nucleo-F411RE** Development Board
2.  **Arduino Uno/Nano** (Transmitter MCU)
3.  **2x Ebyte E22 LoRa Modules** (UART-based)
4.  **Analog Joystick Module**
5.  **Logic Level Converter Components:**
    * **1x 3.3V Zener Diode:** Protects the LoRa RX pin from Arduino's 5V logic.
    * **1x 4.7kΩ Resistor:** Used in the voltage divider/protection circuit.
6.  **Indicators:**
    * 1x LED (Green/Red) connected to STM32 LoRa AUX pin.

---

## ⚡ Circuit & Engineering Notes

This project implements specific hardware design choices for stability and safety:

* **Logic Level Shifting:** Since Arduino operates at 5V and the LoRa module is 3.3V logic tolerant, a **3.3V Zener Diode** is placed on the Arduino TX line to clamp the voltage, protecting the LoRa module.
* **Thermal Stability:** A **4.7kΩ resistor** is used (instead of the standard 2.2kΩ) in the signal path. This higher resistance effectively limits the current, preventing the LoRa module from heating up during continuous high-speed transmission.
* **AUX Indication:** An external LED is connected to the LoRa AUX pin on the STM32 side. This provides physical visual feedback on the module's internal state (Transmission/Reception busy state).

---

## 🔌 Wiring Diagram / Pinout

### 1. Transmitter Side (Arduino)

| Arduino Pin | LoRa Pin | Component | Description |
| :--- | :--- | :--- | :--- |
| **5V** | VCC | - | Power Supply |
| **GND** | GND, M0, M1 | - | Common Ground & Mode Selection |
| **Pin 3** | RX | - | Arduino TX -> LoRa RX (SoftwareSerial) |
| **Pin 2** | TX | 4.7kΩ + Zener | Arduino RX -> LoRa TX (Protected) |
| **A0** | - | Joystick VRx | Throttle/Joystick Signal |

### 2. Receiver Side (STM32 F411RE)

| STM32 Pin | LoRa Pin | Description |
| :--- | :--- | :--- |
| **5V** | VCC | Module Power Supply |
| **GND** | GND, M0, M1 | Common Ground & Normal Mode |
| **PA9 (TX)** | RX | STM32 USART1 TX |
| **PA10 (RX)** | TX | STM32 USART1 RX |
| **PA2 (TX)** | - | PC Communication (USART2 - USB) |
| **PA3 (RX)** | - | PC Communication (USART2 - USB) |
| **PA5** | - | Onboard Status LED (Green) |