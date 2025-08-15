# FPV Tele-Driving Trainer (VR Headset Edition)

## 📖 Overview

The **FPV Tele-Driving Trainer** is a personal engineering project that simulates the experience of driving a real vehicle through a **first-person view (FPV)** system.  
It combines **hardware controls** such as a steering wheel, pedals, and gearshift with a live video feed from a camera mounted on a small RC car.  
Instead of viewing the feed on a screen, the project uses a **Google Cardboard-compatible VR headset** (or similar FPV goggles) for a fully immersive driving experience.  
The goal is to replicate the sensation of being inside the vehicle while serving as a training platform for simulation, robotics, and remote control applications.

---

## 🎯 Objectives

- Build a controllable FPV system using a camera-equipped vehicle
- Design and fabricate custom **physical driving controls**:
  - Steering wheel
  - Accelerator pedal
  - Brake pedal
  - Clutch pedal
  - Gear stick
  - Handbrake
- Enable smooth, low-latency video streaming directly to an FPV/VR headset
- Integrate **hardware electronics**, **software control systems**, and **mechanical design** into one project
- Explore immersive teleoperation, robotics education, and driving simulation applications

---

## 🛠️ System Components

### 1. **Vehicle Platform**
- Small RC chassis or custom-built frame
- **DC motors / Servo motors** for movement and steering
- Motor driver module for control signals
- Mounted FPV camera (optimized for headset viewing)

### 2. **Control Hardware**
- DIY steering wheel mechanism
- Pedals (gas, brake, clutch) with potentiometer or load cell input
- Gear shifter with positional sensors
- Handbrake lever
- Microcontroller (e.g., **Arduino Mega/Uno** or **ESP32**) for reading control inputs

### 3. **Processing & Communication**
- **Raspberry Pi** (onboard vehicle) for camera feed and command processing
- Wi-Fi or RF module for control signal transmission
- Low-latency video streaming protocol (e.g., WebRTC)
- Video feed formatted for **side-by-side (SBS)** view for VR headset compatibility

### 4. **Viewing System**
- **Google Cardboard-compatible VR headset** (or FPV goggles)
- Smartphone or small display inside headset receives live stream from Raspberry Pi
- Gyroscope integration (optional) for head tracking to pan camera

---

## 📡 How It Works

1. **Driver’s Station**  
   The user operates physical driving controls (steering wheel, pedals, gearstick, handbrake) built from custom parts connected to a microcontroller.

2. **Signal Processing**  
   Control inputs are read by the microcontroller and sent wirelessly to the Raspberry Pi on the vehicle.

3. **Vehicle Response**  
   The Raspberry Pi translates received commands into motor and servo actions while streaming a side-by-side 3D camera feed.

4. **Immersive FPV Driving**  
   The user wears a VR headset with a smartphone or display showing the live feed, creating the sensation of being inside the vehicle.

---

## 🔮 Future Improvements

- Add **head-tracking** to move the onboard camera based on headset orientation
- Integrate **haptic feedback** for steering and pedals
- Include **AI driver assistance** using YOLOv8
- Improve streaming performance with **dedicated FPV video transmitters**
- Record and replay driving sessions in VR

---

## 📦 Skills & Technologies Involved

- **Electronics:** Arduino, ESP32, Raspberry Pi, motor drivers, sensors
- **Programming:** Python, C/C++
- **Networking:** Wi-Fi control, low-latency streaming
- **VR Integration:** Side-by-side video formatting, optional head tracking
- **Mechanical Fabrication:** Custom driving control system
- **Computer Vision:** Optional YOLOv8 for object detection

---

> **Disclaimer:** This project is for educational and training purposes only. It is not intended for real vehicle operation on public roads.
