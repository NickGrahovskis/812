const int MOTOR_A1 = 11;  //left
const int MOTOR_A2 = 10;
const int MOTOR_B1 = 9;  //right
const int MOTOR_B2 = 8;
const int ROTATION_1 = 3;  // LEFT ENCODER
const int ROTATION_2 = 2;  // RIGHT ENCODER

const int TRIG_LEFT = A1;
const int TRIG_RIGHT = A0;
const int TRIG = 4;

const int ECHO = 5;
const int ECHO_LEFT = 7;
const int ECHO_RIGHT = 6;

const int MOTOR_A_SPEED = 235;  //235 for straight forward
const int MOTOR_B_SPEED = 240;  //240
const int ROTATION_SPEED = 200;
const int SAFE_DISTANCE = 15;
const int STOP_DISTANCE = 5;
const int SAFE_SIDE_DISTANCE = 15;
const int STOP_SIDE_DISTANCE = 15;

volatile int pulseCountLeft = 0;
volatile int pulseCountRight = 0;
unsigned long startMillis = 0;
unsigned long timerOne = 0;
const int INTERVAL = 500;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ROTATION_1), countPulseLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(ROTATION_2), countPulseRight, RISING);
}

void loop() {
  long distance = getAverageDistance(TRIG, ECHO);
  long leftDistance = getAverageDistance(TRIG_LEFT, ECHO_LEFT);
  long rightDistance = getAverageDistance(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("Left Pulses: ");
  Serial.print(pulseCountLeft);
  Serial.print(" | Right Pulses: ");
  Serial.println(pulseCountRight);

  Serial.print("Middle: ");
  Serial.print(distance);
  Serial.print(", Left: ");
  Serial.print(leftDistance);
  Serial.print(", Right: ");
  Serial.print(rightDistance);
  Serial.println(" cm");
   
  if (leftDistance < STOP_SIDE_DISTANCE && distance < STOP_DISTANCE && rightDistance < STOP_SIDE_DISTANCE) {
    deadEndFunction();
    return;
  }
   if(leftDistance < STOP_SIDE_DISTANCE){
    if(distance < STOP_DISTANCE){
       turnRight90();
       return;
    }else if (leftDistance > SAFE_SIDE_DISTANCE){
        turnLeft90();
        return;
    }else{
      moveForward();
      return;
    }
  }else{
    stopMotors();
    Serial.print("Stopping. Left Distance: ");
    Serial.println(leftDistance);
    return;
  }





  // // If there's an obstacle in front (distance is too short), turn right
  // if (distance < STOP_DISTANCE) {
  //   Serial.println("Front obstacle! Turning right.");
  //   turnRight90();
  // }
  // // If the left distance is too far, we are drifting away from the wall, so turn left to correct
  // else if (leftDistance > SAFE_SIDE_DISTANCE) {
  //   Serial.println("No wall on left, turning left to find it.");
  //   turnLeft90();
  // }
  // // If the left distance is too close, it means we are too close to the wall, so we should move forward
  // else if (leftDistance < STOP_SIDE_DISTANCE) {
  //   Serial.println("Following the left wall (moving forward).");
  //   moveForward();
  // } else {
  //   stopMotors();
  //   Serial.print("Stopping. Left Distance: ");
  //   Serial.println(leftDistance);
  // }
  // delay(100);

}


void countPulseLeft() {
  pulseCountLeft++;
}

void countPulseRight() {
  pulseCountRight++;
}

void resetPulseCount() {
  pulseCountLeft = 0;
  pulseCountRight = 0;
}

void moveForward() {
  resetPulseCount();
  int leftSpeed = MOTOR_A_SPEED;
  int rightSpeed = MOTOR_B_SPEED;

  if (pulseCountLeft > pulseCountRight) {
    leftSpeed -= 5;  // Slow down left motor 5
  } else if (pulseCountRight > pulseCountLeft) {
    rightSpeed -= 5;  // Slow down right motor 5
  } else {
    leftSpeed = MOTOR_A_SPEED;
    rightSpeed = MOTOR_B_SPEED;
  }

  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, leftSpeed);
  analogWrite(MOTOR_B1, rightSpeed);
  analogWrite(MOTOR_B2, 0);
}

long getAverageDistance(int TRIG_PIN, int ECHO_PIN) {
  long sum = 0;
  unsigned long startMillis = millis(); // Get the current time
  int count = 0;

  while (count < 5) {
  
    if (millis() - startMillis >= 100) {
      sum += getDistance(TRIG_PIN, ECHO_PIN);
      count++; 
      startMillis = millis();
       
    }
  }

  return sum / 5;
}

long getDistance(int TRIG_PIN, int ECHO_PIN) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void deadEndFunction() {

  moveBackward();

  if (startMillis == 0){
    startMillis = millis(); 
  }

  if (millis() - startMillis >= 500) {
    timerOne = millis() + INTERVAL;
    stopMotors();
    startMillis = 0;
  }
}

void moveBackward() {
  analogWrite(MOTOR_A1, MOTOR_A_SPEED);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, MOTOR_B_SPEED);
}

void stopMotors() {
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, 0);
}

void turnLeft90() {
  resetPulseCount();
  analogWrite(MOTOR_A1, ROTATION_SPEED);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, ROTATION_SPEED);
  analogWrite(MOTOR_B2, 0);
  while (pulseCountLeft < 7) {}
  stopMotors();
}

void turnRight90() {
  resetPulseCount();
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, ROTATION_SPEED);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, ROTATION_SPEED);
  while (pulseCountRight < 9) {}
  stopMotors();
}
