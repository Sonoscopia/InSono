#include "Motor.h"
#include "Arduino.h"

Motor::Motor() : util(){
  // default constructor
}
Motor::Motor(int _pin, float _vin, int _res) : util(){
  pin = _pin;
  pinMode(pin, OUTPUT);
  vin = _vin; 
  resolution = _res;
  active = false;
  mode = ANALOG; // default = Analog = 1 (0 = DIGITAL)
  wait = resolution; // default wait time = 0 (run immediately)
}
void Motor::SetMode(int _m){
  if(_m > 0) mode = ANALOG;
  else{ 
    mode = DIGITAL;
    digitalWrite(pin, LOW);
  }  
}

void Motor::SetRamp(float _max, int _t){
  rampMax = _max;
  ResetRamp();
  if(_t > resolution) rampDur = _t;
  else rampDur = resolution+1;
  rampDec = rampMax / (rampDur / resolution);
  SetLoopDur(loopDur); 
}

void Motor::SetImpulse(float _max, int _t){
  impulseMax = _max;
  if(_t > resolution) impulseDur = _t;
  else impulseDur = resolution+1;
  SetLoopDur(loopDur);  
}

void Motor::SetLoopDur(int _t){
  if(_t > impulseDur + rampDur + wait) loopDur = _t;
  else loopDur = impulseDur + rampDur + wait;
}

void Motor::SetWait(int _t){
  if(_t > resolution) wait = _t;
  else wait = resolution;
  SetLoopDur(loopDur);
}

void Motor::Run(){
  playHead += resolution;

  if(playHead > loopDur) Stop();
  else{
    if(playHead > wait){ 
      if(playHead < impulseDur+wait) Impulse();
      else {
        if(playHead < rampDur+wait) Ramp();
        else {
          if(mode) analogWrite(pin, LOW);
          else digitalWrite(pin, LOW);
        }
      }
    }
  }
}

void Motor::Impulse(){
  active = true; 
  if(mode)analogWrite(pin, util.Voltage2Float(impulseMax, vin));
  else digitalWrite(pin, HIGH);
}

void Motor::Ramp(){
  active = true;
  if(mode)analogWrite(pin, util.Voltage2Float(rampVal, vin));
  else digitalWrite(pin, HIGH);
  rampVal -= rampDec;
}

void Motor::ResetRamp(){
    rampVal = rampMax;
}

void Motor::Stop(){
  if(mode)  analogWrite(pin, LOW);
  else digitalWrite(pin,LOW);
  active = false;
  playHead = 0;
  rampVal = rampMax;
} 

int Motor::GetPlayHead(){
  return playHead;  
}
