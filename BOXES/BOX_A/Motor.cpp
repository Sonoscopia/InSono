#include "Motor.h"
#include "Arduino.h"

Motor::Motor() : util(){
  // default constructor
}
Motor::Motor(int _pin, float _vin, int _res) : util(){
  pin = _pin;
  vin = _vin; 
  resolution = _res;
  active = false;
}

void Motor::SetRamp(float _max, int _t){
  rampMax = _max;
  ResetRamp();
  if(_t > resolution) rampDur = _t;
  else rampDur = resolution;
  rampDec = rampMax / (rampDur / resolution); 
}

void Motor::SetImpulse(float _max, int _t){
  impulseMax = _max;
  if(_t > resolution) impulseDur = _t;
  else impulseDur = resolution;  
}

void Motor::SetLoopDur(int _t){
  if(_t > impulseDur + rampDur) loopDur = _t;
  else loopDur = impulseDur + rampDur;
}

void Motor::Run(){
  playHead += resolution;
  if(playHead > loopDur) Stop();
  
  if(playHead < impulseDur){ 
    Impulse();
  }
  else {
    if(playHead < rampDur) Ramp();
    else analogWrite(pin, LOW);
  }
}

void Motor::Impulse(){
  analogWrite(pin, util.Voltage2Int(impulseMax, vin)); 
}

void Motor::Ramp(){
  analogWrite(pin, util.Voltage2Int(rampVal, vin));
  Serial.println(util.Voltage2Int(rampVal, vin));
  rampVal -= rampDec;
}

void Motor::ResetRamp(){
    rampVal = rampMax;
}

void Motor::Stop(){
  analogWrite(pin, LOW);
  active = false;
  playHead = 0;
  rampVal = rampMax;
} 
