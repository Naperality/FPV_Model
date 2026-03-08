
---

# 🚗 Vehicle Unit – FPV Tele-Driving Trainer

## 📖 Overview

The **Vehicle Unit** is the mobile robotic platform that executes driving commands received from the **Control Unit**.

It consists of an **RC car chassis, motor controller, steering servo, and FPV camera system**. The microcontroller receives wireless commands and translates them into motor speed and steering angle.

This unit also carries the **FPV camera and video transmitter**, providing the driver with a real-time first-person view of the vehicle.

---

## 🎯 Objectives

- Receive wireless driving commands from the Control Unit
- Control the vehicle's steering and motor
- Provide real-time FPV video feedback
- Maintain responsive teleoperation performance

---

## 🧰 Hardware Components

| Component | Description |
|-----------|-------------|
| **Microcontroller** | Arduino Uno |
| **Motor** | Brushed 540 DC Motor |
| **Motor Controller** | Hobbywing Quicrun ESC |
| **Steering Servo** | DS3218 High Torque Servo |
| **Chassis** | 1/10 Scale RC Car Frame |
| **FPV Camera** | Analog/Digital FPV Camera |
| **Video Transmitter** | Walksnail / DJI / FatShark |
| **Battery** | 11.1V LiPo Battery (3S 30C) |

---

## 📡 Wireless Control

The vehicle unit receives command packets from the control unit.

Example received structure:

```cpp
struct Telemetry {
  uint8_t steering;
  uint16_t throttle;
  uint16_t brake;
  uint8_t gear;
};
```

---

## ⚙️ Motor Control

The Hobbywing Quicrun ESC regulates the motor speed.
Signal interface:
```

PWM Signal → ESC → Motor Speed Control

```
Typical ESC PWM ranges:

| Signal | Value |
|-----------|-------------|
| **Full Reverse** | 1000 µs |
| **Neutral** | 1500 µs |
| **Full Forward** | 2000 µs |

---

## 🔧 Steering System

The steering system uses a DS3218 servo motor connected to the front steering linkage.
```

Steering Command → Servo PWM → Wheel Angle

```
Servo characteristics:
- Torque: ~20 kg·cm
- Voltage: 6–7.4V
- Rotation: ~180°

---

## 📂 Directory Structure

```
VehicleUnit/
│
├── src/
│   ├── vehicle_control.ino
│   ├── radio_receiver.cpp
│   ├── motor_control.cpp
│
├── hardware/
│   ├── wiring_diagram.png
│   ├── chassis_layout.stl
│
└── README.md
```

---