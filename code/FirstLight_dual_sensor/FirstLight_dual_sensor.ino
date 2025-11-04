
// Full documentation on https://github.com/Jaknil/Dancing_lights

//Reads the voltage on an antenna connected directly to an analog input and plots the 0-5V value on a LED bar graph three times in Red Green and Blue with increasing smoothing. The plotted values fades with time. 
// The effect is an interactive rainbow effect if you move, thus indusing a voltage in the antenna. If you stand still, it will average out to a static white bar.
// It only works if it (the arduino ground) is connected to a noise filtered DC power supply.



#include <FastLED.h>

#define strips_alive  3
const int NUM_LEDS = 60*strips_alive;  //120 of 300 are disconnected

#define DATA_PIN 2

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];


#define analogInPin1 A1

//variable to store smooothed signal
int smooth1 = 0;
int smooth2 = 0;

//my wrapped led numbers:
int led_numbers[NUM_LEDS];



// This function sets up the ledsand tells the controller about them
void setup() {

   pinMode(analogInPin1, INPUT);

    Serial.begin(115200);
//Array to store the actual LED positions

int led_strips[strips_alive][60]; //change to 5 strips if I fix it
bool strip_direction = true;
int count_leds =0;
for (int i=0;i<strips_alive;i++){
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
    for (int i=0;i<strips_alive;i++){
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
  FastLED.setBrightness(255);
     FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

// This function runs over and over, and is where you do the magic to light
// your leds.

int position = 0;


 int antennaSignal[3]; //Define a global vector to store the antenna values in
void loop() {


     //read the antenna, set smoothing stength
    Antenna(5); 

     
  
     EVERY_N_MILLISECONDS(20){ 
      fadeToBlackBy(leds, NUM_LEDS, 10); //fade the old leds

//Add colors instead
  // Add one CRGB color to another.
      leds[led_numbers[antennaSignal[0]]] += CRGB( 0, 0, 150); //CRGB::Blue; //signal with smooth
      leds[led_numbers[antennaSignal[1]]] += CRGB( 0, 150, 0); //CRGB::Green;  //more smoothe
      leds[led_numbers[antennaSignal[2]]]  += CRGB(200, 0, 0);  //CRGB::Red; //not smoothed
 /*
      leds[led_numbers[antennaSignal[0]]] += CHSV( 160, 255, 200); //CRGB::Blue;
      leds[led_numbers[antennaSignal[1]]] += CHSV( 96, 255, 200); //CRGB::Green; 
      leds[led_numbers[antennaSignal[2]]]  += CHSV(0, 255, 150);  //CRGB::Red; //not smoothed
   */
      /*
      leds[led_numbers[antennaSignal[0]]]= CRGB::Blue;
      leds[led_numbers[antennaSignal[1]]]= CRGB::Green; 
      leds[led_numbers[antennaSignal[1]]]= CRGB::Red; //not smoothed
      */
      FastLED.show();
   }


}

void Antenna(int smoothStrenght){
//ANALOG antenna
 // read the analog in value:
int sensorValue1 = analogRead(analogInPin1); // goes from zero to 1023
//smooth it
smooth1 = (smooth1*smoothStrenght + sensorValue1)/(1+smoothStrenght);
 int smoothStrenght2 =smoothStrenght+30;
smooth2 = (smooth2*(smoothStrenght2) + sensorValue1)/(1+(smoothStrenght2));
  //OLD map it from a 1024 resolution analog signal to 0-300 leds
 antennaSignal[0] = map(smooth1, 0, 1023, 0, NUM_LEDS-1);
 antennaSignal[1] = map(smooth2, 0, 1023, 0, NUM_LEDS-1);
 antennaSignal[2] =  map(sensorValue1, 0, 1023, 0, NUM_LEDS-1); //TEST TO NOT SMOOTH. Old:  map(smooth2, 0, 1023, 0, NUM_LEDS);
//Offsett them
//antennaSignal[0]= antennaSignal[0]+60;
//antennaSignal[1]= antennaSignal[1]-80;
/*
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
*/


if (true) { //Plot the data
    // print the results to the Serial Monitor:
 //  Serial.print("R ");
 //  Serial.print(sensorValue+240);
   Serial.print("A0 ");
   Serial.print(antennaSignal[0]); //some smooth
   Serial.print(",A1 ");
   Serial.print(antennaSignal[1]); //more smooth
   Serial.print(",A2 ");
   Serial.print(antennaSignal[2]); //raw
  //Fixed lines, stops zooming
    Serial.print(", Max ");
  Serial.print(NUM_LEDS);
//  Serial.print(", Max*2 ");
//  Serial.print(1023*2);
  Serial.print(", Min ");
  Serial.print(1); //to zoom the graph

  Serial.println(); //Note that only this print command is a println = "print line". The others just add text to the same line, have a look in the serial monitor to see.
}
delay(3); //to not confuse the analogread
}  //END ANALOG antenna
