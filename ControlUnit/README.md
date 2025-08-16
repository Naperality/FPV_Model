# Control Unit – FPV Tele-Driving Trainer

## 📖 Overview
The **Control Unit** is the driver’s station for the FPV Tele-Driving Trainer.  
It consists of **physical driving controls** (steering wheel, pedals, gear stick, handbrake) connected to a microcontroller that sends commands to the vehicle wirelessly.  
Video feedback is provided **directly** by dedicated FPV goggles, ensuring near-zero latency without routing video through the control system.

---

## 🎯 Objectives
- Capture and send driver control inputs to the Vehicle Unit
- Ensure low-latency command transmission over Wi-Fi or RF link
- Integrate realistic, custom-built driving controls

---

## 🛠️ Components
- **Microcontroller:** Arduino Mega / Uno / ESP32
- **Driving Controls:**
  - Steering wheel with rotary encoder or potentiometer
  - Accelerator, brake, clutch pedals (potentiometer or load cell sensors)
  - Gear shifter with positional switches
  - Handbrake lever
- **Communication:** Wi-Fi module (ESP32 built-in or ESP8266)
- **Power Supply:** USB or DC adapter

---

## 📡 How It Works
1. User operates physical controls.
2. Arduino/ESP32 reads sensor data from controls.
3. Control data is packaged and sent wirelessly to the Vehicle Unit’s Raspberry Pi.
4. Vehicle Unit acts on these commands while video feed is handled by the FPV system.

---

## 📦 Skills & Tools
- Arduino IDE / PlatformIO
- C/C++ programming
- Basic electronics wiring & soldering

---

## 🔮 Future Improvements
- Force feedback for steering
- Adjustable pedal resistance
