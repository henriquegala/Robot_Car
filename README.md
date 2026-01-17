```markdown
# 🤖 Rover DETI 01: ESP32 Web-Controlled Robot

![Status](https://img.shields.io/badge/Status-Under_Development-yellow) ![Platform](https://img.shields.io/badge/Platform-ESP32-green) ![Stack](https://img.shields.io/badge/Stack-C%2B%2B%20%7C%20IoT-orange)

> **Current Status:** 🚧 **Paused temporarily.** Development is on hold during the University of Aveiro (UA) exam season. Hardware assembly and coding will resume in February.

## 📖 About the Project
**Rover DETI 01** is an IoT exploration robot powered by an **ESP32 Microcontroller**. 
Unlike simple remote-controlled cars, this project focuses on **Low-Level Networking** and **Embedded Systems**. The robot hosts its own Web Server (HTTP), allowing control via any browser (Mobile/Desktop) over Wi-Fi, demonstrating the interaction between Hardware logic (C++) and Web interfaces.

## ⚙️ Hardware & Tech Stack
*   **Microcontroller:** ESP32 (Wi-Fi Module).
*   **Firmware:** C/C++ (Arduino IDE / PlatformIO).
*   **Actuators:** DC Motors with L298N Driver.
*   **Sensors:** HC-SR04 (Ultrasonic Distance Sensor).
*   **Web Interface:** HTML5, CSS3, JavaScript (Asynchronous Fetch API).

## 🗺️ Roadmap
Development is divided into sequential engineering phases:

### Phase 1: Hardware & Low-Level Control
- [X] Component acquisition (Motors, Chassis, Drivers).
- [ ] Circuit Assembly.
- [ ] Firmware implementation: Motor control logic (Forward, Backward, Stop).

### Phase 2: Networking & Web Server
- [ ] ESP32 Wi-Fi Configuration (Access Point / Station Mode).
- [ ] Embedded Web Server implementation (Handling HTTP Requests).
- [ ] Frontend Control Panel (HTML/CSS UI).

### Phase 3: Automation & Sensing
- [ ] Ultrasonic Sensor integration (Data reading).
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
**Note:** This project is part of my personal portfolio as a Computer Engineering student at UA.
