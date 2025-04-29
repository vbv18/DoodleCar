# 🤖 Circular Motion Bot using Arduino UNO, MPU6050, and N20 Motors

## 🧠 Introduction

This is a small robotics project where we built a bot that moves along a fixed circular path using basic components like an Arduino UNO, N20 motors, an MPU6050 sensor, and a custom Zero PCB.  
Instead of using encoders to track wheel rotation, the bot uses **yaw feedback** from the MPU6050 gyroscope to maintain a stable circular movement.

---

## ⚙️ How It Works

- The bot is programmed to follow a circle of a given radius (adjustable in the code **or via Bluetooth**).
- It uses the **yaw rate** (rotation speed) from the MPU6050 to correct motor speeds while moving.
- A simple **proportional controller (P-controller)** keeps adjusting the left and right motor speeds to stay on the desired path.
- Once the bot completes a full **360° rotation** (i.e., one full circle), it **automatically stops** (this behavior is configurable).
- **Bluetooth control (via HC-05)** allows you to send a new circle radius in real time.

---

## 🛠️ Hardware Used

- **Arduino UNO** – Main controller  
- **N20 Motors** – Small DC geared motors (with optional encoders, not used here)  
- **MPU6050** – 6-axis accelerometer and gyroscope  
- **HC-05 Bluetooth Module** – For setting circle radius remotely  
- **Buck Converter** – To step down 7.4V battery voltage  
- **7.4V Li-ion Battery** – Power supply  
- **Zero PCB** – For assembling the circuit neatly  

---

## ✨ Features

- 🛞 **Adjustable Circle Radius** (`CIRCLE_RADIUS` in code or via Bluetooth command)
- 🔄 **Real-time yaw feedback** control using MPU6050
- 📲 **Bluetooth control** to change circle radius on the fly
- 🚀 **Smooth movement** with dynamic speed adjustment
- ⛔ **Automatic stop** after completing a full circle
- 🛠️ **Simple to build and modify**

---

## 🔌 Wiring Overview

- **MPU6050** connected to Arduino's I2C pins:
  - A4 → SDA
  - A5 → SCL
- **Motors** connected to PWM-capable pins:
  - D3, D6, D9, D11
- **HC-05 Bluetooth Module**:
  - HC-05 TX → Arduino pin 7 (Software RX)
  - HC-05 RX → Arduino pin 8 (Software TX, with voltage divider)
- **Battery** connected through a **buck converter** to power Arduino and motors safely.
- **Common GND** shared between all components.

---

## 🚀 Running the Project

1. Connect all components as per the wiring diagram.
2. Upload the code to the Arduino UNO.
3. Power up the bot using the 7.4V battery.
4. Place it on a flat surface and let it move!

✅ You can:
- Adjust circle radius in code **or**
- Send new radius via Bluetooth app (like Serial Bluetooth Terminal) → send values like `0.6` followed by newline.

---

### Other Logic:
- **Yaw Integration**: Tracks current yaw by integrating gyro values
- **P-Control**: Adjusts wheel speed based on yaw error
- **Dynamic PWM Control**: Smooth turning
- **360° Detection**: Stops automatically after full circle (optional)

---

## 🌟 Future Improvements

- Add full **PID control** for smoother path correction
- Integrate **wheel encoders** for better feedback
- Enable **radius control via mobile app slider**
- Add **Wi-Fi or BLE support** for advanced wireless control

---

## 🎥 Demo

*(Coming soon – demo video will be uploaded!)*

---

## 📝 Final Note

This project was an experiment in **IMU-based motion control**.
It’s budget-friendly, easy to build, and open-ended for future upgrades. A great stepping stone toward more advanced autonomous bots!

