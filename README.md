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
| **Board** | ESP32-S3 N16R8 |
| **Steering** | AS5600 Magnetic Encoder + Custom Steering Wheel |
| **Pedals** | KY-024/KY-035 Magnetic Sensor + HX711 + 5KG Load Cell |
| **Gear Shifter** | Omron D2FC-F-7N or KW12-3 Micro Switch + 3D Printed Gear Container |
| **Emergency Handbrake** | Omron D2FC-F-7N or KW12-3 Micro Switch + Lever Mechanism |
| **Wireless Link** | ESP-NOW / Wi-Fi Communication to Vehicle Unit |

---

### 🚗 Vehicle Unit
| Part | Description |
|------|--------------|
| **Board** | ESP32-S3 N16R8 |
| **Engine** | Brushed DC Motor (200 RPM) + BTS7960 Motor Driver |
| **Steering** | DS3218 Servo Motor |
| **Chassis** | 1/10 RC Car Frame |
| **FPV Setup** | Dedicated FPV Camera + Transmitter (Walksnail, DJI, or FatShark) |
| **Power** | LiPo Battery |

---

### 🎥 2DOF Tilt Unit
| Part | Description |
|------|--------------|
| **Board** | ESP32-S3 N16R8 |
| **Tilting Mechanism** | 2× SG90 or MG90S Servo Motors |
| **Mount** | Dual-Axis Servo Mount for FPV Camera |
| **Control Input** | Data from Headgear Unit (Head Tilt) |

---

### 🪖 Headgear Unit
| Part | Description |
|------|--------------|
| **Board** | ESP32-S3 N16R8 |
| **Sensor** | MPU6050 (for head tilt motion tracking) |
| **Wireless Link** | Sends head orientation data to 2DOF Tilt Unit |

---

## 📡 How It Works

1. **Control Unit (Driver Station)**  
   - Reads steering, pedal, gear, and handbrake inputs using sensors and switches.  
   - Sends control signals wirelessly to the **Vehicle Unit** via **ESP-NOW**.

2. **Vehicle Unit (RC Car)**  
   - Receives driving commands and actuates the motor (via BTS7960) and steering servo (DS3218).  
   - The onboard FPV camera transmits live video directly to FPV goggles using a **dedicated FPV system**, not processed by the ESP32.

3. **2DOF Tilt & Headgear Units**  
   - The **Headgear Unit** tracks head tilt using an **MPU6050**, then transmits data to the **2DOF Tilt Unit**, which adjusts two servos to pan and tilt the FPV camera accordingly.

4. **Video Feedback**  
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