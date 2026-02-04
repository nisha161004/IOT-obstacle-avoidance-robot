// ULTRASONIC OBSTACLE AVOIDING CAR BASED ON ARDUINO
// ---------------------------------------------------
// Required Libraries:
// 1. Adafruit Motor Shield library (NOT V2)
// 2. NewPing Library

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// ---------------- Pin Configuration ----------------
#define TRIG_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 200
#define SAFE_DISTANCE 30   // Car stops when obstacle < 30 cm

// ---------------- Motor and Sensor Setup ----------------
NewPing radar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Servo myservo;

int distance = 100;
int pos = 0;

// ---------------- Setup ----------------
void setup() {
  Serial.begin(9600);

  // Motor speed setup
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  // Servo setup
  myservo.attach(9);
  myservo.write(100);
  delay(1000);

  // Initial distance reading
  distance = checkDistance();
}

// ---------------- Main Loop ----------------
void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(40);

  // If obstacle detected within 30 cm, stop and decide what to do
  if (distance <= SAFE_DISTANCE) {
    stopMovement();
    delay(100);

    // Move slightly backward for clearance
    moveBackward();
    delay(400);
    stopMovement();
    delay(200);

    // Check right and left distances
    distanceRight = checkRightDistance();
    delay(200);
    distanceLeft = checkLeftDistance();
    delay(200);

    // If both sides blocked, perform a 180° turn
    if (distanceRight < SAFE_DISTANCE && distanceLeft < SAFE_DISTANCE) {
      turnAround180();
    } 
    else if (distanceRight > distanceLeft) {
      turnRight180();
    } 
    else {
      turnLeft180();
    }
  } 
  else {
    moveForward();
  }

  // Update distance reading
  distance = checkDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

// ---------------- Distance Checking ----------------
int checkRightDistance() {
  myservo.write(30); // Look right
  delay(400);
  int distance = checkDistance();
  delay(100);
  myservo.write(100); // Reset to center
  delay(400);
  return distance;
}

int checkLeftDistance() {
  myservo.write(170); // Look left
  delay(400);
  int distance = checkDistance();
  delay(100);
  myservo.write(100); // Reset to center
  delay(400);
  return distance;
}

int checkDistance() {
  long sum = 0;
  int samples = 5; // Take 5 readings to smooth noise
  for (int i = 0; i < samples; i++) {
    int cm = radar.ping_cm();
    if (cm == 0 || cm > MAX_DISTANCE) cm = MAX_DISTANCE;
    sum += cm;
    delay(30);
  }
  return sum / samples;
}

// ---------------- Movement Functions ----------------
void stopMovement() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// ---------------- Turning Functions ----------------

// Turn approximately 180° Left
void turnLeft180() {
  Serial.println("Turning Left 180°");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(1400);  // Adjust this delay for your car (test for perfect 180°)
  stopMovement();
  delay(200);
}

// Turn approximately 180° Right
void turnRight180() {
  Serial.println("Turning Right 180°");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1400);  // Adjust this delay for your car (test for perfect 180°)
  stopMovement();
  delay(200);
}

// Full turn-around (U-turn) when both sides blocked
void turnAround180() {
  Serial.println("Both sides blocked — Turning Around 180°");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1500);  // Slightly longer for full U-turn
  stopMovement();
  delay(200);
}
