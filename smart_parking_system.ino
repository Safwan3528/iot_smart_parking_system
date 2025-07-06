#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD I2C initialization (address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo motor objects
Servo servoLeft;
Servo servoRight;

// Pin definitions for ultrasonic sensors (3-pin)
const int slot1Pin = 4;    // Parking slot 1 sensor
const int slot2Pin = 2;    // Parking slot 2 sensor
const int gateSensorPin = 10;  // Gate entrance sensor

// Pin definitions for servo motors
const int servoLeftPin = 8;   // Left servo motor
const int servoRightPin = 9;  // Right servo motor

// Threshold distances for car detection (in centimeters)
const int parkingDetectionThreshold = 30;  // Distance to detect car in parking slot
const int gateDetectionThreshold = 150;    // Distance to detect car at gate

/**
 * Function to read distance from ultrasonic sensor
 * Uses time-of-flight principle to calculate distance
 * @param pin: The pin number connected to the ultrasonic sensor
 * @return: Distance in centimeters
 */
long readDistance(int pin) {
  // Set pin as output and send trigger pulse
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  
  // Set pin as input and read echo pulse
  pinMode(pin, INPUT);
  long duration = pulseIn(pin, HIGH);
  
  // Calculate distance using speed of sound (0.034 cm/microsecond)
  return duration * 0.034 / 2;
}

/**
 * Setup function - runs once when Arduino starts
 * Initializes all components and displays welcome message
 */
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Attach servo motors to their respective pins
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize LCD display
  lcd.begin(16, 2);
  lcd.backlight();
  
  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print(" Smart Parking ");
  lcd.setCursor(0, 1);
  lcd.print("   System V1.0  ");
  
  // Show welcome message for 3 seconds
  delay(3000);
  
  // Clear display for main operation
  lcd.clear();
  
  // Initialize gate to closed position
  servoLeft.write(0);
  servoRight.write(0);
  
  // Debug message
  Serial.println("Smart Parking System Initialized");
  Serial.println("Parking Threshold: " + String(parkingDetectionThreshold) + "cm");
  Serial.println("Gate Threshold: " + String(gateDetectionThreshold) + "cm");
}

/**
 * Main loop function - runs continuously
 * Monitors sensors, updates display, and controls gate
 */
void loop() {
  // Read distances from all three sensors
  long dist1 = readDistance(slot1Pin);
  long dist2 = readDistance(slot2Pin);
  long gateDist = readDistance(gateSensorPin);
  
  // Determine slot occupancy based on distance thresholds
  bool slot1Occupied = dist1 < parkingDetectionThreshold;
  bool slot2Occupied = dist2 < parkingDetectionThreshold;
  bool hasCarAtGate = gateDist < gateDetectionThreshold;
  
  // Debug output to Serial Monitor
  Serial.println("=== Sensor Readings ===");
  Serial.println("Slot 1: " + String(dist1) + "cm - " + (slot1Occupied ? "OCCUPIED" : "EMPTY"));
  Serial.println("Slot 2: " + String(dist2) + "cm - " + (slot2Occupied ? "OCCUPIED" : "EMPTY"));
  Serial.println("Gate: " + String(gateDist) + "cm - " + (hasCarAtGate ? "CAR DETECTED" : "NO CAR"));
  Serial.println();
  
  // Update LCD display with current slot status
  lcd.clear();
  
  // Display Slot 1 status on first line
  lcd.setCursor(0, 0);
  lcd.print("Slot1: ");
  if (slot1Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Empty   ");
  }
  
  // Display Slot 2 status on second line
  lcd.setCursor(0, 1);
  lcd.print("Slot2: ");
  if (slot2Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Empty   ");
  }
  
  // Control servo gate based on car presence at entrance
  if (hasCarAtGate) {
    // Open gate - both servos move to 90 degrees
    servoLeft.write(90);
    servoRight.write(90);
    Serial.println(">>> GATE OPENED <<<");
  } else {
    // Close gate - both servos move to 0 degrees
    servoLeft.write(0);
    servoRight.write(0);
    Serial.println(">>> GATE CLOSED <<<");
  }
  
  // Small delay before next iteration (500ms = 2Hz update rate)
  delay(500);
}

/**
 * Additional utility functions (optional)
 */

/**
 * Function to test all components individually
 * Useful for debugging and system verification
 */
void testComponents() {
  Serial.println("=== Component Test Mode ===");
  
  // Test LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Testing LCD...");
  delay(2000);
  
  // Test Servos
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Testing Servos..");
  servoLeft.write(90);
  servoRight.write(90);
  delay(2000);
  servoLeft.write(0);
  servoRight.write(0);
  delay(2000);
  
  // Test Sensors
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Testing Sensors.");
  for (int i = 0; i < 5; i++) {
    Serial.println("Slot1: " + String(readDistance(slot1Pin)) + "cm");
    Serial.println("Slot2: " + String(readDistance(slot2Pin)) + "cm");
    Serial.println("Gate: " + String(readDistance(gateSensorPin)) + "cm");
    delay(1000);
  }
  
  Serial.println("=== Component Test Complete ===");
}

/**
 * Function to calibrate sensor thresholds
 * Call this function to help set optimal detection distances
 */
void calibrateSensors() {
  Serial.println("=== Sensor Calibration Mode ===");
  Serial.println("Place objects at various distances and note readings:");
  
  for (int i = 0; i < 20; i++) {
    Serial.println("Reading " + String(i + 1) + ":");
    Serial.println("  Slot1: " + String(readDistance(slot1Pin)) + "cm");
    Serial.println("  Slot2: " + String(readDistance(slot2Pin)) + "cm");
    Serial.println("  Gate: " + String(readDistance(gateSensorPin)) + "cm");
    Serial.println();
    delay(2000);
  }
  
  Serial.println("=== Calibration Complete ===");
}
