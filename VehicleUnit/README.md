# Vehicle Unit – FPV Tele-Driving Trainer

## 📖 Overview
The **Vehicle Unit** is the mobile platform of the FPV Tele-Driving Trainer.  
It receives control commands from the Control Unit, actuates motors/steering, and streams live video through a **dedicated FPV video transmitter** to the driver’s FPV goggles.

---

## 🎯 Objectives
- Drive motors and steering based on remote control commands
- Provide near-zero latency video via FPV transmitter
- Maintain stable wireless connection for controls

---

## 🛠️ Components
- **Vehicle Platform:** RC car chassis or custom frame
- **Drive System:** DC motors with motor driver (L298N, BTS7960, etc.)
- **Steering:** Servo motor
- **Onboard Controller:** Raspberry Pi (receives commands and controls actuators)
- **Communication:** Wi-Fi link for control data
- **FPV Video System:**
  - FPV camera
  - FPV video transmitter (Walksnail, DJI, FatShark, etc.)
  - Powered from onboard battery

---

## 📡 How It Works
1. Raspberry Pi listens for control signals from Control Unit.
2. Commands are translated into motor driver and servo actions.
3. FPV camera sends live feed directly to driver’s FPV goggles via dedicated transmitter.
4. No video data passes through the Raspberry Pi, minimizing latency.

---

## 📦 Skills & Tools
- Python for Raspberry Pi control scripts
- Motor control programming
- Power management for mobile systems

---

## 🔮 Future Improvements
- Add distance sensors for collision alerts (buzzer in Control Unit)
- Modular battery system for longer runtimes
