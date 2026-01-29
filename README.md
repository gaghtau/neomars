NeoMars — Autonomous Planetary Rover Prototype
NeoMars is an autonomous planetary rover prototype inspired by robotic exploration systems used in Mars missions.
The project focuses on autonomous navigation, environmental sensing, and real-time data visualization, simulating the core functionalities of a planetary exploration rover.
NeoMars is designed as a modular research and educational platform that can be extended with additional scientific instruments and communication systems.
________________________________________________________________________________________________________________________________________

Mission Concept
1)The primary mission of NeoMars is to:
2)Navigate autonomously in an unknown environment
3)Detect and avoid obstacles using active distance sensing
4)Collect environmental data similar to planetary surface measurements
5)Visualize sensor data in real time for analysis and debugging
________________________________________________________________________________________________________________________________________

System Architecture
* NeoMars consists of:
1)Autonomous mobility system (DC motors + motor driver)
2)Sensor mast with ultrasonic scanning and servo control
3)Environmental monitoring module (temperature, humidity, air quality)
4)Vision system (ESP32-CAM)
5)Dual display telemetry system
6)Independent power and energy management system
________________________________________________________________________________________________________________________________________

* Hardware Components
1)Control Unit
2)Arduino UNO
3)ESP32-CAM  (vision and wireless communication)
* Navigation & Environment Sensors
3)HC-SR04 Ultrasonic Distance Sensor (obstacle detection)
4)DHT11 Temperature & Humidity Sensor
5)MQ-135 Air Quality Sensor
* Mobility & Actuation
6)2 × DC Motors
7)L298N Motor Driver
8)2 × SG90 Servo Motors (sensor scanning and orientation)
* Visualization
9)OLED 128×64 (SSD1306, I2C) — radar visualization
10)LCD 16×2 (I2C) — telemetry data
* Power
1)Rechargeable battery pack
2)10,000 mAh power bank
3)Solar panel
________________________________________________________________________________________________________________________________________

| Component        | Arduino Pin        |
| ---------------- | ------------------ |
| L298N IN1        | D8                 |
| L298N IN2        | D9                 |
| L298N IN3        | D10                |
| L298N IN4        | D11                |
| HC-SR04 TRIG     | D2                 |
| HC-SR04 ECHO     | D3                 |
| Servo Motor 1    | D4                 |
| Servo Motor 2    | D7                 |
| DHT11            | D13                |
| MQ-135           | A0                 |
| OLED / LCD (I2C) | A4 (SDA), A5 (SCL) |
________________________________________________________________________________________________________________________________________

Autonomous Navigation Logic

1)The rover moves forward autonomously.
2)Distance measurements are continuously performed.
3)If an obstacle is detected below the defined safety threshold:
* The rover stops
* Performs a radar-style scan using a servo-mounted sensor
* Determines a safer direction of travel
* Resumes autonomous movement
________________________________________________________________________________________________________________________________________

Telemetry & Visualization
* OLED Display
1)Radar-style obstacle detection visualization
2)Sensor scanning angle
* LCD Display
1)Distance to obstacle
2)Servo angle
3)Temperature
4)Humidity
5)Air quality index (relative)
* Serial Output
1)Distance measurements in centimeters
________________________________________________________________________________________________________________________________________

Vision & Imaging System
NeoMars is equipped with an onboard camera module for visual monitoring and future computer vision experiments.

* Camera Module - ESP32-CAM
1)Provides real-time image capture
2)Can stream video over Wi-Fi
3)Enables remote observation and data collection
4)Designed for future integration of object detection and visual navigation
* The camera is mounted on a servo-driven platform, allowing directional control similar to a rover camera mast.
________________________________________________________________________________________________________________________________________

* Power System
NeoMars is designed as a semi-autonomous mobile platform with independent power supply, simulating real planetary rover energy systems.
1)Power Components
2)Rechargeable batteries
3)Power bank (10,000 mAh)
4)Solar panel (auxiliary power source)
5)Power Architecture
6)The power bank supplies stable voltage to the control electronics and sensors
7)DC motors are powered through the L298N motor driver
8)The solar panel is intended for:
9)Battery recharging
10)Extending mission duration
11)Demonstrating renewable energy usage in robotic systems
12)This configuration allows the rover to operate for extended periods without external power sources.
________________________________________________________________________________________________________________________________________

* Technical Note
NeoMars is a prototype-class autonomous rover inspired by real Mars exploration missions.
All subsystems are designed with modularity in mind, allowing further expansion and experimentation.


<img width="450" height="315" alt="image" src="https://github.com/user-attachments/assets/a4ac22e1-22e3-4814-a64c-98d5aa36a296" />
<img width="450" height="315" alt="image" src="https://github.com/user-attachments/assets/2d716a8e-6fc4-4fbf-a658-dceb194d3b04" />


<br>

<img width="250" height="425" alt="image" src="https://github.com/user-attachments/assets/720ad911-84ab-43cf-8e80-458d00367794" />
<img width="250" height="425" alt="image" src="https://github.com/user-attachments/assets/4abd9c5c-4075-4e73-820d-8d033f10dfff" />
