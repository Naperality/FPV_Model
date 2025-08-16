# Vehicle Unit – FPV Tele-Driving Trainer

## 📖 Overview
The Vehicle Unit is the **RC car platform** for the FPV Tele-Driving Trainer project.  
It consists of a Raspberry Pi handling **motor control** and **live FPV video streaming** to the Control Unit's VR headset.

---

## 🛠 Components
- **Raspberry Pi 4/5** (for processing and streaming)
- **Motors & Steering**:
  - DC motor(s) for driving
  - Servo motor for steering
- **Motor Driver**: L298N / L293D / ESC
- **FPV Camera**: Pi Camera Module / USB camera
- **Wireless Communication**: Built-in Pi Wi-Fi or external dongle
- **Power Supply**: LiPo battery

---

## 📡 How It Works
1. Raspberry Pi receives control commands from the Control Unit over Wi-Fi or RF.
2. Pi translates commands into PWM signals for motors and steering.
3. Pi captures video from the camera.
4. Video is streamed in **side-by-side (SBS)** format for VR headset compatibility.
5. Video feed is viewed in real-time by the driver through a VR headset.

---

## 📷 Video Streaming
- **Protocol Options**:
  - WebRTC (low latency, <100 ms)
  - GStreamer (configurable latency)
  - Dedicated FPV transmitter/receiver for near-zero delay
- **Format**: Side-by-side (SBS) for VR headset display.

---

## 🔌 Wiring Overview
- Raspberry Pi GPIO → Motor driver → Motors
- Raspberry Pi GPIO (PWM) → Servo motor (steering)
- Camera connected via CSI or USB

---

## 🖥 Software
- Python scripts to:
  - Receive and parse control packets
  - Drive motors and steering via GPIO PWM
  - Stream camera feed to Control Unit
- Optional ROS 2 nodes for scalable communication.

---

## 📦 Skills Used
- Raspberry Pi hardware interfacing
- Python programming
- Motor driver control
- Low-latency video streaming
- Networking over Wi-Fi

---
