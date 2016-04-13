/*
CAIXA B
*/
// includes
#include "DistanceSensor.h"
#include "Motor.h"
#include "LED.h"
//#include "Utils.h" (not need because Utils is included in Motor.h and LED.h)

// LED 1 PINS (RGB) : Vasos
#define L1RED 11
#define L1GREEN 10
#define L1BLUE 9
// LED 2 PIN (brightness control) : Copos
#define L2 6 
// MOTOR 1 PIN : Vasos
#define M1 3 
// MOTOR 2 PIN : Copos
#define M2 5
// SENSOR PINS
#define ECHOPIN 13                            // Pin to receive echo pulse
#define TRIGPIN 12                           // Pin to send trigger pulse


// "components"
DistanceSensor sensor;
LED led1, led2;
Motor m1, m2;
// utilities
Utils u, u1, u2; 
// Arduino supply voltage
int Vin = 12; // 12v
// Motor max. voltage
//int Vmax = 6; // 8v

// variables
int inactivityTime = 8000; // time(ms) needed for deactivation
bool active = false; 
int threshDist = 80; // threshold distance in cm
int distance; 
int loopDelay = 10; // void loop() delay in milliseconds

void setup(){
  Serial.begin(9600);
  
  u = *new Utils(10); // average uses 10 samples
  
  sensor = *new DistanceSensor(TRIGPIN, ECHOPIN);
  led1 = *new LED(L1RED, L1GREEN, L1BLUE, 1.f, 5.f, 0.f);
  led2 = *new LED(L2, 5.f);

  // m = motor pin, mv = maximum voltage, v = arduino input voltage, t = ramp time, d = initial ramp direction, i = ramp iterator value (ms)
  m1 = *new Motor(M1, 2.3, Vin, 2000, true, loopDelay);
  m2 = *new Motor(M2, 2, Vin, 2000, false, loopDelay);
  
}

void loop(){
  distance = u.average(sensor.readValues());
  //Serial.println(u.average(sensor.readValues()));
  
  if(distance < threshDist && distance > 0 && active == false) {
    active = true;
    u.resetTimer();
  }
  if (active == true){
    m1.play();
    m2.play();
    led1.on();
    led2.on();
    //Serial.println(distance);
  }
  if(distance > threshDist && u.mTime > inactivityTime){
    u.resetTimer();
    active = false;
    m1.pause();
    m2.pause();
    led1.off();
    led2.off();
  }
  //Serial.println(u.mTime);
  u.timer(loopDelay);
  delay(loopDelay);
}
