const int MOTOR_A1 = 10;
const int MOTOR_A2 = 11;
const int MOTOR_B1 = 12;
const int MOTOR_B2 = 13;
//const int SPEED_A = 6;
//const int SPEED_B = 9;



void setup() {
  pinMode(MOTOR_A1,OUTPUT);
  pinMode(MOTOR_A2,OUTPUT);
  pinMode(MOTOR_B1,OUTPUT);
  pinMode(MOTOR_B2,OUTPUT);
  //pinMode(SPEED_A,OUTPUT);
  //pinMode(SPEED_B,OUTPUT);
  

}

void loop() {
  
      analogWrite(MOTOR_A1,0);
      analogWrite(MOTOR_A2,120);
      //analogWrite(SPEED_A,127);
      analogWrite(MOTOR_B1,100);
      analogWrite(MOTOR_B2,0);
      //analogWrite(SPEED_B,127);
      
      
      delay(10000);

      analogWrite(MOTOR_A1,0);
      analogWrite(MOTOR_A2,0);
      analogWrite(MOTOR_B1,0);
      analogWrite(MOTOR_B2,0);
  

}

