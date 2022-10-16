
#include <FastLED.h>

#define NUM_LEDS 240 //60 are disconnected

#define DATA_PIN 2

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];



//my wrapped led numbers:
int led_numbers[240];



// This function sets up the ledsand tells the controller about them
void setup() {
    Serial.begin(57600);
//Array to store the actual LED positions
int led_strips[4][60]; //change to 5 strips if I fix it
bool strip_direction = true;
int count_leds =0;
for (int i=0;i<4;i++){
    for (int j=0;j<60;j++){
      if (strip_direction){
      led_strips[i][j]=count_leds;
      }else{
        led_strips[i][59-j]=count_leds;
      }
      count_leds++;
    }
    strip_direction=!strip_direction;
}
/*
//print the array to check it
for (int i=0;i<4;i++){
    for (int j=0;j<60;j++){
        Serial.print(led_strips[i][j]);
        Serial.print(",");
}        
Serial.println();
}
*/
count_leds =0; //might as well reuse

//Walk through the matrix rows first 
for (int j=0;j<60;j++){
    for (int i=0;i<4;i++){
led_numbers[count_leds]=led_strips[i][j]; //print the led nr to the linear array
count_leds++;

}       
}
/*
//print the array to check it
for (int i=0;i<240;i++){
   Serial.print(led_numbers[i]);
   Serial.print(",");
}
   Serial.println();
*/
  
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);
  FastLED.setBrightness(96);
     FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

// This function runs over and over, and is where you do the magic to light
// your leds.

int position = 0;

void loop() {
   // Move a single white led     
   for(int whiteLed = 0; whiteLed < 240; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[led_numbers[whiteLed]] = CRGB::White;
      //copyLEDs();
      //rearrangeLEDs();
      // Show the leds (only one of which is set to white, from above)
      FastLED.show();
      // Wait a little bit
      delay(10); //16.6 mm C-C between leds every 0.1 s = 166 mm/s movement speed //change to  EVERY_N_MILLISECONDS(50){

      fadeToBlackBy(leds, NUM_LEDS, 50);

     
   }


}
