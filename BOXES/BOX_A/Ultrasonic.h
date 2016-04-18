/*
  Ultrasonic.h - Library for HR-SC04 Ultrasonic Ranging Module.
  Created by ITead studio. Alex, Apr 20, 2010.
  iteadstudio.com
*/


#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"
#define MINDIST 4
#define MAXDIST 600

class Ultrasonic
{
  public:
    Ultrasonic(int TP, int EP);
    long Timing();
    unsigned long Ranging();
    
    private:
    int Trig_pin;
    int Echo_pin;
    unsigned long  duration,distance, prevDist;
    
};

#endif
