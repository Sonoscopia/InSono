/*
  Ultrasonic.cpp - Library for HC-SR04 Ultrasonic Ranging Module.library

  Created by ITead studio. Apr 20, 2010.
  iteadstudio.com
*/

#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int TP, int EP)
{
   pinMode(TP,OUTPUT);
   pinMode(EP,INPUT);
   Trig_pin=TP;
   Echo_pin=EP;
   prevDist = 0;
}

long Ultrasonic::Timing()
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH);
  return duration;
}

unsigned long Ultrasonic::Ranging()
{
  Timing();
  distance = duration /29 / 2 ;
  if(distance > MINDIST && distance < MAXDIST){
    prevDist = distance;
    return distance;
  }
  else{
    return prevDist;
  }
}
