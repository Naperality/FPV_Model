# Vehicle Unit – FPV Tele-Driving Trainer

## 📖 Overview
The **Vehicle Unit** serves as the RC vehicle platform of the FPV Tele-Driving Trainer.  
It receives control data from the **Control Unit** via **ESP-NOW** and drives the **motor**, **steering servo**, and other systems onboard.  
A **dedicated FPV camera and video transmitter** provides a real-time, low-latency first-person view directly to the driver’s FPV goggles — fully independent from the ESP32 system.

---

## 🛠️ Components

| Part | Description |
|------|--------------|
| **Main Board** | ESP32-S3 N16R8 |
| **Chassis Base** | 1/10 Scale RC Car Frame |
| **Drive Motor** | Brushed DC Motor (200 RPM) |
| **Motor Driver** | BTS7960 (for brushed DC motors) |
| **Steering Motor** | DS3218 High-Torque Servo |
| **FPV System** | FPV Camera + Video Transmitter (Walksnail, DJI, or FatShark) |
| **Power Supply** | LiPo or Li-ion Battery Pack |
| **Wireless Link** | ESP-NOW (direct communication with Control Unit) |

---

## ⚙️ How It Works

1. The **ESP32-S3 Vehicle Unit** receives wireless control data from the **Control Unit** using the **ESP-NOW protocol**.
2. The **BTS7960** motor driver regulates power to the **DC motor**, controlling forward and reverse motion based on throttle input.
3. The **DS3218 servo** adjusts steering position based on steering angle commands.
4. The **FPV camera** transmits a live video feed directly to FPV goggles — bypassing the ESP32 entirely for **ultra-low latency**.
5. The onboard battery powers all electronic components, maintaining wireless and motor operation simultaneously.

---

## 📡 Communication Protocol

The **Control Unit** transmits structured data packets via ESP-NOW, formatted as:

```
STEER:512|ACC:300|BRK:0|GEAR:3|HB:0
```

---

| Field | Description |
|--------|--------------|
| **STEER** | Steering wheel angle (0–1023 mapped to servo PWM) |
| **ACC** | Accelerator pedal position (0–1023 mapped to DC motor speed) |
| **BRK** | Brake intensity (0–1023 mapped to reverse torque or stop) |
| **GEAR** | Current gear state (e.g., Park, Drive, Reverse) |
| **HB** | Handbrake toggle (0 = off, 1 = engaged) |

The ESP32 parses this data and outputs PWM signals to the BTS7960 and DS3218 servo accordingly.

---

## ⚙️ Control Logic Summary

| Function | Hardware | Description |
|-----------|-----------|-------------|
| **Throttle/Brake** | BTS7960 + DC Motor | Converts input throttle/brake values into PWM motor control |
| **Steering** | DS3218 Servo | Adjusts wheel angle proportionally to steering input |
| **Gear & Handbrake** | Digital Pins | Interprets logic signals for gear state and handbrake |

---

## 📂 File Structure

```
VehicleUnit/
│
├── README.md # This file
├── src/
│ ├── main.ino # ESP32-S3 control firmware for motor & steering
│ └── espnow_receiver.h # Handles wireless data reception and parsing
│
└── hardware/
├── wiring_diagram.png # Motor & servo wiring schematic
├── chassis_model.stl # (Optional) 3D model of chassis frame
└── pinout_reference.pdf
```


---

## 🔮 Future Enhancements
- Add **wheel speed sensor** for closed-loop speed control.  
- Integrate **IMU (MPU6050)** for stability and tilt sensing.  
- Implement **telemetry feedback** to Control Unit (battery voltage, RPM, etc.).  
- Support **head-tracked gimbal** from 2DOF Tilt Unit for dynamic FPV view.  
- Add **proximity sensors** (ultrasonic, IR, or ToF) for obstacle detection.

---

## ⚙️ Notes
- The FPV video stream operates **independently** from ESP-NOW communication.  
- Using **ESP32-S3 N16R8** ensures stable performance and low latency for control response.  
- Proper isolation of **motor driver power and logic ground** is crucial to prevent noise in signal lines.

---

> **Disclaimer:**  
> This system is designed solely for educational and experimental use.  
> It is **not intended for use in real vehicles** or outdoor public environments.