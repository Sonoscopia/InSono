/*
BOX D
Parts: Arduino Uno, 2 x Relay 220V, 2 RGB Led, 1 HC-SR04 Ultrasonic sensor
Objects: 3 Aquariums
*/

#include "Ultrasonic.h"
#include "Utils.h"
#include "Led.h"
#include "Motor.h"
// WATCH OUT !!! 
#define VIN 5 // Input voltage from power adapter

// LED 1 PINS (RGB) : 
#define L1RED 11
#define L1GREEN 9
#define L1BLUE 10
// LED 2 PINS (RGB) : 
#define L2RED 6
#define L2GREEN 3
#define L2BLUE 5
// MOTOR 1 PIN : relay  
#define MOTOR1 2 
// MOTOR 2 PIN : relay
#define MOTOR2 4
// SENSOR PINS
#define ECHO 7                            // Pin to receive echo pulse
#define TRIG 8                           // Pin to send trigger pulse

Ultrasonic ultrasonic(TRIG, ECHO);
Utils utils; // average and elapsedTime/presence functions
Led led1, led2;
Motor motor1, motor2; 

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
  
  randomSeed(analogRead(0));
  
  thresholdTimeIn = thresholdTimeIn / resolution;

  motor1 = *new Motor(MOTOR1, VIN, resolution); // (pin, Vin, resolution)
  motor1.SetMode(DIGITAL);
  motor1.SetImpulse(VIN, resolution); // (voltage, duration)
  motor1.SetRamp(VIN, 4000); // (voltage, duration)
  motor1.SetLoopDur(6000); // must be called after SetRamp() and/or SetImpulse()
  
  motor2 = *new Motor(MOTOR2, VIN, resolution); // (pin, Vin, resolution)
  motor2.SetMode(DIGITAL);
  motor2.SetImpulse(VIN, resolution); // (voltage, duration)
  motor2.SetRamp(VIN, 4000); // (voltage, duration)
  motor2.SetWait(1000);
  motor2.SetLoopDur(6000); // must be called after SetRamp() and/or SetImpulse()
  
  led1 = *new Led(L1RED, L1GREEN, L1BLUE, ANALOG);
  led1.SetRGB(0, 128, 255);

  led2 = *new Led(L2RED, L2GREEN, L2BLUE, ANALOG);
  led2.SetRGB(0, 128, 255);
  
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

  RandomizeMotors();
  
  delay(resolution);
}
void StartAll(){
  led1.On();
  led2.On();
  motor1.Run();
  motor2.Run();
}
void StopAll(){
  led1.Off();
  led2.Off();
  motor1.Stop();
  motor2.Stop();
}

void RandomizeMotors(){
  if(!motor1.active){
    motor1.SetRamp(VIN, (int)random(6000, 12000)); // (voltage, duration)
    motor1.SetLoopDur((int)random(8000, 16000)); // must be called after SetRamp() and/or SetImpulse()
  }
  if(!motor2.active){
    motor2.SetRamp(VIN, (int)random(6000, 12000)); // (voltage, duration)
    motor2.SetWait((int)random(2000, 4000));
    motor2.SetLoopDur((int)random(8000, 16000)); // must be called after SetRamp() and/or SetImpulse()
  }
}

void Debug(String _label, int _val){
  if(debug){
    Serial.print(_label);
    Serial.println(_val);
  }  
}

