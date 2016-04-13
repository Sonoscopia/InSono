#include "Motor.h"
#include "Arduino.h"

Motor::Motor() : u() {
  voltageIn = 5;
  maxVoltage = 8;   
} 

Motor::Motor(int m) : u() {
  motorPin = m;
  maxVoltage = 5;   
  voltageIn = 5;
  pinMode(motorPin, OUTPUT); 
}

Motor::Motor(int m, float mv) : u() {
  motorPin = m;
  maxVoltage = mv;   
  voltageIn = 5;
  pinMode(motorPin, OUTPUT); 
}

Motor::Motor(int m, float mv, int v) : u() {
  motorPin = m;
  maxVoltage = mv;   
  voltageIn = v;
  pinMode(motorPin, OUTPUT); 
}

Motor::Motor(int m, float mv, int v, int t, bool d, int i){
  motorPin = m;
  maxVoltage = mv;   
  voltageIn = v;

  u.rampTime = t;
  u.rdir = d;
  u.rItValue = i;
  if (u.rdir == false ){ u.rIt = 0; }
  else{ u.rIt = u.rampTime; }
  //u = *new Utils (10, t, d, i); // ramp time, direction, ramp iterator value
  pinMode(motorPin, OUTPUT); 
}

void Motor::play(){
  //Serial.print("rdir = ");
  //Serial.println(u.rdir);
  
  float m = u.fmap(u.ramp(), 0.f, u.rampTime, 0.f, maxVoltage);
  //Serial.println(u.voltage2int(m, voltageIn));
  analogWrite(motorPin, u.voltage2int(m, voltageIn)); 
  //Serial.print("motor = ");
  //Serial.println(u.voltage2int(m, voltageIn));
}

void Motor::digitalPlay(){
  digitalWrite(motorPin, HIGH);
}

void Motor::pause(){
  //u.rIt = u.rampTime; // reset ctime
  //rdir = false; // reset rdir  
  //u.rampReset();
  analogWrite(motorPin, LOW);

}

void Motor::digitalPause(){
  digitalWrite(motorPin, LOW);
}

