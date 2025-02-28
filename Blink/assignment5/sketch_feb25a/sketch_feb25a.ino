// Motor control pins
const int MOTOR_A1 = 10;  // Left motor control
const int MOTOR_A2 = 11;
const int MOTOR_B1 = 5;   // Right motor control
const int MOTOR_B2 = 6;

// Ultrasonic sensor pins (for obstacle detection, optional)
const int TRIG = 7;
const int ECHO = 9;

// Base motor speeds (0–255)
const int baseSpeed = 200;      // Base speed for both motors
const int MOTOR_A_SPEED = 230;  // (Not used in this example)
const int MOTOR_B_SPEED = 217;  // (Not used in this example)
const int ROTATION_SPEED = 200; // (Not used in this example)


// ----- Line Sensor Setup -----
const int sensorPins[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };
const int numSensors = 8;
int sensorValues[8];  // To hold analog readings

// Assign weights to each sensor for proportional control
int sensorWeights[8] = { -3, -2, -1, 0, 0, 1, 2, 3 };

// Define thresholds for white and black
const int whiteThreshold [] = {500,600}; // Values below this mean the sensor is on white
const int blackThreshold [] = {900,1050}; // Values above this mean the sensor is on black

// Proportional control constant
const int Kp = 60;

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

// Set motor speeds
void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  if (leftSpeed > 0) {
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, leftSpeed);
  } else {
    analogWrite(MOTOR_A1, -leftSpeed);
    analogWrite(MOTOR_A2, 0);
  }

  if (rightSpeed > 0) {
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
  long weightedSum = 0;
  int activeSensors = 0;
  
  for (int i = 0; i < numSensors; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    
    // Print sensor values for debugging
    Serial.print(sensorValues[i]);
    Serial.print("\t");

    // If sensor detects black, use it for calculation
   if (sensorValues[i] >= blackThreshold[0] && sensorValues[i] <= blackThreshold[1])
    {
    weightedSum += sensorWeights[i];
    activeSensors++;
    }
  }
  Serial.println();

  // Calculate error
  int error = 0;
  if (activeSensors > 0) {
    error = weightedSum;
  }

  // Compute correction using proportional control
  int correction = Kp * error;

  // Adjust left and right motor speeds based on error correction
  int leftMotorSpeed = baseSpeed - correction;
  int rightMotorSpeed = baseSpeed + correction;

  // Constrain motor speeds within valid range (0-255)
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

  // Check for obstacles
  long distance = getDistance();
  if (distance > 0 && distance < 20) {
    stopMotors();
    Serial.println("Obstacle detected! Stopping...");
  } else {
    setMotorSpeeds(leftMotorSpeed, rightMotorSpeed);
  }

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
