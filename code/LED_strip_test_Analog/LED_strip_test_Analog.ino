#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 30
#define analogInPin A0


// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 2
//#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

//variable to store smooothed signal
int smooth = 0;


void setup() { 
//Select type of led strip
     FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    // initialize serial communications at 9600 bps:
  Serial.begin(57600);
   FastLED.setBrightness(50);
   pinMode(analogInPin, INPUT);
   pinMode(DATA_PIN, OUTPUT);

}

void loop() { 

//Turn leds off
for (int i=0;i<NUM_LEDS;i++){
 leds[i] = CRGB::Black;
}


  //read the antenna and print it to serial for debug
int antennaSignal = Antenna();
for (int i=0;i<antennaSignal;i++){
 leds[i] = CRGB::Green;
}
  
  FastLED.show();
  delay(10);
}


int Antenna(){
//ANALOG antenna
 // read the analog in value:
int sensorValue = analogRead(analogInPin); // goes from zero to 1023
//smooth it
const int smoothStrenght = 6;
smooth = (smooth*smoothStrenght + sensorValue)/(1+smoothStrenght);
  //OLD map it from a 1024 resolution analog signal to 0-300 leds
int outputValue = map(smooth, 0, 1023, 0, NUM_LEDS);
//Plot the data
    // print the results to the Serial Monitor:
   Serial.print("Raw ");
   Serial.print(sensorValue+1023);
   Serial.print(", SmoothValue ");
   Serial.print(smooth);
  //Fixed lines, stops zooming
  Serial.print(", Max ");
  Serial.print(1023);
  Serial.print(", Max*2 ");
  Serial.print(1023*2);
  Serial.print(", Min ");
  Serial.println(0); //Note that only this print command is a println = "print line". The others just add text to the same line, have a look in the serial monitor to see.
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  //END ANALOG antenna
  return outputValue;
}
