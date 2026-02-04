**IoT Based Obstacle Avoidance Autonomous Vehicle**

   **Project Overview**
   
This project demonstrates an **IoT-based obstacle avoidance autonomous vehicle** using **Arduino**.  
The robot detects obstacles using an **HC-SR04 ultrasonic sensor** and autonomously changes its direction to avoid collisions.  
It also supports **Bluetooth control** via an Android application for manual operation.

  **Objectives**
  
- Design an autonomous vehicle capable of avoiding obstacles
- Use ultrasonic sensing for distance measurement
- Enable wireless control using Bluetooth
- Implement motor control using a motor driver module

**Hardware Components**
- Arduino Uno / R3 / R4  
- HC-SR04 Ultrasonic Sensor  
- Servo Motor (SG90)  
- L293D Motor Driver Shield / L298N Module  
- DC Motors with Wheels  
- Robot Chassis  
- Battery Pack  
- Bluetooth Module (HC-05)  
- Jumper Wires  
- Soldering Kit  

**Software Tools & Libraries**
- Arduino IDE  
- AF Motor Library  
- Servo Library (built-in)  
- Bluetooth Terminal App (Android)

**Working Principle**
1. The ultrasonic sensor continuously measures distance ahead of the robot.
2. If an obstacle is detected within a predefined range:
   - The robot stops
   - The servo rotates the sensor to scan left and right
   - The robot chooses the path with maximum clearance
3. Motors are controlled via the motor driver to change direction.
4. Bluetooth module allows manual override and control via mobile app.

**Circuit Diagram**
 circuit diagram is availble in the `circuit_diagram/` folder.

**How to Run the Project**
1. Install **Arduino IDE**
2. Connect Arduino board to your system
3. Install required libraries:
   - AF Motor Library
   - Servo Library
4. Open `obstacle_avoidance_robot.ino`
5. Select correct **Board** and **COM Port**
6. Upload the code to Arduino
7. Power the robot using a battery pack
8. Control via Bluetooth app 

**Project Images**
Images of the robot are available in the `images/` folder.

**Future Enhancements**
- Add GPS-based navigation
- Integrate camera for vision-based obstacle detection
- Implement mobile app UI
- Add IoT cloud monitoring


**Nisha Shankar**  
CSE department / ACS college of engineering


