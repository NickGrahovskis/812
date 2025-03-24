#include <Adafruit_NeoPixel.h>

#define LED_PIN    13       // Digital pin connected to the LED strip
#define NUM_LEDS   4        // Number of LEDs in the strip

// Initialize the NeoPixel strip object
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // Initialize the LED strip
  strip.show();            // Turn off all LEDs to start
}

void loop() {
  // Turn all LEDs to red
  setAllLEDs(255, 0, 255);
  delay(1000);

  // Turn all LEDs to green
  setAllLEDs(0, 255, 0);
  delay(1000);

  // Turn all LEDs to blue
  setAllLEDs(0, 0, 255);
  delay(1000);

  // Turn off all LEDs
  setAllLEDs(0, 0, 0);
  delay(1000);
}

// Helper function to set all LED colors at once
void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();  // Update the strip with the new color
}
