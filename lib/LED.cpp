#include "LED.h"
#include "Arduino.h"

#define VOUT 5 // maximum voltage to LEDs = 5V 

/***************************************** CONSTRUCTORS *****************************************/
LED::LED() : u() {} // default constructor

LED::LED(int rp, int gp, int bp) : u() {
  rPin = rp;
  gPin = gp;
  bPin = bp;
  red = 5.f;
  green = 5.f; 
  blue = 5.f;
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

LED::LED(int l) : u(){
  rPin = l;
  gPin = l;
  bPin = l; 
  red = 5.f;
  green = 5.f; 
  blue = 5.f;
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

LED::LED(int rp, int gp, int bp, float r, float g, float b) : u() {
  rPin = rp;
  gPin = gp;
  bPin = bp;
  red = r;
  green = g; 
  blue = b;
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

LED::LED(int l, float v) : u(){
  rPin = l;
  gPin = l;
  bPin = l; 
  red = v;
  green = v; 
  blue = v;
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

LED::LED(int rp, int gp, int bp, int r, int g, int b) : u() {
  rPin = rp;
  gPin = gp;
  bPin = bp;
  red = u.int2voltage(r, 5.f);
  green = u.int2voltage(g, 5.f);
  blue = u.int2voltage(b, 5.f);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

LED::LED(int l, int v) : u(){
  rPin = l;
  gPin = l;
  bPin = l; 
  red = u.int2voltage(v, 5.f);
  green = u.int2voltage(v, 5.f);
  blue = u.int2voltage(v, 5.f);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}
/***************************************** METHODS *****************************************/
void LED::on(){
  analogWrite(rPin, u.voltage2int(red, VOUT)); // if 5V = 255, 3.3V = 168 
  analogWrite(bPin, u.voltage2int(green, VOUT)); // if 5V = 255, 3.3V = 168 
  analogWrite(gPin, u.voltage2int(blue, VOUT)); // if 5V = 255, 3.3V = 168 
}

void LED::off(){
  analogWrite(rPin, LOW);  
  analogWrite(gPin, LOW); 
  analogWrite(bPin, LOW);
}
