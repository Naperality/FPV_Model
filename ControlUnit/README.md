# Control Unit – FPV Tele-Driving Trainer

## 📖 Overview
The **Control Unit** is the driver’s station for the FPV Tele-Driving Trainer.  
It contains all physical driving input devices — steering wheel, pedals, gear shifter, and handbrake — connected to a **microcontroller** (Arduino Mega or ESP32) that reads these inputs and sends them wirelessly to the Vehicle Unit.

---

## 🛠️ Components
- **Microcontroller:** Arduino Mega or ESP32
- **Steering Wheel:** Potentiometer or rotary encoder
- **Accelerator Pedal:** Potentiometer or load cell sensor
- **Brake Pedal:** Potentiometer or load cell sensor
- **Clutch Pedal (optional):** Potentiometer or load cell sensor
- **Gear Shifter:** Microswitches or rotary encoder
- **Handbrake Lever:** Potentiometer or microswitch
- **Wireless Communication:**  
  - **Wi-Fi** (ESP32, Pi, or separate module)  
  - **RF modules** (NRF24L01, HC-12, etc.)
- **Power Supply:** USB or 5V adapter

---

## ⚙️ How It Works
1. Each control device outputs an analog or digital signal.
2. The microcontroller reads the values in real-time.
3. Values are packaged into a data packet.
4. The packet is transmitted wirelessly to the Vehicle Unit.
5. The Vehicle Unit interprets the data and moves accordingly.

---

## 📡 Communication Protocol
- **Data Format Example:**  

```
STEER:512|ACC:300|BRK:0|GEAR:3|HB:0
```

- **Transmission Rate:** 50–100 Hz for smooth control.
- **Error Handling:** Include checksum or CRC to verify data integrity.

---

## 📂 File Structure

```
ControlUnit/
│
├── README.md # This file
├── src/ # Arduino or ESP32 firmware
└── hardware/ # Schematics, wiring diagrams, CAD files
```

---

## 🔮 Possible Upgrades
- Use **Hall effect sensors** for pedals and steering for higher precision.
- Add **force feedback** to steering wheel.
- Add **LCD display** to show speed, RPM, and gear.
