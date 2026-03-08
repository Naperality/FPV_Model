# FPV Tele-Driving Trainer

## 📖 Overview
The **FPV Tele-Driving Trainer** is a personal engineering project that simulates driving a vehicle from a **first-person perspective** using an RC platform.  
It combines **custom-built physical driving controls** — steering wheel, pedals, gear shifter, and handbrake — with a **live FPV (First-Person View)** video feed from a camera mounted on the vehicle.

Unlike computer-based streaming, the system uses a **dedicated FPV video transmitter and receiver** (such as Walksnail, DJI, or FatShark) to provide **ultra-low latency** video directly to FPV goggles for a smooth and immersive driving experience.

---

## 🎯 Objectives

- Build a controllable FPV vehicle with realistic driving controls.  
- Achieve **sub-50 ms video latency** via a dedicated FPV system.  
- Separate the project into four functional modules:
  - **Control Unit** – driver control inputs
  - **Vehicle Unit** – RC vehicle with motor and steering
  - **2DOF Tilt Unit** – head-tilt gimbal for the FPV camera
  - **Headgear Unit** – head tracking control interface
- Integrate electronics, mechanics, and wireless control into a cohesive teleoperation system.
- Provide an educational platform for robotics, mechatronics, and remote vehicle operation.

---

## 🛠️ Components

### 🧭 Control Unit
| Part | Description |
|------|--------------|
| **Board** | Arduino Uno |
| **Steering** | AS5600 Magnetic Encoder + Custom Steering Wheel |
| **Pedals** | Hall-effect Sensors |
| **Gear Shifter** | KY-024/KY-035 Magnetic Sensor + Custom Linear P-R-N-D Shifter |
| **Wireless Link** | ESP-NOW / NRF24 PA+LNA |

---

### 🚗 Vehicle Unit
| Part | Description |
|------|--------------|
| **Board** | Arduino Uno |
| **Engine** | Brushed 540 DC Motor (200 RPM) + Hobbywing Quikrun ESC |
| **Steering** | DS3218 Servo Motor |
| **Chassis** | 1/10 RC Car Frame |
| **FPV Setup** | Dedicated FPV Camera + Transmitter (Walksnail, DJI, or FatShark) |
| **Power** | LiPo Battery(11.1 30C rating) |

---

## 📡 How It Works

1. **Control Unit (Driver Station)**  
   - Reads steering, pedal, and gear inputs using sensors and switches.  
   - Sends control signals wirelessly to the **Vehicle Unit** via **(SPI) Radio Transmission**.

2. **Vehicle Unit (RC Car)**  
   - Receives driving commands and actuates the motor (via Hobbywing ESC) and steering servo (DS3218).  
   - The onboard FPV camera transmits live video directly to FPV goggles using a **dedicated FPV system**, not processed by the Arduino.

3. **Video Feedback**  
   - Video bypasses any microcontroller, streaming directly to the goggles for **near-zero latency** — similar to drone FPV racing setups.

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

- Integrate **force feedback** for the steering wheel.  
- Add **suspension sensors** or **IMU data** for terrain feedback.  
- Implement **vehicle telemetry** (speed, voltage, temp) overlay on FPV.  
- Upgrade wireless link to **ESP-NOW Mesh** or **custom RF modules** for longer range.  
- Add **mobile app interface** for monitoring system parameters.

---

## ⚙️ Skills & Technologies Involved

- **Electronics:** ESP32-S3, sensors, motor drivers, servos  
- **Programming:** C/C++ (Arduino/ESP-IDF)  
- **Networking:** ESP-NOW / Wi-Fi communication  
- **FPV Systems:** Dedicated camera and video transmitter  
- **Mechanical Design:** 3D printing, custom steering/pedal assemblies  

---

> **Disclaimer:**  
> This project is for **educational and experimental purposes only**.  
> It is not intended for real vehicle operation or use on public roads.