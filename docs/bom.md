# Bill of Materials: Rover DETI 01

Final parts list of the finished rover (V4 build).

## 1. Brain & Logic

| Qty | Component | Notes |
|:---:|---|---|
| 1 | ESP32 development board (NodeMCU / DevKit, Wi-Fi + Bluetooth) | Microcontroller, Wi-Fi access point and web server |
| 1 | ESP32 expansion board with screw terminals | Makes the wiring easier and more secure |

## 2. Power & Motion Electronics

| Qty | Component | Notes |
|:---:|---|---|
| 1 | L298N V3 "4-Way" motor driver module | Integrated LM2596S buck converter and USB output ports |
| 2 | 18650 Li-ion rechargeable cells | |
| 1 | Holder for 2x 18650 in series (7.4 V nominal) | Integrated ON/OFF switch |
| 1 | Smart battery charger (e.g. Keenstone Smart LCD) | For charging the 18650 cells |

## 3. Actuators & Basic Mechanics

| Qty | Component | Notes |
|:---:|---|---|
| 2 | TT DC gear motors (yellow, 3 V to 6 V) | Drive motors |
| 2 | Plastic wheels for the TT motor shafts | About 63.5 mm diameter |
| 1 | Steel caster ball wheel (omnidirectional) | Front support |

## 4. Sensors & Peripherals

| Qty | Component | Notes |
|:---:|---|---|
| 1 | HC-SR04 ultrasonic distance sensor | 4 pins: VCC, Trig, Echo, GND |

## 5. Protection & Passive Components

| Qty | Component | Notes |
|:---:|---|---|
| 1 | Resistor 1 kΩ | Voltage divider for the Echo signal |
| 1 | Resistor 2 kΩ | Voltage divider for the Echo signal |

## 6. Hardware, Fixing & 3D-Printed Structure

| Qty | Component | Notes |
|:---:|---|---|
| 1 | 3D-printed chassis (V4) | Single-deck design, 150 × 210 mm, snap-fit walls for the sensor and holes for the boards. Files in `cad/v4/` |
| 1 | 3D-printed spacer block for the caster ball | |
| - | M3 screws | |
| - | Wool | Fixes the ESP32 and the motor driver |
| - | Hot glue | Fixes the TT motors and the battery holder |
| - | Dupont jumper wires (male-male, male-female, female-female) and bench wire for soldering | |

## Notes
- The 1 kΩ / 2 kΩ divider brings the 5 V Echo signal of the HC-SR04 down to about 3.3 V for the ESP32 input.
- Power: 2x 18650 in series give 7.4 V nominal. Use protected cells or a battery protection board, charge them only with a suitable charger, and never short them.
- Prices, quantities of small items (screws, wire) and the filament used are not listed here.
