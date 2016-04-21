/*
BOX E - 4 boxes
Parts: Arduino MEGA, 4 x 12V Motor, 4 RGB Led (1 w/ brightness control only),
1 HC-SR04 Ultrasonic sensor
Objects: Medals, Wooden Bars (right top), Rock (middle right), Wood Blocks
*/

#include "Ultrasonic.h"
#include "Utils.h"
#include "Led.h"
#include "Motor.h"
// WATCH OUT !!! 
#define VIN 12 // Input voltage from power adapter

// LED 1 PINS (RGB) : 
#define L1RED 13
#define L1GREEN 12 
#define L1BLUE 11
// LED 2 PINS (RGB) : 
#define L2RED 10
#define L2GREEN 9 
#define L2BLUE 8
// LED 3 PINS (RGB) : 
#define L3RED 7 
#define L3GREEN 6 
#define L3BLUE 5 
// LED 4 PINS (L) : 
#define LED4 4

// MOTOR 1 PIN : 
#define MOTOR1 2
// MOTOR 2 PIN :
#define MOTOR2 3
// MOTOR 3 PIN : 
#define MOTOR3 44
// MOTOR 4 PIN :
#define MOTOR4 46

// SENSOR PINS
//#define ECHOPIN1 24                            
//#define TRIGPIN1 22                           
#define ECHO 52 // Pin to receive echo pulse
#define TRIG 50 // Pin to send trigger pulse

Ultrasonic ultrasonic(TRIG, ECHO);
Utils utils; // average and elapsedTime/presence functions
Led led1, led2, led3, led4;
Motor motor1, motor2, motor3, motor4; 
float motor1MaxV = 4.f;
float motor2MaxV = 3.f;
float motor3MaxV = 5.5;
float motor4MaxV = 4.f;
float motor1PeakV = 6.f;
float motor2PeakV = 6.5;
float motor3PeakV = 6.5;
float motor4PeakV = 6.f;

bool debug = false;

int dist; // distance in cm
int threshold = 80; // threshold distance in cm
int resolution = 50; // ms delay time in loop()
int averageSamples = 5; // number of distance samples to average
// min thresholdTimeIn = resolution, otherwise thresholdTimeIn = resolution
int thresholdTimeIn = 250; // threshold time with presence to startAll()
int thresholdTimeOut = 8000; // threshold time without presence to stopAll()

bool presence; // is someone in front of the sensor ?

void setup(){
  if(debug) Serial.begin(9600);
  //Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  thresholdTimeIn = thresholdTimeIn / resolution;

  motor1 = *new Motor(MOTOR1, VIN, resolution); // (pin, Vin, resolution)
  motor1.SetImpulse(motor1PeakV, resolution); // (voltage, duration)
  motor1.SetRamp(motor1MaxV, 4000); // (voltage, duration)
  motor1.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()

  motor2 = *new Motor(MOTOR2, VIN, resolution); // (pin, Vin, resolution)
  motor2.SetImpulse(motor2PeakV, resolution); // (voltage, duration)
  motor2.SetRamp(motor2MaxV, 4000); // (voltage, duration)
  motor2.SetWait(1000);
  motor2.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()

  motor3 = *new Motor(MOTOR3, VIN, resolution); // (pin, Vin, resolution)
  motor3.SetImpulse(motor3PeakV, resolution); // (voltage, duration)
  motor3.SetRamp(motor3MaxV, 4000); // (voltage, duration)
  motor3.SetWait(2000);
  motor3.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()

  motor4 = *new Motor(MOTOR4, VIN, resolution); // (pin, Vin, resolution)
  motor4.SetImpulse(motor4PeakV, resolution); // (voltage, duration)
  motor4.SetRamp(motor3MaxV, 4000); // (voltage, duration)
  motor4.SetWait(3000);
  motor4.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()
  
  led1 = *new Led(L1RED, L1GREEN, L1BLUE, ANALOG);
  led1.SetRGB(255, 255, 255);
  led2 = *new Led(L2RED, L2GREEN, L2BLUE, ANALOG);
  led2.SetRGB(255, 255, 255);
  led3 = *new Led(L3RED, L3GREEN, L3BLUE, ANALOG);
  led3.SetRGB(255, 255, 255);
  led4 = *new Led(LED4, LED4, LED4, ANALOG);
  led4.SetRGB(255, 255, 255);
  
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
  led3.On();
  led4.On();
  motor1.Run();
  motor2.Run();
  motor3.Run();
  motor4.Run();
}
void StopAll(){
  led1.Off();
  led2.Off();
  led3.Off();
  led4.Off();
  motor1.Stop();
  motor2.Stop();
  motor3.Stop();
  motor4.Stop();
}

void RandomizeMotors(){
  if(!motor1.active){
    motor1.SetRamp(motor1MaxV, (int)random(2000, 6000)); // (voltage, duration)
    motor1.SetLoopDur((int)random(4000, 8000)); // must be called after SetRamp() and/or SetImpulse()
  }
  if(!motor2.active){
    motor2.SetRamp(motor2MaxV, (int)random(2000, 6000)); // (voltage, duration)
    motor2.SetWait((int)random(500, 3000));
    motor2.SetLoopDur((int)random(4000, 8000)); // must be called after SetRamp() and/or SetImpulse()
  }
  if(!motor3.active){
    motor3.SetRamp(motor3MaxV, (int)random(2000, 6000)); // (voltage, duration)
    motor3.SetWait((int)random(500, 3000));
    motor3.SetLoopDur((int)random(4000, 8000)); // must be called after SetRamp() and/or SetImpulse()
  }
  if(!motor4.active){
    motor4.SetRamp(motor3MaxV, (int)random(2000, 6000)); // (voltage, duration)
    motor4.SetWait((int)random(500, 3000));
    motor4.SetLoopDur((int)random(4000, 8000)); // must be called after SetRamp() and/or SetImpulse()
  }
}

void Debug(String _label, int _val){
  if(debug){
    Serial.print(_label);
    Serial.println(_val);
  }  
}

