
#include <FastLED.h>

#define NUM_LEDS 240 //60 are disconnected

#define DATA_PIN 2

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);
  FastLED.setBrightness(96);
     FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
   // Move a single white led 
   for(int whiteLed = 0; whiteLed < 60; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;
      copyLEDs();
      // Show the leds (only one of which is set to white, from above)
      FastLED.show();
      // Wait a little bit
      delay(100); //16.6 mm C-C between leds every 0.1 s = 166 mm/s movement speed
      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
   }
}

void copyLEDs(){ //copies the settings of the first row of leds around the stick 
  for (int i=0;i<60;i++){
  leds[i+120]=leds[i];
 // leds[i+240]=leds[i]; //only needed if I fix the last 60 leds they are currently out due to a missing solder pad
  leds[120-1-i]=leds[i];
  leds[240-1-i]=leds[i];
}
}
