# Build Notes: Rover DETI 01

A log of how the rover was built, what went wrong, and what I would do differently.

## Summary
The finished rover is an ESP32-based robot that hosts its own web interface over a Wi-Fi access point, drives with PWM-controlled DC motors, and avoids obstacles on its own with an ultrasonic sensor. The final chassis is the 3D-printed **V4** design (`cad/v4/`). The electronics and firmware were verified on the bench before final assembly.

## Chassis iterations

| Version | What it was |
|---|---|
| V1 | Initial chassis design |
| V2 | Revised chassis with mounts for the battery, ESP32, L298N, motor and sensor |
| V3 | Intermediate iteration, superseded by V4 |
| V4 | Final design, used in the finished rover: single-deck chassis, 150 × 210 mm, with snap-fit walls for the sensor, holes for the boards and a spacer block for the caster ball |

## The hole-measurement problem (V4)

**What happened:** the mounting holes in the V4 print did not match the real component dimensions accurately.

**How I fixed it:** I used **wool padding** to hold the ESP32 and the motor driver, and **hot glue** to fix the TT motors and the battery holder. The wool fills the gaps and cushions the boards, and the hot glue locks the heavier parts in place.

**Result:** every component sits firmly and the rover runs reliably, including driving and obstacle avoidance. The fix is not elegant, but it is easy to undo and rework.

**Root cause:** (fill in, for example "dimensions taken from product photos or datasheets instead of measuring the real parts").

### Measurement log (optional, fill in if you still have the numbers)

| Component | Real size (measured) | Size used in CAD | Difference |
|---|---|---|---|
| ESP32 board | | | |
| L298N driver | | | |
| HC-SR04 | | | |
| Battery holder | | | |

## What I would do differently (V5)
These are general good practices rather than numbers measured on this build:
- **Measure the real parts with calipers** before modelling, and keep the measurements in a table like the one above.
- **Add clearance to the holes** to allow for printing tolerance. A small clearance on the order of a few tenths of a millimetre is a common starting point for FDM printing, tuned to your own printer.
- **Print a small test piece** with only the mounting patterns before printing the whole chassis.
- **Prefer slots and standoffs** over tight holes, so small errors can be absorbed.

## Electronics notes
- **Power:** 2x 18650 Li-ion cells in series (7.4 V nominal) in a holder with an integrated ON/OFF switch.
- **Motor driver:** L298N V3 "4-Way" module with an integrated LM2596S buck converter and USB output ports. The ESP32 sits on a screw-terminal expansion board, which makes the wiring easier and more secure.
- **Common ground** between the motor driver, buck converter and ESP32 was verified on the bench. Missing a common ground is one of the most common causes of erratic behaviour in this kind of build.
- **HC-SR04 protection:** the sensor works at 5 V, but ESP32 pins are 3.3 V. A 1 kΩ / 2 kΩ resistor divider on the echo line brings the signal down to a safe level.

## Firmware notes
- Written in C/C++ (Arduino IDE / PlatformIO) with **non-blocking** timing (`millis()`) instead of `delay()`, so the rover keeps responding to the web interface while the obstacle-avoidance logic runs.
- The ESP32 runs in **access point mode** and serves the control page through an asynchronous HTTP server.
- The web interface uses the Fetch API with touch and mouse "hold to move" events (momentary tank steering) and polls distance telemetry periodically.
- The firmware was **written by an AI assistant (Gemini)**, as described in the AI Usage Disclosure in the README. The learning goal of the project was the hardware and assembly side.

## Testing
- Bench test of the electronics before assembly, including common-ground verification.
- PWM speed control calibrated for forward, backward and stop.
- Obstacle avoidance and manual override verified on the finished rover.
- Real-time distance telemetry shown on the web interface.

## Possible future improvements
- V5 chassis with corrected hole tolerances.
- Camera module for video streaming.
- Bluetooth Low Energy (BLE) as an alternative control channel.
- Authentication on the web server and packet analysis of the client-rover traffic, as a cybersecurity exercise.
