
#include <FastLED.h>

#define NUM_LEDS 240 //60 are disconnected

#define DATA_PIN 2

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];


#define analogInPin1 A0
#define analogInPin2 A1
//variable to store smooothed signal
int smooth1 = 0;
int smooth2 = 0;

//my wrapped led numbers:
int led_numbers[240];



// This function sets up the ledsand tells the controller about them
void setup() {

   pinMode(analogInPin1, INPUT);
   pinMode(analogInPin2, INPUT);
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


 int antennaSignal[2];
void loop() {


     //read the antenna
    Antenna(40);

     
  
     EVERY_N_MILLISECONDS(50){ 
      fadeToBlackBy(leds, NUM_LEDS, 80);
      leds[led_numbers[antennaSignal[0]]]= CRGB::Green;
      leds[led_numbers[antennaSignal[1]]]= CRGB::Blue;
      FastLED.show();
   }


}

void Antenna(int smoothStrenght){
//ANALOG antenna
 // read the analog in value:
int sensorValue1 = analogRead(analogInPin1); // goes from zero to 1023
int sensorValue2 = analogRead(analogInPin2); // goes from zero to 1023
//smooth it
smooth1 = (smooth1*smoothStrenght + sensorValue1)/(1+smoothStrenght);
smooth2 = (smooth2*smoothStrenght + sensorValue2)/(1+smoothStrenght);
  //OLD map it from a 1024 resolution analog signal to 0-300 leds
 antennaSignal[0] = map(smooth1, 0, 1023, 0, NUM_LEDS);
 antennaSignal[1] =  map(smooth2, 0, 1023, 0, NUM_LEDS);
antennaSignal[0]= antennaSignal[0]+60;
antennaSignal[1]= antennaSignal[0]-80;
if(antennaSignal[0]<0){
  antennaSignal[0]=0;
}
if(antennaSignal[1]<0){
  antennaSignal[1]=0;
}
if(antennaSignal[0]>NUM_LEDS){
  antennaSignal[0]=NUM_LEDS;
}
if(antennaSignal[0]>NUM_LEDS){
  antennaSignal[0]=NUM_LEDS;
}



if (true) { //Plot the data
    // print the results to the Serial Monitor:
 //  Serial.print("R ");
 //  Serial.print(sensorValue+240);
   Serial.print("S1 ");
   Serial.print(antennaSignal[0]);
   Serial.print(",S2 ");
   Serial.print(antennaSignal[1]);
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
}  //END ANALOG antenna
