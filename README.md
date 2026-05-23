# 🤖 Rover DETI 01: ESP32 Web-Controlled Robot

![Status](https://img.shields.io/badge/Status-Active_Development-brightgreen) ![Platform](https://img.shields.io/badge/Platform-ESP32-green) ![Stack](https://img.shields.io/badge/Stack-C%2B%2B%20%7C%20IoT-orange)

> **Current Status:** 🚀 **Active Development.** The low-level electronics and motor calibration have been successfully validated on the bench. Currently implementing Phase 2 (Asynchronous Web Server and Access Point control).

## 📖 About the Project
**Rover DETI 01** is an IoT exploration robot powered by an **ASYNCHRONOUS ESP32 Microcontroller**. 
Unlike simple remote-controlled cars, this project focuses on **Low-Level Networking** and **Embedded Systems**. The robot hosts its own Web Server (HTTP), allowing control via any browser (Mobile/Desktop) over Wi-Fi, demonstrating the interaction between Hardware logic (C++) and Web interfaces.

## ⚙️ Hardware & Tech Stack
*   **Microcontroller:** ESP32 (Wi-Fi Module).
*   **Firmware:** C/C++ (Arduino IDE / PlatformIO).
*   **Actuators:** DC Motors with L298N V3 "4-Way" Driver (powered by a high-efficiency LM2596S buck converter).
*   **Sensors:** HC-SR04 (Ultrasonic Distance Sensor).
*   **Power:** 2x 18650 Li-ion batteries in series (7.4V nominal) with a dedicated power switch.
*   **Web Interface:** HTML5, CSS3, JavaScript (Asynchronous Fetch API).

## 🗺️ Roadmap
Development is divided into sequential engineering phases:

### Phase 1: Hardware & Low-Level Control
- [X] Component acquisition (Motors, Chassis, Drivers, Batteries).
- [X] Circuit Assembly (Bench-test electronics successfully wired, including common ground verification).
- [X] Firmware implementation: Motor control logic (Forward, Backward, Stop with PWM speed control calibrated).
- [ ] Physical Chassis Assembly (CAD 3D modeling in SolidWorks and physical integration - *Paused for Phase 2*).

### Phase 2: Networking & Web Server
- [🔄] ESP32 Wi-Fi Configuration (Access Point Mode) - *In Progress (Step 2.1)*.
- [ ] Embedded Web Server implementation (Handling HTTP Requests).
- [ ] Frontend Control Panel (HTML/CSS UI with responsive D-Pad).

### Phase 3: Automation & Sensing
- [ ] Ultrasonic Sensor integration (with voltage divider protection for 3.3V ESP32 pins).
- [ ] Autonomous Obstacle Avoidance logic.
- [ ] Real-time telemetry display on the Web Interface.

### Phase 4: Advanced Features (Long Term)
- [ ] Video Streaming (Camera Module).
- [ ] Bluetooth Low Energy (BLE) alternative control.

## 🔒 Security Note (Future Work)
As part of my interest in **Cybersecurity**, future updates will focus on securing the communication channel:
*   Implementing authentication for the Web Server.
*   Analyzing network packets between the client and the rover.

---
**Note:** This project is part of my personal portfolio as a Computer Engineering (LECI) student at the University of Aveiro (UA), Portugal. Active member of the NeRD core.
