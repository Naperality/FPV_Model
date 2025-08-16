# Control Unit – FPV Tele-Driving Trainer

## 📖 Overview
The Control Unit is the **driver's station** for the FPV Tele-Driving Trainer project.  
It consists of physical driving controls — steering wheel, pedals, gear shifter, and handbrake — connected to a microcontroller (Arduino or ESP32) that reads input values and sends them wirelessly to the **Vehicle Unit**.

---

## 🛠 Components
- **Microcontroller**: Arduino Mega / Uno / ESP32
- **Controls**:
  - Steering wheel (potentiometer-based)
  - Accelerator pedal (potentiometer or load cell)
  - Brake pedal (potentiometer or load cell)
  - Clutch pedal (potentiometer)
  - Gear shifter (positional switches/sensors)
  - Handbrake lever (switch or potentiometer)
- **Wireless Communication**:
  - Wi-Fi (ESP32 or Arduino + ESP8266)
  - Optional: NRF24L01 or RF module

---

## 📡 How It Works
1. The microcontroller reads analog and digital signals from the controls.
2. Inputs are converted into control commands:

```
STEER=45
THROTTLE=80
BRAKE=0
GEAR=2
```

3. Commands are sent over Wi-Fi or RF to the Vehicle Unit at ~20–50 Hz.

---

## 🔌 Wiring Overview
- Potentiometers connected to analog pins for steering and pedals.
- Switches or sensors connected to digital pins for gear and handbrake.
- Communication module connected via UART or SPI.

---

## 🖥 Software
- **Arduino IDE** for microcontroller programming.
- Code reads all inputs, formats them into a packet, and transmits to Vehicle Unit.
- Communication protocol: UDP, WebSocket, or ROS 2 micro-ROS.

---

## 📦 Skills Used
- Electronics wiring and sensor interfacing
- Microcontroller programming (C/C++)
- Networking basics (Wi-Fi or RF communication)

---
