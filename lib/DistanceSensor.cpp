#include "DistanceSensor.h"

// METHODS
DistanceSensor::DistanceSensor(){} // default constructor
DistanceSensor::DistanceSensor(int t, int e){
  trigPin = t;
  echoPin = e;
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);   
}

int DistanceSensor::readValues(){
  digitalWrite(trigPin, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);                   // Send pin low again
  dist = pulseIn(echoPin, HIGH);        // Read in times pulse
  dist= dist/58;                        // Calculate distance from time of pulse

  return dist;
  //average(dist);      
}

