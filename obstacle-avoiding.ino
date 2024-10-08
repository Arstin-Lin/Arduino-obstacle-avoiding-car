// 1. Library Inclusion
#include <Ultrasonic.h>

// 2. Ultrasonic Sensor Setup
Ultrasonic ultrasonic(12, 13); // (Trig PIN, Echo PIN)

// 3. Motor Control Pins

const byte LEFT1 = 8;  // IN1
const byte LEFT2 = 9;  // IN2
const byte LEFT_PWM = 10;

const byte RIGHT1 = 7;  // IN3
const byte RIGHT2 = 6;  // IN4
const byte RIGHT_PWM = 5;

// 4. Motor Speed Setup
byte motorSpeed = 130;

// 5. Movement Functions
void forward() {
  // Left motor: Forward
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);

  // Right motor: Forward (opposite wiring setup)
  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  analogWrite(RIGHT_PWM, motorSpeed);
}
void backward() {
  // Left motor: Backward
  digitalWrite(LEFT1, LOW);
  digitalWrite(LEFT2, HIGH);
  analogWrite(LEFT_PWM, motorSpeed);

  // Right motor: Backward
  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(RIGHT_PWM, motorSpeed);
}
void turnLeft() {
  analogWrite(LEFT_PWM, 0);  // Stop the left motor
  digitalWrite(RIGHT1, LOW);  // Turn the right motor
  digitalWrite(RIGHT2, HIGH);
  analogWrite(RIGHT_PWM, motorSpeed);
}
void turnRight() {
  digitalWrite(LEFT1, HIGH);  // Turn the left motor
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);

  analogWrite(RIGHT_PWM, 0);  // Stop the right motor
}
void stopMotor() {
  analogWrite(LEFT_PWM, 0);  // Stop left motor
  analogWrite(RIGHT_PWM, 0); // Stop right motor
}
// 6. Setup Function
void setup() {
  pinMode(LEFT1, OUTPUT);
  pinMode(LEFT2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT1, OUTPUT);
  pinMode(RIGHT2, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
}

// 7. Main Loop: Obstacle Avoidance Logic
void loop() {
  int dis = ultrasonic.read(); // Read distance from the ultrasonic sensor

  if (dis < 15) {
    turnRight();  // If obstacle is closer than 15 cm, turn right
    delay(200);   // Turn for 0.2 seconds
    stopMotor();  // Stop after turning
  } else {
    forward();    // Otherwise, keep moving forward
  }
}
