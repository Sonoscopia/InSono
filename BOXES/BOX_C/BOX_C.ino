#include "LED.h"
#include "Utils.h"
#include "Motor.h"
#include "DistanceSensor.h"

#define ECHOPIN 13                            // Pin to receive echo pulse
#define TRIGPIN 12                            // Pin to send trigger pulse

// LED 1 PINS (RGB) : Vasos
#define L1RED 11
#define L1GREEN 10
#define L1BLUE 9
// LED 2 PIN (brightness control) : Copos
// MOTOR 1 PIN : Grande
#define M1 6 
// MOTOR 2 PIN : Medio
#define M2 5
// MOTOR 1 PIN : Pequeno
#define M3 3

LED led1;
Motor m1, m2, m3;
Utils u;
DistanceSensor sensor; 

// Arduino supply voltage
int Vin = 5; // 12v

int inactivityTime = 5000; // time(ms) needed for deactivation
bool active = false; 
int threshDist = 80; // threshold distance in cm
int distance; 
int loopDelay = 10; // void loop() delay in milliseconds


void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));
//  pinMode(ECHOPIN, INPUT);
//  pinMode(TRIGPIN, OUTPUT);
  sensor = *new DistanceSensor(TRIGPIN, ECHOPIN);
  
  u = *new Utils();
  led1 = *new LED(L1RED, L1GREEN, L1BLUE, 1.f, 5.f, 0.f);
  // m = motor pin, mv = maximum voltage, v = arduino input voltage, t = ramp time, d = initial ramp direction, i = ramp iterator value (ms)
  m1 = *new Motor(M1, 1.8f, Vin, 2000, true, loopDelay);
  m2 = *new Motor(M2, 0.8f, Vin, 2666, true, loopDelay);
  m3 = *new Motor(M3, 1.8f, Vin, 2000, true, loopDelay);
}

void loop(){
//  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
//  delayMicroseconds(2);
//  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
//  delayMicroseconds(10);
//  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
//  int distance = pulseIn(ECHOPIN, HIGH);        // Read in times pulse
//  distance = distance/58;                        // Calculate distance from time of pulse
//  Serial.println(distance);                     
  distance = u.average(sensor.readValues());
  //if(distance > 0)Serial.println(distance);
  
  if(distance < threshDist && distance > 0 && active == false) {
    active = true;
    u.resetTimer();
  }
  if (active == true){
    //m1.play();
    // if(u.mTime > 1000) { m2.play(); }
    //m2.play();
    //m3.play();
    int sel = random(1, 3);
    switch (sel){
      case 1:
        m1.play();
        break;
      case 2:
        m2.play();
        break;
      case 3:
        m3.play();
      default:
        break;
    }
    led1.on();
  }
  if(distance > threshDist && u.mTime > inactivityTime){
    u.resetTimer();
    active = false;
    m1.pause();
    m2.pause();
    m3.pause();
    led1.off();
  }
  //Serial.println(u.mTime);
  u.timer(loopDelay);  
  delay(loopDelay);                                    // Wait 50mS before next ranging
}

