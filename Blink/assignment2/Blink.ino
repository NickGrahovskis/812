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
const int btnpin = 10;


void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(btnpin, INPUT_PULLUP);

  
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledRed, HIGH);
}

void loop() {
  digitalWrite(ledRed, LOW);
    
  if (digitalRead(btnpin) == LOW) { 
    delay(50); 
    while (digitalRead(btnpin) == LOW); 
    digitalWrite(ledRed, HIGH);

    digitalWrite(ledGreen, LOW);
    delay(4000);
    digitalWrite(ledGreen, HIGH);

    digitalWrite(ledYellow, LOW);
    delay(1000);
    digitalWrite(ledYellow, HIGH);

    digitalWrite(ledRed, LOW);
    
  }
}


    



// /*
//   Blink

//   Turns an LED on for one second, then off for one second, repeatedly.

//   Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
//   it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
//   the correct LED pin independent of which board is used.
//   If you want to know what pin the on-board LED is connected to on your Arduino
//   model, check the Technical Specs of your board at:
//   https://www.arduino.cc/en/Main/Products

//   modified 8 May 2014
//   by Scott Fitzgerald
//   modified 2 Sep 2016
//   by Arturo Guadalupi
//   modified 8 Sep 2016
//   by Colby Newman

//   This example code is in the public domain.

//   https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
// */
// const int ledRed = 11;
// const int ledYellow = 12;
// const int ledGreen = 13;
// const int btnpin = 10;
// int btnpin2 = 9;


// void setup() {
//   pinMode(ledGreen, OUTPUT);
//   pinMode(ledYellow, OUTPUT);
//   pinMode(ledRed, OUTPUT);
//   pinMode(btnpin, INPUT_PULLUP);
//   pinMode(btnpin2, INPUT);
//   pinMode(LED_BUILTIN, OUTPUT);

  
//   digitalWrite(ledGreen, HIGH);
//   digitalWrite(ledYellow, HIGH);
//   digitalWrite(ledRed, HIGH);

// }

// void loop() {

//   if(digitalRead(btnpin2) == LOW) { 
//     delay(50);
//     while (digitalRead(btnpin2) == LOW);

//     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//     delay(500);                      // wait for a second
//     digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//     delay(500);
//   }else{
//      digitalWrite(LED_BUILTIN, HIGH);  
//       delay(1000);                      
//       digitalWrite(LED_BUILTIN, LOW);   
//       delay(1000);
//   }


//   if (digitalRead(btnpin) == LOW) { 
//     delay(50); 
//     while (digitalRead(btnpin) == LOW); 

//     digitalWrite(ledGreen, LOW);
//     delay(4000);
//     digitalWrite(ledGreen, HIGH);

//     digitalWrite(ledYellow, LOW);
//     delay(1000);
//     digitalWrite(ledYellow, HIGH);

//     digitalWrite(ledRed, LOW);
//     delay(3000);
//     digitalWrite(ledRed, HIGH);
//   }
// }


    











