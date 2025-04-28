# 🤖 Circular Motion Bot using Arduino UNO, MPU6050, and N20 Motors

## 🧠 Introduction

This is a small robotics project where we built a bot that moves along a fixed circular path using basic components like an Arduino UNO, N20 motors, an MPU6050 sensor, and a custom Zero PCB.  
Instead of using encoders to track wheel rotation, the bot uses **yaw feedback** from the MPU6050 gyroscope to maintain a stable circular movement.

---

## ⚙️ How It Works

- The bot is programmed to follow a circle of a given radius (adjustable in the code).
- It uses the **yaw rate** (rotation speed) from the MPU6050 to correct motor speeds while moving.
- A simple **proportional controller (P-controller)** keeps adjusting the left and right motor speeds to stay on the desired path.
- Once the bot completes a full **360° rotation** (i.e., one full circle), it **automatically stops** (this behavior is configurable).

---

## 🛠️ Hardware Used

- **Arduino UNO** – Main controller
- **N20 Motors** – Small DC geared motors (with optional encoders, but not used here)
- **MPU6050** – 6-axis accelerometer and gyroscope
- **Buck Converter** – To step down the 7.4V battery voltage
- **7.4V Li-ion Battery** – Power supply
- **Zero PCB** – For assembling the circuit neatly

---

## ✨ Features

- 🛞 **Adjustable Circle Radius** (`CIRCLE_RADIUS` in code)
- 🔄 **Real-time yaw feedback** control using MPU6050
- 🚀 **Smooth movement** with dynamic speed adjustment
- ⛔ **Automatic stop** after completing a full circle
- 🛠️ **Simple to build and modify**

---

## 🔌 Wiring Overview

- **MPU6050** connected to Arduino's I2C pins:
  - A4 → SDA
  - A5 → SCL
- **Motors** connected to PWM-capable pins for speed control:
  - D3, D6, D9, D11
- **Battery** connected through a **buck converter** to power Arduino and motors safely.
- **Common GND** shared between all components.

*(A simple wiring diagram will be uploaded soon!)*

---

## 🚀 Running the Project

1. Wire up the components as per the circuit diagram.
2. Upload the code to the Arduino UNO.
3. Power up the bot using the 7.4V battery.
4. Place it on a flat surface and watch it move!

You can easily adjust parameters like:
- Circle radius
- Base motor speed
- Yaw correction gain  
→ directly from the code to fine-tune behavior.

---

## 💻 Code Highlights

- **Yaw Integration**: Calculates yaw angle by integrating gyro readings.
- **Motor PWM Control**: Dynamically adjusts wheel speeds.
- **Simple P-Control**: Reduces yaw error without needing full PID tuning.
- **360° Detection**: Automatically stops after one full circle (optional).

---

## 🌟 Future Improvements

- Implement full **PID control** instead of only P-controller.
- Add **wheel encoders** for better speed feedback.
- Allow **dynamic circle radius** changes during motion.
- Add **wireless control** (Bluetooth / Wi-Fi).

---

## 🎥 Demo

*(Coming soon – planning to upload a demo video!)*

---

## 📝 Final Note

This project mainly explores **basic motion control using an IMU**, without needing expensive sensors or complicated localization algorithms.  
It’s simple, fun to build, and serves as a great starting point for learning **autonomous robot behaviors**!

---
