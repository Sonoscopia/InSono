/*
BOX B 
Parts: Arduino Uno, 2 x 12V Motor (fan), 2 RGB Led (1RGB, 1Bright+Pots), 1 HC-SR04 Ultrasonic sensor
Objects: 1 box with Glasses, 1 box with Vases 
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
// LED 2 PIN (brightness control) : Glasses
#define L2 6 
// MOTOR 1 PIN : Vases
#define MOTOR1 3 
// MOTOR 2 PIN : Glasses
#define MOTOR2 5

Ultrasonic ultrasonic(TRIG, ECHO);
Utils utils; // average and elapsedTime/presence functions
Led led1, led2;
Motor motor1, motor2; 
float motor1MaxV = 2.f;
float motor2MaxV = 2.f;

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
  motor1.SetImpulse(6.f, resolution); // (voltage, duration)
  motor1.SetRamp(motor1MaxV, 4000); // (voltage, duration)
  motor1.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()

  motor2 = *new Motor(MOTOR2, VIN, resolution); // (pin, Vin, resolution)
  motor2.SetImpulse(5.f, resolution); // (voltage, duration)
  motor2.SetRamp(motor2MaxV, 4000); // (voltage, duration)
  motor2.SetWait(2000);
  motor2.SetLoopDur(8000); // must be called after SetRamp() and/or SetImpulse()
  
  led1 = *new Led(RED, GREEN, BLUE, ANALOG);
  led1.SetRGB(51, 255, 0);
  led2 = *new Led(L2, L2, L2, DIGITAL);
  led2.SetRGB(255, 255, 255);
  
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
    motor1.SetRamp(motor1MaxV, (int)random(2000, 6000)); // (voltage, duration)
    motor1.SetLoopDur((int)random(4000, 8000)); // must be called after SetRamp() and/or SetImpulse()
  }
  if(!motor2.active){
    motor2.SetRamp(motor2MaxV, (int)random(2000, 6000)); // (voltage, duration)
    motor2.SetWait((int)random(0, 3000));
    motor2.SetLoopDur((int)random(4000, 8000)); // must be called after SetRamp() and/or SetImpulse()
  }
}

void Debug(String _label, int _val){
  if(debug){
    Serial.print(_label);
    Serial.println(_val);
  }  
}

