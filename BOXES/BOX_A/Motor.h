#ifndef MOTOR_H
#define MOTOR_H

#include "Utils.h"

class Motor{
public: 
  Motor(); //default constructor 
  Motor(int _pin, float _vin, int _res); // (pin, Vin, resolution) 
  void SetRamp(float _max, int _t);
  void SetImpulse(float _max, int _t);
  void SetLoopDur(int _t); // if loopTime > impulseTime+rampTime there is a pause after the ramp
  
  void Run();
  void Stop();
  
  int rampDur;
  float rampMax; // max voltage
  int impulseDur;
  float impulseMax; // max voltage
  int loopDur;
     
private: 
  Utils util;

  void Impulse();
  void Ramp();
  void ResetRamp();
  
  float vin; // Vin
  int pin;
  int resolution; // ms delay time in loop()
  int playHead;
  float rampVal; // ramp value at current timing
  float rampDec; // ramp decrementation value (depends on rampDur and resolution)
  bool active;
};

#endif
