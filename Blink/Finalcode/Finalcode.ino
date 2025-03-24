#define MOTOR_A1  11;  // Left Motor – Backward 
#define MOTOR_A2  10;  // Left Motor – Forward
#define MOTOR_B1  9;   // Right Motor – Forward 
#define MOTOR_B2  8;   // Right Motor – Backward

//  ULTRASONIC SENSOR PINS 
// Right sensor (for wall following)
#define RIGHT_TRIG_PIN  A0;
#define RIGHT_ECHO_PIN  6;
float RIGHT_DIS;
// Front sensor (for obstacle detection)
#define FRONT_TRIG_PIN  4;
#define FRONT_ECHO_PIN  5;
float FORWARD_DIS;
// Front sensor (for obstavle detection)
#define LEFT_TRIG_PIN  A1;
#define LEFT_ECHO_PIN  7;
float LEFT_DIS;
//  ENCODER / ROTATION CONFIGURATION 
#define ENCODER_LEFT  3;    // Left encoder pin (interrupt pin)
#define ENCODER_RIGHT  2;   // Right encoder pin (interrupt pin)
volatile unsigned long leftPulses = 0;
volatile unsigned long rightPulses = 0;

float Kp = 7.25;    
float Ki = 1.25;  
float Kd = 0.75;  

#define PIVALUE  3.141592653589793238462643383279502884197
#define GRIPPER 12
#define LEDPIN 13

const int Num_Led = 4;

