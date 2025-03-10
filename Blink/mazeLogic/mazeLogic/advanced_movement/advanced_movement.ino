// Motor control pins
const int MOTOR_A1 = 10;  // Left motor control
const int MOTOR_A2 = 11;
const int MOTOR_B1 = 5;   // Right motor control
const int MOTOR_B2 = 6;

// Motor speeds
const int MOTOR_A_SPEED = 250;
const int MOTOR_B_SPEED = 237;
const int ROTATION_SPEED = 180;

// Timing variables
unsigned long previousMillis = 0;
int movementInterval = 4000; // Variable for movement duration
int movementState = 0; // 0: Forward, 1: Backward, 2: Turn Left, 3: Turn Right

void setup() {
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
}

void loop() {
  millisTimer(movementInterval);
}

void millisTimer(int interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    void (*movementFunctions[])() = {moveForward, moveBackward, turnLeft, turnRight};
    movementFunctions[movementState]();
    
    movementState = (movementState + 1) % 4; // Cycle through movement states
  }
}

void moveForward() {
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, MOTOR_A_SPEED);
    analogWrite(MOTOR_B1, MOTOR_B_SPEED);
    analogWrite(MOTOR_B2, 0);
}

void moveBackward() {
    analogWrite(MOTOR_A1, MOTOR_A_SPEED);
    analogWrite(MOTOR_A2, 0);
    analogWrite(MOTOR_B1, 0);
    analogWrite(MOTOR_B2, MOTOR_B_SPEED);
}

void turnLeft() {
    analogWrite(MOTOR_A1, ROTATION_SPEED);
    analogWrite(MOTOR_A2, 0);  // Left motor backward
    analogWrite(MOTOR_B1, ROTATION_SPEED);
    analogWrite(MOTOR_B2, 0);  // Right motor forward
}

void turnRight() {
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, ROTATION_SPEED);  // Left motor forward
    analogWrite(MOTOR_B1, 0);
    analogWrite(MOTOR_B2, ROTATION_SPEED);  // Right motor backward
}
