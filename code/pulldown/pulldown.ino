/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

//+

/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

int smoothed = 0;


//BUTTON
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

//ANALOG
// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
    // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {


//READ THE PINS
  //BUTTON
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin); //is either one or zero
//ANALOG
 // read the analog in value:
  sensorValue = analogRead(analogInPin); // goes from zero to 1023
  // map it from a 1024 resolution analog signal to 0-5000mV (could be calibrated with a multimeter, max might be less than 5V)
  outputValue = map(sensorValue, 0, 1023, 0, 5000);
  int smoothStrenght = 5;
  smoothed = (outputValue + smoothStrenght*smoothed)/(1+smoothStrenght); 


//Plot the data
  // For visual feedback and proof, turn the 13 led on and off with the buttonstate
    digitalWrite(ledPin, buttonState);
    // print the results to the Serial Monitor:
   Serial.print("RawSensor ");
   Serial.print(outputValue);
   Serial.print(", Smoothed_p5k ");
   Serial.print(smoothed+5000);
  Serial.print(", 5k ");
  Serial.print(5000);// smoothed zero line 
  //Fixed lines, stops zooming
  Serial.print(", Max ");
  Serial.print(10000);
  Serial.print(", Min ");
  Serial.println(-1000); //Note that only this print command is a println = "print line". The others just add text to the same line, have a look in the serial monitor to see.

    
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);

}
