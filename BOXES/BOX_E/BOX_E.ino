/*
CAIXA E
*/
// includes
#include "DistanceSensor.h"
#include "Motor.h"
#include "LED.h"
//#include "Utils.h" (not need because Utils is included in Motor.h and LED.h)

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
#define L4 4

// MOTOR 1 PIN : 
#define M1 2
// MOTOR 2 PIN :
#define M2 3
// MOTOR 3 PIN : 
#define M3 44
// MOTOR 4 PIN :
#define M4 46

// SENSOR PINS
#define ECHOPIN1 24                            // Pin to receive echo pulse
#define TRIGPIN1 22                           // Pin to send trigger pulse
#define ECHOPIN2 52
#define TRIGPIN2 50


// "components"
DistanceSensor sensor1, sensor2;
LED led1, led2, led3, led4;
Motor m1, m2, m3, m4;
// utilities
Utils u; 
// Arduino supply voltage
int Vin = 12; // 12v
// Motor max. voltage
int Vmax = 7; // 8v

// variables
int inactivityTime = 10000; // time(ms) needed for deactivation
bool active = false; 
int threshDist = 80; // threshold distance in cm

int mean[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // mean distance values
int meanIt = 0; // mean iterator
float distance = 0.f; 

int distance1, distance2; 
int loopDelay = 10; // void loop() delay in milliseconds

void setup(){
  Serial.begin(9600);
  
  u = *new Utils(10); // average uses 10 samples
  
  sensor1 = *new DistanceSensor(TRIGPIN1, ECHOPIN1);
  sensor2 = *new DistanceSensor(TRIGPIN2, ECHOPIN2);
  led1 = *new LED(L1RED, L1GREEN, L1BLUE, 5.f, 5.f, 5.f);
  led2 = *new LED(L2RED, L2GREEN, L2BLUE, 5.f, 5.f, 5.f);
  led3 = *new LED(L3RED, L3GREEN, L3BLUE, 5.f, 5.f, 5.f);
  led4 = *new LED(L4, 5.f);

  // m = motor pin, mv = maximum voltage, v = arduino input voltage, t = ramp time, d = initial ramp direction, i = ramp iterator value (ms)
  m1 = *new Motor(M1, Vmax, Vin, 4000, true, loopDelay);
  m2 = *new Motor(M2, Vmax, Vin, 3000, false, loopDelay);
  m3 = *new Motor(M3, Vmax, Vin, 6000, true, loopDelay);
  m4 = *new Motor(M4, Vmax, Vin, 9000, false, loopDelay);
  
}

void loop(){
  distance1 = u.average(sensor1.readValues());
  distance2 = u.average(sensor2.readValues());
  Serial.println(distance);
  readDistance();
  
  if(distance < threshDist && distance > 0 && active == false) {
    active = true;
    u.resetTimer();
  }
  if (active == true){
    m1.play();
    m2.play();
    m3.play();
    m4.play();
    led1.on();
    led2.on();
    led3.on();
    led4.on();
    
    //Serial.println(distance);
  }
  if(distance > threshDist && u.mTime > inactivityTime){
    u.resetTimer();
    active = false;
    m1.pause();
    m2.pause();
    m3.pause();
    m4.pause();
    led1.off();
    led2.off();
    led3.off();
    led4.off();
  }
  //Serial.println(u.mTime);
  u.timer(loopDelay);
  delay(loopDelay);
}

void readDistance(){
  digitalWrite(TRIGPIN1, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN1, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN1, LOW);                   // Send pin low again
  int dist = pulseIn(ECHOPIN1, HIGH);        // Read in times pulse
  dist= dist/58;                        // Calculate distance from time of pulse
  //Serial.println(dist);                     
  average(dist);
}

void average(int d){
//  distance = 0; 
  mean[meanIt] = d; 
  meanIt++;
  // calc mean after 10 values
  if(meanIt > 9) { 
    distance = 0; // reset average distance
    meanIt = 0; // reset mean iterator
    for(int j = 0; j< 9; j++){
      distance += mean[j]; 
    }
    distance /= 10.f;
//    Serial.println(distance);
  }
}
