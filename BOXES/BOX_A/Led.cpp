#include "Led.h"
#include "Arduino.h"

Led::Led(){
  // default constructor
  red = HIGH;
  green = HIGH;
  blue = HIGH;
}

Led::Led(int _rPin, int _gPin, int _bPin, int _m){ // default constructor
  rPin = _rPin;
  gPin = _gPin;
  bPin = _bPin;
  mode = _m;
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void Led::SetRGB(int _r, int _g, int _b){
  red = _r;
  green = _g;
  blue = _b;
}

void Led::On(){
  if(mode){
    analogWrite(rPin, red);
    analogWrite(gPin, green);
    analogWrite(bPin, blue);
  }
  else{
    if (red > 0) digitalWrite(rPin, HIGH);
    else digitalWrite(rPin, LOW);
    if (green > 0) digitalWrite(gPin, HIGH);
    else digitalWrite(gPin, LOW);
    if (blue > 0) digitalWrite(bPin, HIGH);
    else digitalWrite(bPin, LOW);
  }
}

void Led::Off(){
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);  
  digitalWrite(bPin, LOW);
}
