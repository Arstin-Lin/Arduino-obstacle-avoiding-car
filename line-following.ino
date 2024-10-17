// Left motor control settings
const byte LEFT1 = 8;  // IN1
const byte LEFT2 = 9;  // IN2
const byte LEFT_PWM = 10;

// Right motor control settings
const byte RIGHT1 = 7;  // IN3
const byte RIGHT2 = 6;  // IN4
const byte RIGHT_PWM = 5;

// Set PWM output value (represents the speed of the car)
byte motorSpeed = 130;

void forward() {  // Move forward
  // Left wheel
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);
  
  // Right wheel. Because the motor installation direction on the car is opposite for the left and right wheels, the motor settings for the other wheel need to be opposite, so that both wheels can work together.
  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  analogWrite(RIGHT_PWM, motorSpeed);
}

void backward() { // Move backward
  digitalWrite(LEFT1, LOW);
  digitalWrite(LEFT2, HIGH);
  analogWrite(LEFT_PWM, motorSpeed);

  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(RIGHT_PWM, motorSpeed);
}

void turnLeft() { // Turn left
  // Stop the left wheel, move the right wheel (left wheel speed set to 0)
  analogWrite(LEFT_PWM, 0);

  digitalWrite(RIGHT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  analogWrite(RIGHT_PWM, motorSpeed);
}

void turnRight() {  // Turn right
  // Stop the right wheel, move the left wheel (right wheel speed set to 0)
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);
  
  analogWrite(RIGHT_PWM, 0);
}

void stopMotor() {  // Stop, both wheels' speed set to 0
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}

void setup() {
  // Set the mode for each PIN
  pinMode(LEFT1, OUTPUT);
  pinMode(LEFT2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT1, OUTPUT);
  pinMode(RIGHT2, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  
  pinMode(12, INPUT); // Right infrared sensor
  pinMode(13, INPUT); // Left infrared sensor

  //forward();  // Initially commented out; used for testing forward movement
}

void loop() {
  // This simple example makes the car follow a black line. If the right sensor detects white, turn slightly left; if the left sensor detects white, turn slightly right.
  
  if(digitalRead(13) == 0) {  // Left sensor detects white
      turnRight();
      delay(80);
  } else if(digitalRead(12) == 0) {  // Right sensor detects white
      turnLeft();
      delay(80);
  } else {
      forward();  // Keep moving forward if both sensors detect black
  }
}
