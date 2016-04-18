/*
BOX A - the smallest box 
Parts: Arduino Uno, 1 x 12V Motor (fan), 1 RGB Led, 1 HC-SR04 Ultrasonic sensor
Objects: 2 small gongs 
*/

#include "Ultrasonic.h"
#include "Utils.h"
#include "Led.h"
#include "Motor.h"
// WATCH OUT !!! 
#define VIN 12 // Input voltage from power adapter

#define ECHO 13                            // Pin to receive echo pulse
#define TRIG 12                            // Pin to send trigger pulse

#define MOTOR 3 
#define RED 11
#define GREEN 10
#define BLUE 9

Ultrasonic ultrasonic(TRIG, ECHO);
Utils utils; // average and elapsedTime/presence functions
Led led;
Motor motor; 

bool debug = false;

int dist; // distance in cm
int threshold = 80; // threshold distance in cm
int resolution = 50; // ms delay time in loop()
int averageSamples = 5; // number of distance samples to average
// min thresholdTimeIn = resolution, otherwise thresholdTimeIn = resolution
int thresholdTimeIn = 250; // threshold time with presence to startAll()
int thresholdTimeOut = 5000; // threshold time without presence to stopAll()

bool presence; // is someone in front of the sensor ?

void setup(){
  if(debug) Serial.begin(9600);
  Serial.begin(9600);
  
  thresholdTimeIn = thresholdTimeIn / resolution;

  motor = *new Motor(MOTOR, VIN, resolution); // (pin, Vin, resolution)
  motor.SetImpulse(4.5, resolution); // (voltage, duration)
  motor.SetRamp(2, 4000); // (voltage, duration)
  motor.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()
  
  led = *new Led(RED, GREEN, BLUE, ANALOG);
  led.SetRGB(168, 168, 168);
  
  utils = *new Utils();
  utils.AverageSetup(averageSamples);
  for(int i = 0; i < averageSamples; i++){ // fill avereage array
   utils.Average(ultrasonic.Ranging());
  }
  utils.ElapsedSetup(thresholdTimeIn, thresholdTimeOut, resolution);

  delay(1000);
  // 
}

void loop(){
  
  dist = utils.Average(ultrasonic.Ranging());
  Debug("distance = ", dist);
  
  presence = utils.ElapsedTime(dist < threshold);
  Debug("presence = ", presence);
  
  if (presence) StartAll();
  else StopAll();
  
  delay(resolution);
}
void StartAll(){
  led.On();
  motor.Run();
}
void StopAll(){
  led.Off();
  motor.Stop();
}

void Debug(String _label, int _val){
  if(debug){
    Serial.print(_label);
    Serial.println(_val);
  }  
}

