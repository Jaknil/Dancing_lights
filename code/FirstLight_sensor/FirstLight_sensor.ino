
#include <FastLED.h>

#define NUM_LEDS 240 //60 are disconnected

#define DATA_PIN 2

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];


#define analogInPin A0
//variable to store smooothed signal
int smooth = 0;

//my wrapped led numbers:
int led_numbers[240];



// This function sets up the ledsand tells the controller about them
void setup() {

   pinMode(analogInPin, INPUT);
    Serial.begin(115200);
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


     //read the antenna
      int antennaSignal = Antenna(40);

     
  
     EVERY_N_MILLISECONDS(50){ 
      fadeToBlackBy(leds, NUM_LEDS, 80);
      leds[led_numbers[antennaSignal]]= CRGB::White;
      FastLED.show();
   }


}

int Antenna(int smoothStrenght){
//ANALOG antenna
 // read the analog in value:
int sensorValue = analogRead(analogInPin); // goes from zero to 1023
//smooth it
smooth = (smooth*smoothStrenght + sensorValue)/(1+smoothStrenght);
  //OLD map it from a 1024 resolution analog signal to 0-300 leds
int outputValue = map(smooth, 0, 1023, 0, NUM_LEDS);

if (true) { //Plot the data
    // print the results to the Serial Monitor:
   Serial.print("R ");
   Serial.print(sensorValue+240);
   Serial.print(",S ");
   Serial.print(outputValue);
  //Fixed lines, stops zooming
//  Serial.print(", Max ");
//  Serial.print(1023);
//  Serial.print(", Max*2 ");
//  Serial.print(1023*2);
//  Serial.print(", Min ");
//  Serial.print(0);

  Serial.println(); //Note that only this print command is a println = "print line". The others just add text to the same line, have a look in the serial monitor to see.
}
delay(3); //to not confuse the analogread
  return outputValue;
}  //END ANALOG antenna
