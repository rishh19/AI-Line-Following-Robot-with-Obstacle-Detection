#  AI-Driven Autonomous Line Following Robot with Obstacle Avoidance

##  Project Overview

This project presents an autonomous robot capable of following a predefined path and avoiding obstacles using sensor-based decision making. The system integrates line detection and obstacle avoidance to achieve intelligent navigation in real-time environments.

---

##  Components Used

* Arduino Uno
* L298N Motor Driver Module
* HC-SR04 Ultrasonic Sensor
* TCRT5000 IR Sensors (2 units)
* SG90 Servo Motor
* 4 DC Geared Motors
* 4WD Robot Chassis
* 18650 Battery Pack
* Jumper Wires and Connectors

---

##  Features

* Line following using IR sensors
* Real-time obstacle detection
* Servo-based obstacle scanning (left & right)
* Intelligent path decision making
* Autonomous navigation without human intervention

---

##  Working Principle

The robot continuously reads input from IR sensors to detect the line path and uses an ultrasonic sensor to measure the distance of obstacles. When an obstacle is detected within a threshold distance, the robot stops and scans both directions using a servo-mounted sensor. It then chooses the direction with more space and continues movement while attempting to return to the original path.

---

##  Hardware Connections

### Line Sensors

* Left Sensor → A0
* Right Sensor → A1

### Ultrasonic Sensor

* Echo → A2
* Trigger → A3

### Servo Motor

* Signal Pin → A5

### Motor Driver (L298N)

* ENA → D10
* IN1 → D9
* IN2 → D8
* IN3 → D7
* IN4 → D6
* ENB → D5

---

##  Project Structure

```
AI-Line-Following-Robot/
│
├── Code/
│   └── Robot_final.ino
│
├── Report/
│   └── Final_Report.pdf
│
├── Images/
│   ├── block_diagram.png
│   ├── circuit_diagram.png
│   └── prototype.jpg
│
└── README.md
```

---

##  System Workflow

1. Read line sensors
2. Detect line position
3. Check for obstacle using ultrasonic sensor
4. If obstacle detected:

   * Stop robot
   * Scan left and right using servo
   * Choose direction with more space
5. Move and attempt to return to line
6. Repeat continuously

---

## Output

The robot successfully follows a predefined path and avoids obstacles dynamically. It demonstrates stable movement, accurate sensing, and reliable decision-making using embedded control logic.

---

##  Future Scope

* Implementation of PID control for smoother motion
* Integration of Bluetooth/Wi-Fi control
* Camera-based line detection
* AI-based obstacle recognition
* Battery monitoring system
* Advanced navigation and mapping

---

##  Authors

* ISHAN CHOWDHURY 2305132
* PRIYANSHU SEKHAR BHUYAN 2305148
* RISHAV KUMAR SHRIVASTAVA 2305151
* ROSHAN PANDA 2305152
* SHIBANG MAITY 2305161

---

## 📜 License

This project is developed for academic purposes under KIIT Deemed to be University.
