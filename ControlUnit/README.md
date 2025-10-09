# Control Unit – FPV Tele-Driving Trainer

## 📖 Overview
The **Control Unit** acts as the driver’s cockpit for the FPV Tele-Driving Trainer.  
It houses all physical input controls — **steering wheel**, **pedals**, **gear shifter**, and **handbrake** — which are read by an **ESP32-S3 N16R8** and transmitted wirelessly via **ESP-NOW** to the Vehicle Unit for real-time driving control.

---

## 🛠️ Components

| Part | Description |
|------|--------------|
| **Main Board** | ESP32-S3 N16R8 |
| **Steering Input** | AS5600 Magnetic Encoder + Steering Wheel |
| **Accelerator Pedal** | KY-024 or KY-035 Linear Hall Sensor |
| **Brake Pedal** | HX711 Amplifier + 5 kg Load Cell |
| **Gear Shifter** | Omron D2FC-F-7N / KW12-3 Microswitches in 3D Printed Shifter Housing |
| **Handbrake** | Lever + Omron D2FC-F-7N / KW12-3 Microswitch |
| **Wireless Link** | ESP-NOW (Direct peer-to-peer ESP32 communication) |
| **Power Supply** | USB-C / 5V Regulated Adapter |

---

## ⚙️ How It Works

1. The **ESP32-S3** continuously reads all analog and digital inputs from the controls:
   - The **AS5600 encoder** provides steering angle data.
   - The **Hall sensors** detect pedal positions.
   - The **Load Cell + HX711** measures brake pressure.
   - The **Omron switches** detect gear shift positions and handbrake engagement.
2. The ESP32-S3 packages these values into a structured data packet.
3. Data is transmitted via **ESP-NOW** to the **Vehicle Unit** at high frequency (~100 Hz).
4. The Vehicle Unit interprets the values and responds instantly with motor and steering actions.

---

## 📡 Communication Protocol

- **Transmission Type:** ESP-NOW (peer-to-peer, low-latency)
- **Typical Update Rate:** 50 – 100 Hz
- **Packet Format:**

```
STEER:512|ACC:300|BRK:120|GEAR:2|HB:0
```

---
- **Field Descriptions:**

| Field | Description |
|--------|-------------|
| **STEER** | Steering position (0–1023 from AS5600) |
| **ACC** | Accelerator pedal position (0–1023 from Hall sensor) |
| **BRK** | Brake pressure (0–1023 mapped from HX711) |
| **GEAR** | Gear selector position (integer value 0–5) |
| **HB** | Handbrake state (0 = off, 1 = on) |

---

## ⚙️ Wiring Summary

| Component | Signal Type | ESP32 Pin Example |
|------------|--------------|-------------------|
| AS5600 Magnetic Encoder | I²C (SDA/SCL) | GPIO 21 (SDA), GPIO 22 (SCL) |
| KY-024 / KY-035 Pedal Sensor | Analog | GPIO 34 (ACC), GPIO 35 (optional clutch) |
| HX711 + Load Cell | Digital (DT/SCK) | GPIO 18 (DT), GPIO 19 (SCK) |
| Gear Shifter Switches | Digital | GPIO 12–15 |
| Handbrake Switch | Digital | GPIO 27 |
| ESP-NOW Communication | Wi-Fi Hardware | Internal |
| Power | 5 V USB-C | — |

---

## 📂 File Structure

```
ControlUnit/
│
├── README.md # This file
├── src/
│ ├── main.ino # ESP32-S3 firmware for reading sensors & sending packets
│ └── espnow_sender.h # ESP-NOW transmission logic
│
└── hardware/
├── wiring_diagram.png # Control panel wiring schematic
├── 3d_shifter_case.stl # 3D printable gear shifter container
└── pinout_reference.pdf
```


---

## 🔮 Future Enhancements

- Add **clutch pedal** input for manual transmission simulation.  
- Implement **force feedback** using a motorized steering wheel.  
- Include **OLED/LCD dashboard** for live telemetry (gear, throttle, brake).  
- Integrate **hand-tracking or voice control** for secondary functions.  
- Add **vibration/haptic feedback** for enhanced realism.

---

## ⚙️ Notes

- The **ESP32-S3 N16R8** provides ample processing power and memory for simultaneous analog, digital, and wireless tasks.  
- Using **ESP-NOW** ensures **ultra-low latency** control, independent of Wi-Fi networks.  
- Make sure to **debounce all microswitches** (hardware or software) to avoid false triggers.  

---

> **Disclaimer:**  
> This Control Unit is intended for **educational and experimental** applications only.  
> Not suitable for use in real vehicles or outdoor operation.