# Smart Parking System

An IoT-based automated parking management system using Arduino that detects car presence in parking slots and automatically controls entrance gates with real-time status display.

![Smart Parking](https://github.com/user-attachments/assets/276ff9c4-140c-4682-891b-641d0869e092)

## 🚗 Project Overview

The Smart Parking System is designed to solve common parking management issues by providing automated monitoring and control. The system uses ultrasonic sensors to detect vehicle presence, servo motors for gate control, and an LCD display for real-time status updates.

## ✨ Features

- **Automated Gate Control**: Entrance gate opens/closes automatically when vehicles approach
- **Real-time Slot Monitoring**: Continuous monitoring of parking slot occupancy
- **LCD Status Display**: Live display showing slot availability (Occupied/Empty)
- **Cost-effective Solution**: Uses affordable Arduino components
- **Scalable Design**: Easy to expand for more parking slots
- **Responsive Detection**: Quick sensor response with customizable thresholds

## 🛠️ Hardware Components

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Main microcontroller |
| Ultrasonic Sensors (3-pin or HC-SR04) | 3 | Distance measurement |
| LCD Display 16x2 with I2C | 1 | Status display |
| Servo Motors | 2 | Gate control mechanism |
| Connecting Wires | Multiple | Circuit connections |
| Breadboard/PCB | 1 | Circuit assembly |
| 5V Power Supply | 1 | System power |

## 📋 Software Requirements

- **Programming Language**: C/C++ (Arduino)
- **Arduino IDE** (version 1.8.0 or higher)
- **Main Code File**: `smart_parking_system.ino`
- **Required Libraries**:
  - `Wire.h` - I2C communication
  - `LiquidCrystal_I2C.h` - LCD control
  - `Servo.h` - Servo motor control

## 🔌 Circuit Connections

### Pin Configuration

| Component | Arduino Pin | Connection |
|-----------|-------------|------------|
| Slot 1 Sensor | Pin 4 | Signal pin |
| Slot 2 Sensor | Pin 2 | Signal pin |
| Gate Sensor | Pin 10 | Signal pin |
| Left Servo | Pin 8 | Control pin |
| Right Servo | Pin 9 | Control pin |
| LCD I2C | A4 (SDA), A5 (SCL) | I2C communication |

### Wiring Diagram

```
Ultrasonic Sensors:
VCC → 5V
GND → GND
Signal → Digital Pins (2, 4, 10)

LCD I2C:
VCC → 5V
GND → GND
SDA → A4
SCL → A5

Servo Motors:
Red → 5V
Brown → GND
Orange → Digital Pins (8, 9)
```

## ⚡ Power Requirements

- **Arduino Uno**: 5V, 500mA
- **Servo Motors**: 5V, 1A each
- **Sensors & LCD**: 5V, 100mA total
- **Recommended Power Supply**: 5V, 3A

## 🚀 Installation & Setup

### 1. Hardware Assembly
1. Connect all components according to the wiring diagram
2. Ensure proper power connections
3. Mount sensors at appropriate positions
4. Test all connections before powering on

### 2. Software Installation
1. Install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install required libraries:
   ```
   Sketch → Include Library → Manage Libraries
   Search and install: LiquidCrystal I2C
   ```
3. Download the `smart_parking_system.ino` file
4. Open the file in Arduino IDE
5. Upload the code to Arduino Uno

### 3. Configuration
1. Adjust threshold values in code if needed:
   ```cpp
   const int parkingDetectionThreshold = 30;  // cm
   const int gateDetectionThreshold = 150;    // cm
   ```
2. Calibrate sensor positions for optimal detection
3. Test system functionality

## 💻 Code Structure

### Main Functions

#### `readDistance(int pin)`
Reads distance from ultrasonic sensor using time-of-flight principle.

```cpp
long readDistance(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  long duration = pulseIn(pin, HIGH);
  return duration * 0.034 / 2;
}
```

#### Main Loop Logic
1. Read distances from all sensors
2. Process data to determine occupancy
3. Update LCD display
4. Control gate servos
5. Repeat every 500ms

## 🎯 How It Works

1. **Initialization**: System displays "Smart Parking" welcome message
2. **Continuous Monitoring**: Sensors measure distances every 500ms
3. **Slot Detection**: 
   - Distance < 30cm = Slot Occupied
   - Distance ≥ 30cm = Slot Empty
4. **Gate Control**:
   - Car detected (< 150cm) = Gate opens (90°)
   - No car detected = Gate closes (0°)
5. **Display Update**: LCD shows real-time slot status

## 📱 Applications

### Real-World Use Cases
- **Shopping Malls**: Customer parking management
- **Office Buildings**: Employee parking optimization
- **Hospitals**: Patient/visitor parking assistance
- **Universities**: Student parking management
- **Airports**: Long-term parking solutions
- **Residential Complexes**: Apartment parking systems

### Benefits
- ✅ Reduced waiting time
- ✅ Efficient space utilization
- ✅ Cost-effective automation
- ✅ Easy maintenance
- ✅ Scalable design
- ✅ Real-time monitoring

## 🔮 Future Enhancements

- **📱 Mobile App Integration**: Real-time notifications and remote monitoring
- **💳 Payment System**: Automated billing and payment processing
- **🔍 License Plate Recognition**: Enhanced security features
- **☁️ Cloud Connectivity**: Remote monitoring and data analytics
- **🌞 Solar Power**: Eco-friendly operation
- **🏢 Multi-level Support**: Expansion for multiple floors
- **📅 Reservation System**: Pre-booking capabilities

## 🧪 Testing & Demonstration

### Demo Steps
1. Power on the system
2. Observe LCD showing empty slots
3. Place object in Slot 1 → LCD shows "Occupied"
4. Place object in Slot 2 → LCD shows "Occupied"
5. Approach gate sensor → Gate opens automatically
6. Move away from gate → Gate closes automatically

### Expected Results
- ✅ Real-time status updates
- ✅ Smooth gate operation
- ✅ Clear LCD display
- ✅ Responsive sensor detection

## 🔧 Troubleshooting

### Common Issues

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LCD not displaying | Wiring issue or wrong I2C address | Check connections, try address 0x3F |
| Servo not moving | Power supply insufficient | Use external 5V power supply |
| Inaccurate readings | Sensor positioning | Adjust sensor angle and height |
| Gate not responding | Threshold values | Modify detection thresholds in code |

### Debugging Tips
1. Use Serial Monitor to check sensor readings
2. Verify all connections with multimeter
3. Test components individually
4. Check power supply voltage

## 📊 Performance Specifications

- **Detection Range**: 2cm - 400cm
- **Detection Accuracy**: ±1cm
- **Response Time**: <1 second
- **Operating Voltage**: 5V DC
- **Operating Temperature**: -10°C to +50°C
- **Update Frequency**: 2Hz (every 500ms)

## 💰 Cost Estimation

| Component | Estimated Cost (USD) |
|-----------|---------------------|
| Arduino Uno | $15 - $25 |
| Ultrasonic Sensors (3x) | $6 - $15 |
| LCD + I2C Module | $5 - $10 |
| Servo Motors (2x) | $8 - $15 |
| Miscellaneous | $5 - $10 |
| **Total** | **$39 - $75** |

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.

### Development Setup
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 👨‍💻 Author

**Safwan Rahimi**
- Email: tokrimauhitam@gmail.com
- GitHub: Safwan3528

## 🙏 Acknowledgments

- Arduino community for excellent documentation
- Open source library contributors
- Dr. Asiah for guidance in IoT development

## 📞 Support

If you encounter any issues or have questions:
1. Check the troubleshooting section
2. Search existing issues
3. Create a new issue with detailed description
4. Contact the author directly

---

**⭐ If you found this project helpful, please consider giving it a star!**

## 📚 Additional Resources

- [Arduino Official Documentation](https://docs.arduino.cc/)
- [Ultrasonic Sensor Guide](https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380)
- [Servo Motor Tutorial](https://docs.arduino.cc/learn/electronics/servo-motors)
- [I2C LCD Setup Guide](https://create.arduino.cc/projecthub/najad/interfacing-lcd1602-with-arduino-764ec4)
