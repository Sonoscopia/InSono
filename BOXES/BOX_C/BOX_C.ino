/*
BOX B 
Parts: Arduino Uno, 3 x 5V Motor, 1 RGB Led, 1 HC-SR04 Ultrasonic sensor
Objects: 3 Bowls 
*/

#include "Ultrasonic.h"
#include "Utils.h"
#include "Led.h"
#include "Motor.h"
// WATCH OUT !!! 
#define VIN 12 // Input voltage from power adapter

#define ECHO 13                            // Pin to receive echo pulse
#define TRIG 12                            // Pin to send trigger pulse

// LED 1 PINS (RGB) : Vases
#define RED 11
#define GREEN 10
#define BLUE 9
// MOTOR 1 PIN : Big Bowl
#define MOTOR1 6 
// MOTOR 2 PIN : Medium Bowl
#define MOTOR2 5
// MOTOR 3 PIN : Small Bowl
#define MOTOR3 3

Ultrasonic ultrasonic(TRIG, ECHO);
Utils utils; // average and elapsedTime/presence functions
Led led;
Motor motor1, motor2, motor3; 
float motor1MaxV = 2.f;
float motor2MaxV = 2.f;
float motor3MaxV = 2.f;

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
  //Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  thresholdTimeIn = thresholdTimeIn / resolution;

  motor1 = *new Motor(MOTOR1, VIN, resolution); // (pin, Vin, resolution)
  motor1.SetImpulse(4.f, resolution); // (voltage, duration)
  motor1.SetRamp(motor1MaxV, 4000); // (voltage, duration)
  motor1.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()

  motor2 = *new Motor(MOTOR2, VIN, resolution); // (pin, Vin, resolution)
  motor2.SetImpulse(4.f, resolution); // (voltage, duration)
  motor2.SetRamp(motor2MaxV, 4000); // (voltage, duration)
  motor2.SetWait(1000);
  motor2.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()

  motor3 = *new Motor(MOTOR3, VIN, resolution); // (pin, Vin, resolution)
  motor3.SetImpulse(4.f, resolution); // (voltage, duration)
  motor3.SetRamp(motor3MaxV, 4000); // (voltage, duration)
  motor3.SetWait(2000);
  motor3.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()
  
  led = *new Led(RED, GREEN, BLUE, ANALOG);
  led.SetRGB(0, 128, 255);
  
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
  led.On();
  motor1.Run();
  motor2.Run();
  motor3.Run();
}
void StopAll(){
  led.Off();
  motor1.Stop();
  motor2.Stop();
  motor3.Stop();
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
}

void Debug(String _label, int _val){
  if(debug){
    Serial.print(_label);
    Serial.println(_val);
  }  
}

