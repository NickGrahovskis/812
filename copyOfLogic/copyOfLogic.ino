const int MOTOR_A1 = 11;
const int MOTOR_A2 = 10;
const int MOTOR_B1 = 9;
const int MOTOR_B2 = 8;

const int TRIG_LEFT = A1;
const int TRIG_RIGHT = A0;
const int TRIG = 4;

const int ECHO = 5;
const int ECHO_LEFT = 7;
const int ECHO_RIGHT = 6;

const int MOTOR_A_SPEED = 250;
const int MOTOR_B_SPEED = 237;
const int ROTATION_SPEED = 200;
const int SAFE_DISTANCE = 20;
const int STOP_DISTANCE = 10;

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
}

void loop() {
  long distance = getAverageDistance(TRIG, ECHO);
  long leftDistance = getAverageDistance(TRIG_LEFT, ECHO_LEFT);
  long rightDistance = getAverageDistance(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("Middle: "); Serial.print(distance);
  Serial.print(", Left: "); Serial.print(leftDistance);
  Serial.print(", Right: "); Serial.print(rightDistance);
  Serial.println(" cm");

  if (distance < STOP_DISTANCE) {
    stopMotors();
  } else if (distance < SAFE_DISTANCE) {
    stopMotors();
    if (leftDistance > rightDistance) {
      turnLeft();
    } else {
      turnRight();
    }
    delay(500); // Give time to turn
  } else {
    moveForward();
  }
}

long getAverageDistance(int TRIG_PIN, int ECHO_PIN) {
  long sum = 0;
  for (int i = 0; i < 5; i++) { // Take 5 readings for accuracy
    sum += getDistance(TRIG_PIN, ECHO_PIN);
    delay(10);
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

void deadEndFunction(long distance, long leftDistance, long rightDistance) {
    if (leftDistance < STOP_DISTANCE && distance < STOP_DISTANCE && rightDistance < STOP_DISTANCE) {
        while (leftDistance < STOP_DISTANCE && distance < STOP_DISTANCE && rightDistance < STOP_DISTANCE) {
            moveBackward();
            delay(500);  
            distance = getAverageDistance(TRIG, ECHO);
            leftDistance = getAverageDistance(TRIG_LEFT, ECHO_LEFT);
            rightDistance = getAverageDistance(TRIG_RIGHT, ECHO_RIGHT);
        }
        stopMotors();  // Stop after backing up
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
  analogWrite(MOTOR_B2, MOTOR_A_SPEED);
}

void stopMotors() {
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, 0);
}

void turnLeft() {
  analogWrite(MOTOR_A1, ROTATION_SPEED);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, ROTATION_SPEED);
  analogWrite(MOTOR_B2, 0);
}

void turnRight() {
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, ROTATION_SPEED);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, ROTATION_SPEED);
}