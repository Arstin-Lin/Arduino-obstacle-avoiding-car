// Left motor control
const byte LEFT1 = 8;  // IN1
const byte LEFT2 = 9;  // IN2
const byte LEFT_PWM = 10;  // PWM control for left motor speed

// Right motor control
const byte RIGHT1 = 7;  // IN3
const byte RIGHT2 = 6;  // IN4
const byte RIGHT_PWM = 5;  // PWM control for right motor speed

// Motor speed setting
byte motorSpeed = 130;

// Ultrasonic sensor setup
const byte TRIG_PIN = 4;  // Ultrasonic sensor TRIG pin
const byte ECHO_PIN = 3;  // Ultrasonic sensor ECHO pin
const int OBSTACLE_DISTANCE_THRESHOLD = 15;  // Distance threshold for obstacles (in cm)

void setup() {
  // Motor control pin configurations
  pinMode(LEFT1, OUTPUT);
  pinMode(LEFT2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT1, OUTPUT);
  pinMode(RIGHT2, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  
  // Line-following infrared sensor pin configurations
  pinMode(12, INPUT); // Right infrared sensor
  pinMode(13, INPUT); // Left infrared sensor
  
  // Ultrasonic sensor pin configurations
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize the serial monitor
  Serial.begin(9600);
  Serial.println("Robot initialized. Waiting for actions...");

  stopMotor(); // Stop the motors during initialization
}

// Measure obstacle distance
int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;  // Convert time to distance in cm
  return distance;
}

// Move forward
void forward() {
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);

  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(RIGHT_PWM, motorSpeed);
}

// Turn left
void turnLeft() {
  analogWrite(LEFT_PWM, motorSpeed / 2);  // Reduce left wheel speed
  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(RIGHT_PWM, motorSpeed);
}

// Turn right
void turnRight() {
  analogWrite(RIGHT_PWM, motorSpeed / 2);  // Reduce right wheel speed
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);
}

// Stop motors
void stopMotor() {
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}

void loop() {
  // Measure the distance of obstacles ahead
  int distance = measureDistance();

  // Print the measured distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an obstacle is detected, turn right
  if (distance < OBSTACLE_DISTANCE_THRESHOLD) {
    Serial.println("Obstacle detected! Turning right...");
    turnRight();
    return;
  }

  // Line-following logic
  if (digitalRead(12) == 0 && digitalRead(13) == 1) {  // Right infrared sensor detects black, left detects white
    Serial.println("Line detected on the right. Turning right...");
    turnRight();
  } else if (digitalRead(13) == 0 && digitalRead(12) == 1) {  // Left infrared sensor detects black, right detects white
    Serial.println("Line detected on the left. Turning left...");
    turnLeft();
  } else if (digitalRead(12) == 1 && digitalRead(13) == 1) {  // Both sensors detect black
    Serial.println("Line detected ahead. Moving forward...");
    forward();
  } else {  // Both sensors detect white
    Serial.println("Line lost. Stopping...");
    stopMotor();
  }

  delay(80);  // Small delay to avoid rapid state switching
}
