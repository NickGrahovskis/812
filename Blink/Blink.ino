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
  pinMode(btnpin, INPUT_PULLUP); // Enable internal pull-up resistor

  // Ensure all LEDs are OFF at the start
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledRed, HIGH);
}

void loop() {
  if (digitalRead(btnpin) == LOW) { // Button pressed
    delay(50); // Debounce delay
    while (digitalRead(btnpin) == LOW); // Wait for button release

    // Start the light cycle

    digitalWrite(ledGreen, LOW); // Green ON
    delay(4000);
    digitalWrite(ledGreen, HIGH); // Green OFF

    digitalWrite(ledYellow, LOW); // Yellow ON
    delay(1000);
    digitalWrite(ledYellow, HIGH); // Yellow OFF

    digitalWrite(ledRed, LOW); // Red ON
    delay(3000);
    digitalWrite(ledRed, HIGH); // Red OFF

    // Now all LEDs remain OFF until the next button press
  }
}


    







