//CODE from https://github.com/s-marley/FastLED-basics/blob/main/4.%20Waves%20and%20blur/phaseBeat/phaseBeat.ino
//SEE https://www.youtube.com/watch?v=2owTxbrmY-s&list=PLgXkGn3BBAGi5dTOCuEwrLuFtfz0kGFTC&index=4

#include <FastLED.h>

#define NUM_LEDS  60
#define NUM_LEDS_STRIP  300

#define LED_PIN   2

CRGB leds[NUM_LEDS_STRIP];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS_STRIP);
  FastLED.setBrightness(96);

  Serial.begin(57600);
}


void copyLEDs(){ //copies the settings of the first 30 leds around the stick 
  for (int i=0;i<60;i++){
  leds[i+120]=leds[i];
  leds[i+240]=leds[i];
  leds[120-1-i]=leds[i];
  leds[240-1-i]=leds[i];
}
}
void loop() {

 /* uint8_t sinBeat   = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  uint8_t sinBeat2  = beatsin8(30, 0, NUM_LEDS - 1, 0, 85);
  uint8_t sinBeat3  = beatsin8(30, 0, NUM_LEDS - 1, 0, 170);
*/
  // If you notice that your pattern is missing out certain LEDs, you
  // will need to use the higher resolution beatsin16 instead. In this
  // case remove the 3 lines above and replace them with the following:
   uint16_t sinBeat   = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
   uint16_t sinBeat2  = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
   uint16_t sinBeat3  = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

  leds[sinBeat]   = CRGB::Blue;
  leds[sinBeat2]  = CRGB::Red;
  leds[sinBeat3]  = CRGB::White;
  
  fadeToBlackBy(leds, NUM_LEDS, 10);

  EVERY_N_MILLISECONDS(10){
    Serial.print(sinBeat);
    Serial.print(",");
    Serial.print(sinBeat2);
    Serial.print(",");
    Serial.println(sinBeat3);
  }
copyLEDs();
  FastLED.show();
}
