#ifndef MOTOR_H
#define MOTOR_H

#include "Utils.h"

class Motor {
public:
   Motor(); // default constructor
   Motor(int m); // constructor given motor pin
   Motor(int m, float mv); // constructor given motor pin and motor maximum output voltage
   Motor(int m, float mv, int v); // constructor given motor pin,  motor maximum voltage and arduino voltage in

   // FULL CONSTRUCTOR
   Motor(int m, float mv, int v, int t, bool d, int i);
   // m = motor pin, mv = maximum voltage, v = arduino input voltage, t = ramp time, d = initial ramp direction, i = ramp iterator value (ms)
   
   void play();
   void digitalPlay();
   void pause(); 
   void digitalPause();
   // variables
   int motorPin;
private:   
   // utils
   Utils u;
   int voltageIn; // voltage supplied to arduino
   float maxVoltage; // maximum voltage supplied to motor
};

#endif
