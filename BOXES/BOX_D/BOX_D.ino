/*
CAIXA D
*/
// includes
#include "DistanceSensor.h"
#include "Motor.h"
#include "LED.h"
//#include "Utils.h" (not need because Utils is included in Motor.h and LED.h)

// LED 1 PINS (RGB) : 
#define L1RED 11
#define L1GREEN 9
#define L1BLUE 10
// LED 2 PINS (RGB) : 
#define L2RED 6
#define L2GREEN 3
#define L2BLUE 5
// MOTOR 1 PIN : relay  
#define M1 2 
// MOTOR 2 PIN : relay
#define M2 4
// SENSOR PINS
#define ECHOPIN 8                            // Pin to receive echo pulse
#define TRIGPIN 7                           // Pin to send trigger pulse


// "components"
DistanceSensor sensor;
LED led1, led2;
Motor m1, m2;
// utilities
Utils u; 


// variables
int inactivityTime = 10000; // time(ms) needed for deactivation
bool active = false; 
int threshDist = 80; // threshold distance in cm
int distance; 
int loopDelay = 10; // void loop() delay in milliseconds

void setup(){
  Serial.begin(9600);
  
  u = *new Utils(10); // average uses 10 samples
  
  sensor = *new DistanceSensor(TRIGPIN, ECHOPIN);
  led1 = *new LED(L1RED, L1GREEN, L1BLUE, 0.f, 0.f, 5.f);
  led2 = *new LED(L2RED, L2GREEN, L2BLUE, 0.f, 0.f, 5.f);

  // m = motor pin, mv = maximum voltage, v = arduino input voltage, t = ramp time, d = initial ramp direction, i = ramp iterator value (ms)
  m1 = *new Motor(M1, 5, 5, 6000, true, loopDelay);
  m2 = *new Motor(M2, 5, 5, 6000, false, loopDelay);
}

void loop(){
  distance = u.average(sensor.readValues());
  if(distance != 0 )Serial.println(distance);
  //Serial.println(u.average(sensor.readValues()));
  
  if(distance < threshDist && distance > 0 && active == false) {
    active = true;
    u.resetTimer();
  }
  if (active == true){
    m1.digitalPause();
    m2.digitalPause();
    led1.on();
    led2.on();
    //Serial.println(distance);
  }
  if(distance > threshDist && u.mTime > inactivityTime){
    u.resetTimer();
    active = false;
    m1.digitalPlay();
    m2.digitalPlay();
    led1.off();
    led2.off();
  }
  //Serial.println(u.mTime);
  u.timer(loopDelay);
  delay(loopDelay);
}
