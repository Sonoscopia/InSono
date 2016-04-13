//#ifndef DISTANCESENSOR_H
//#define DISTANCESENSOR_H

#include "Arduino.h"

class DistanceSensor{
public:
  //methods
  DistanceSensor(); // default constructor
  DistanceSensor(int t, int e); // constructor given a trigger an echo pin   
  int readValues(); 
  // variables
  char trigPin, echoPin;
  int dist; // distance value
};

//#endif
