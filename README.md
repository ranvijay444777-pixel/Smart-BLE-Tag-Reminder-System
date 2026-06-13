# Smart BLE Tag Reminder System

An IoT-based asset tracking and reminder system built using ESP32 and Bluetooth Low Energy (BLE) technology. The system continuously monitors BLE tags attached to important belongings and alerts users when an item is left behind.

---

## System Overview

The project uses ESP32 as a BLE scanner and HM-10 modules as custom BLE tags. By analyzing RSSI (Received Signal Strength Indicator) values, the system estimates the proximity of tagged objects and generates alerts whenever required items are detected without the designated pivot item.

---
## Key Features

- Real-time BLE device scanning
- RSSI-based proximity estimation
- HM-10 BLE tag integration
- ESP32-based control logic
- Audio alerts using buzzer
- Visual status indication using LEDs
- Configurable distance threshold
- Support for multiple tagged items

---

## Hardware Components

| Component | Purpose |
|------------|----------|
| ESP32 DevKit V1 | Main controller |
| HM-10 BLE Module | BLE tag |
| Buzzer | Audio alert |
| Red LED | Alert indication |
| Green LED | Status indication |
| Resistors | Current limiting |
| Breadboard & Jumper Wires | Prototyping |

---

## Working Principle

1. ESP32 continuously scans nearby BLE devices.
2. RSSI values are collected for each detected BLE tag.
3. Average RSSI is computed to improve stability.
4. Presence of the Pivot Tag is verified.
5. Required Tags are checked.
6. Alert logic determines system status.

### Normal State

- Pivot Tag detected
- Required Tag detected

Result:

- Green LED ON
- Red LED OFF
- No alarm

### Forgotten Item State

- Pivot Tag missing
- Required Tag detected

Result:

- Red LED ON
- Buzzer activated

### All Items Removed Together

- Pivot Tag missing
- Required Tag missing

Result:

- No alarm triggered

---

## Pin Connections

| ESP32 Pin | Component |
|------------|-----------|
| GPIO 5 | Buzzer |
| GPIO 22 | Green LED |
| GPIO 23 | Red LED |

---

## Software 

- Arduino IDE
- ESP32 BLE Library
- C++
- Bluetooth Low Energy (BLE)

---

## Applications

- Student item reminder system
- Smart inventory monitoring
- Asset tracking
- Travel luggage monitoring
- Workplace equipment tracking
- Elderly assistance systems

---

## Repository Structure

```text
├── README.md
├── LICENSE
├── code.cpp
├── Project_Report.pdf
├── Flow Chart.png
└── Pin Diagram.png
```

---

