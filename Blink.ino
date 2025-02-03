/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
const int ledRed = 11;
const int ledYellow = 12;
const int ledGreen = 13;
bool grenLight;
bool yellowLight;
bool redLight;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledGreen,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  pinMode(ledRed,OUTPUT);
  

}

// the loop function runs over and over again forever
void loop() {
  if(grenLight){
    digitalWrite(ledGreen, LOW);  
    delay(4000);
    digitalWrite(ledGreen, HIGH);  
    delay(0);
  }elseif()
  


  digitalWrite(ledYellow, LOW);  
  delay(1000);
  digitalWrite(ledYellow, HIGH);  
  delay(0);

  digitalWrite(ledRed, LOW);  
  delay(3000);
  digitalWrite(ledRed, HIGH);  
  delay(0);

}






