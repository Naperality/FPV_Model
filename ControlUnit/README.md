# 🎮 Control Unit – FPV Tele-Driving Trainer

## 📖 Overview
The **Control Unit** acts as the **driver station** of the FPV Tele-Driving Trainer system.  
It captures the driver’s inputs through physical controls such as a **steering wheel, pedals, and gear shifter**, then converts them into digital control signals.

These signals are transmitted wirelessly to the **Vehicle Unit** using an RF communication module (NRF24L01 PA+LNA or ESP-NOW). The goal is to replicate a **realistic driving interface** similar to an actual vehicle cockpit.

---

## 🎯 Objectives

- Capture driver inputs using sensors and mechanical controls.
- Convert physical movement into digital control signals.
- Transmit control commands wirelessly to the vehicle.
- Provide low-latency input response for smooth tele-driving.

---

## 🧰 Hardware Components

| Component | Description |
|-----------|-------------|
| **Microcontroller** | Arduino Uno |
| **Steering Sensor** | AS5600 Magnetic Rotary Encoder |
| **Pedal Sensors** | Hall Effect Sensors |
| **Gear Shifter Sensor** | KY-024 / KY-035 Magnetic Sensor |
| **Wireless Module** | NRF24L01 PA+LNA or ESP32 ESP-NOW |
| **Display (optional)** | OLED display for telemetry feedback |

---

## 🎮 Driver Controls

### Steering Wheel
- Uses an **AS5600 magnetic encoder** for contactless rotation measurement.
- Converts wheel angle into steering commands.
- Mimics real vehicle steering behavior.

### Pedal System
Two pedals are used:

| Pedal | Function |
|------|---------|
| Accelerator | Controls vehicle throttle |
| Brake | Controls braking or reverse |

Hall sensors detect pedal position via magnetic displacement.

---

### Gear Shifter

A **linear magnetic gear shifter** provides four positions:
```
P → Park
R → Reverse
N → Neutral
D → Drive
```


The KY-024/KY-035 sensor detects the magnet position to determine the gear state.

---

## 📡 Wireless Communication

The control unit sends a **structured data packet** to the vehicle unit containing:

Example structure:

```cpp
struct Telemetry {
  uint8_t steering;
  uint16_t throttle;
  uint16_t brake;
  uint8_t gear;
};
```

---

## ⚙️ System Workflow

- Driver moves steering wheel or pedals.
- Sensors detect position changes.
- Arduino converts readings to control values.
- Data packet is transmitted wirelessly.
- Vehicle Unit receives commands and executes them.


---

### 📂 Directory Structure

```
ControlUnit/
│
├── src/
│   ├── main_control.ino
│   ├── steering_reader.ino
│   ├── pedal_reader.ino
│
├── hardware/
│   ├── wiring_diagram.png
│   ├── steering_mechanism.stl
│
└── README.md
```

---