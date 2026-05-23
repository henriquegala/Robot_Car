# 🤖 Rover DETI 01: ESP32 Web-Controlled Robot

![Status](https://img.shields.io/badge/Status-Active_Development-brightgreen) ![Platform](https://img.shields.io/badge/Platform-ESP32-green) ![Stack](https://img.shields.io/badge/Stack-C%2B%2B%20%7C%20IoT-orange)

> **Current Status:** 🚀 **Active Development.** Phase 1 (Firmware/Electronics), Phase 2 (Networking/Web Server), and Phase 3 (Automation/Sensing) have been successfully developed, integrated, and verified on the bench. Low-level control, real-time telemetry, and autonomous obstacle avoidance are fully operational. Now moving to Phase 1 Trilha A (Physical Chassis Modeling in SolidWorks).

## 📖 About the Project
**Rover DETI 01** is an IoT exploration robot powered by an **Asynchronous ESP32 Microcontroller**. 
Unlike simple remote-controlled cars, this project focuses on **Low-Level Networking** and **Embedded Systems**. The robot hosts its own Web Server (HTTP), allowing control via any browser (Mobile/Desktop) over Wi-Fi, demonstrating the interaction between Hardware logic (C++) and Web interfaces.

## ⚙️ Hardware & Tech Stack
*   **Microcontroller:** ESP32 (Wi-Fi Module).
*   **Firmware:** C/C++ (Arduino IDE / PlatformIO) featuring non-blocking tasks (`millis()`) and communication safety nets.
*   **Actuators:** DC Motors with L298N V3 "4-Way" Driver (powered by a high-efficiency LM2596S buck converter).
*   **Sensors:** HC-SR04 (Ultrasonic Distance Sensor) protected by a 1K/2K resistor voltage divider.
*   **Power:** 2x 18650 Li-ion batteries in series (7.4V nominal) with a dedicated power switch.
*   **Web Interface:** HTML5, CSS3, JavaScript (Asynchronous Fetch API with touch/mouse momentary event listeners and periodic telemetry polling).

## 🗺️ Roadmap
Development is divided into sequential engineering phases:

### Phase 1: Hardware & Low-Level Control
- [X] Component acquisition (Motors, Chassis, Drivers, Batteries).
- [X] Circuit Assembly (Bench-test electronics successfully wired, including common ground verification).
- [X] Firmware implementation: Motor control logic (Forward, Backward, Stop with PWM speed control calibrated).
- [ ] Physical Chassis Assembly (CAD 3D modeling in SolidWorks and physical integration - **Current Goal**).

### Phase 2: Networking & Web Server
- [X] ESP32 Wi-Fi Configuration (Access Point Mode).
- [X] Embedded Web Server implementation (Handling Asynchronous HTTP Requests via unified routes).
- [X] Frontend Control Panel (Responsive Momentary Tank Steering UI with multi-touch event listeners).

### Phase 3: Automation & Sensing
- [X] Ultrasonic Sensor integration (with 1K/2K resistor voltage divider protection for 3.3V ESP32 pins).
- [X] Autonomous Obstacle Avoidance logic (using non-blocking `millis()` loops and manual override).
- [X] Real-time distance telemetry display on the Web Interface.

### Phase 4: Advanced Features (Long Term)
- [ ] Video Streaming (Camera Module).
- [ ] Bluetooth Low Energy (BLE) alternative control.

## 🔒 Security Note (Future Work)
As part of my interest in **Cybersecurity**, future updates will focus on securing the communication channel:
*   Implementing authentication for the Web Server.
*   Analyzing network packets between the client and the rover.

---
**Note:** This project is part of my personal portfolio as a Computer Engineering (LEI) student at the University of Aveiro (UA), Portugal. Active member of the NeRD core.