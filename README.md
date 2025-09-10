# FPV Tele-Driving Trainer

## 📖 Overview
The **FPV Tele-Driving Trainer** is a personal engineering project that simulates driving a vehicle from a **first-person perspective** using an RC platform.  
It combines **custom-built physical driving controls** — steering wheel, pedals, gearshift, and handbrake — with a **live FPV (First-Person View) video feed** from a camera mounted on the vehicle.  

Unlike computer-based streaming, the system uses a **dedicated FPV video transmitter and receiver** (similar to drone racing systems such as Walksnail, DJI, or FatShark), providing **ultra-low latency** video directly to FPV goggles for a smooth and immersive driving experience.
---




































## 🎯 Objectives

- Build a controllable FPV vehicle with realistic driving controls.
- Achieve **sub-50 ms video latency** via a dedicated FPV system.
- Separate the project into two main modules:
  - **Control Unit** – driver input hardware
  - **Vehicle Unit** – RC vehicle hardware
- Integrate electronics, mechanics, and wireless control into a cohesive system.
- Provide an educational platform for robotics, teleoperation, and embedded systems.

---

## 🛠️ Components

### Control Unit
- Arduino Mega / ESP32
- Steering wheel (potentiometer or encoder)
- Accelerator and brake pedals (potentiometers or load cell sensors)
- Gear shifter (switches or encoders)
- Handbrake lever
- Wi-Fi or RF module for sending control data

### Vehicle Unit
- RC chassis or custom frame
- DC drive motors + motor driver (L298N, BTS7960, etc.)
- Servo motor for steering
- Raspberry Pi for receiving control data and controlling actuators
- Wi-Fi or RF receiver module
- **FPV camera** (dedicated, not Pi camera)
- **FPV video transmitter** (Walksnail, DJI, FatShark, etc.)
- Onboard battery

---

## 📡 How It Works

1. **Driver’s Station (Control Unit)**  
   - Physical driving controls are connected to an Arduino/ESP32.
   - The microcontroller reads the inputs and sends control commands wirelessly to the Vehicle Unit.

2. **Vehicle Control (Vehicle Unit)**  
   - Raspberry Pi receives commands and drives the motors/steering accordingly.
   - The onboard FPV camera sends live video directly to the driver’s FPV goggles through the dedicated transmitter.

3. **Video Feedback**  
   - Video does **not** pass through the Raspberry Pi, avoiding processing delays.
   - The FPV goggles receive the feed in near real-time, similar to professional drone setups.

---

## 📦 Repository Structure

```
FPV_Model/
│
├── ControlUnit/
│ ├── README.md # Details of the Control Unit hardware and firmware
│ ├── src/ # Arduino/ESP32 code
│ └── hardware/ # Schematics, CAD files
│
├── VehicleUnit/
│ ├── README.md # Details of the Vehicle Unit hardware and control code
│ ├── src/ # Raspberry Pi control scripts
│ └── hardware/ # Wiring diagrams, chassis files
│
└── README.md # (This file) Project overview
```


---

## 🔮 Future Improvements

- Add **head-tracking** to move a gimbal-mounted FPV camera.
- Implement **haptic feedback** for steering and pedals.
- Integrate basic obstacle detection sensors for safety.
- Test different FPV modules for range and image quality.

---

## 📦 Skills & Technologies Involved

- **Electronics:** Arduino, ESP32, Raspberry Pi, motor drivers, sensors.
- **Programming:** Python, C/C++.
- **Networking:** Wi-Fi or RF control link.
- **FPV Systems:** Dedicated camera and transmitter for low-latency video.
- **Mechanical Fabrication:** Custom steering and pedal assemblies.

---

> **Disclaimer:** This project is for educational and experimental use only. Not intended for real vehicle operation on public roads.
