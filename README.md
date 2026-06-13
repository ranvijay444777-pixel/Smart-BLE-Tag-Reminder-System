# Smart BLE Tag Reminder System

A Bluetooth Low Energy (BLE) based reminder system built using ESP32 and HM-10 modules.

## Features

- Detects BLE tags attached to personal items
- Uses RSSI-based proximity estimation
- Alerts users when important items are left behind
- Visual indication through LEDs
- Audio alerts using buzzer

## Hardware

- ESP32 DevKit V1
- HM-10 BLE Modules
- LEDs
- Buzzer
- Resistors

## Working Principle

The ESP32 continuously scans BLE advertisements from HM-10 tags.

A pivot tag is attached to an important item (e.g. backpack).

If the pivot tag disappears while required tags remain detected, the system triggers alerts indicating a potentially forgotten item.

## Technologies

- ESP32
- Arduino IDE
- Bluetooth Low Energy (BLE)
- Embedded Systems
- IoT

## Team

- Ran Vijay Singh
- Garima Nidhi
- Roshni Haldar
- Janet Pushpa
