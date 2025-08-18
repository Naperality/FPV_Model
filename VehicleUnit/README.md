# Vehicle Unit – FPV Tele-Driving Trainer

## 📖 Overview
The **Vehicle Unit** is the RC vehicle platform for the FPV Tele-Driving Trainer.  
It receives driving commands from the Control Unit and controls the motors, steering, and other onboard systems.  
A **dedicated FPV camera and video transmitter** sends real-time video to the driver’s FPV goggles.

---

## 🛠️ Components
- **Base:** RC chassis or custom frame
- **Drive Motors:** DC motors with motor driver (L298N, BTS7960, etc.)
- **Steering:** Servo motor
- **Onboard Controller:** Raspberry Pi (or ESP32 if no Pi needed)
- **Wireless Communication Module:** Wi-Fi or RF receiver
- **FPV System:**  
  - FPV camera (Walksnail, DJI, FatShark, etc.)  
  - FPV video transmitter  
  - FPV goggles (receiver)
- **Battery:** LiPo or Li-ion pack

---

## ⚙️ How It Works
1. Raspberry Pi (or controller) receives control data from the Control Unit.
2. Commands are translated into motor driver and servo signals.
3. The FPV camera sends live video directly to the goggles via the FPV transmitter — bypassing the Pi to ensure minimal latency.
4. Vehicle movement and video feedback occur almost instantly.

---

## 📡 Communication Protocol
- Matches the Control Unit format:
```
STEER:512|ACC:300|BRK:0|GEAR:3|HB:0
```

- Pi interprets values and adjusts PWM outputs accordingly.

---

## 📂 File Structure

```
VehicleUnit/
│
├── README.md # This file
├── src/ # Raspberry Pi scripts for motor control
└── hardware/ # Wiring diagrams, chassis files
```

---

## 🔮 Possible Upgrades
- Add **two-axis gimbal** for FPV camera.
- Integrate **GPS** for telemetry.
- Add **collision detection sensors** (ultrasonic, IR).
- Enable **head tracking** for camera control.
