// Motor control pins
const int MOTOR_A1 = 10;
const int MOTOR_A2 = 11;
const int MOTOR_B1 = 5;
const int MOTOR_B2 = 6;

// Ultrasonic sensor pins
const int TRIG = 7;
const int ECHO = 9;

// Base motor speed
const int baseSpeed = 200;

// Line sensor setup
const int sensorPins[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };
const int numSensors = 8;
int sensorValues[8];

// Assign weights to each sensor for proportional control
int sensorWeights[8] = { -3, -2, -1, 0, 0, 1, 2, 3 };

// Thresholds for white and black
const int whiteThreshold = 600;
const int blackThreshold = 900;

// Proportional control constant
const float Kp = 30.0;

void setup() {
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  Serial.begin(9600);
}

// Function to measure distance using ultrasonic sensor
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  long duration = pulseIn(ECHO, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Set motor speeds (updated to allow negative speeds for reverse)
// When a speed is positive, the motor runs forward; negative values reverse it.
void setMotorSpeeds(int leftSpeed, int rightSpeed) {
 
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  // Left motor control
  if (leftSpeed >= 0) {
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, leftSpeed);
  } else {
    analogWrite(MOTOR_A1, -leftSpeed);
    analogWrite(MOTOR_A2, 0);
  }
  
  // Right motor control
  if (rightSpeed >= 0) {
    analogWrite(MOTOR_B1, rightSpeed);
    analogWrite(MOTOR_B2, 0);
  } else {
    analogWrite(MOTOR_B1, 0);
    analogWrite(MOTOR_B2, -rightSpeed);
  }
}

// Stop motors
void stopMotors() {
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, 0);
}

void loop() {
  // Check for obstacles first
  long distance = getDistance();
  if (distance > 0 && distance < 20) {
    stopMotors();
    Serial.println("Obstacle detected! Stopping...");
    delay(100);
    return;  // Skip rest of loop while obstacle is present
  }
  
  int weightedSum = 0;
  int activeSensors = 0;
  
  // Read sensors and compute weighted sum for line position
  for (int i = 0; i < numSensors; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    Serial.print(sensorValues[i]);
    Serial.print("\t");
    
    // Use sensor reading if it detects black (line)
    if (sensorValues[i] > blackThreshold) {
      weightedSum += sensorWeights[i];
      activeSensors++;
    }
  }
  Serial.println();

  // If no sensor detects the line, execute a recovery routine
  if (activeSensors == 0) {
    Serial.println("Line lost! Reversing and pivoting...");
    // Reverse briefly to try and relocate the line
    setMotorSpeeds(-baseSpeed, -baseSpeed);
    delay(200);
    // Pivot turn (for example, pivot left) to search for the line
    setMotorSpeeds(-baseSpeed, baseSpeed);
    delay(150);
    return;  // Skip the rest of the loop this cycle
  }

  // Normal line following using proportional control
  float error = (float)weightedSum / activeSensors;
  int correction = Kp * error;
  int leftMotorSpeed = baseSpeed - correction;
  int rightMotorSpeed = baseSpeed + correction;
  
  setMotorSpeeds(leftMotorSpeed, rightMotorSpeed);
  
  // Debugging output
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print("  Correction: ");
  Serial.print(correction);
  Serial.print("  Left Speed: ");
  Serial.print(leftMotorSpeed);
  Serial.print("  Right Speed: ");
  Serial.println(rightMotorSpeed);
  
  delay(50);
}
