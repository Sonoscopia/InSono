#ifndef LED_H
#define LED_H

#define ANALOG 1
#define DIGITAL 0

class Led{
public: 
  Led(); //default constructor 
  Led(int _rPin, int _gPin, int _bPin, int _m); // (redPin, greenPin, bluePin, mode) 
  void SetRGB(int _r, int _g, int _b); // set RGB colors
  // variables
  int red, green, blue; 
  int mode; // 1 = analog, 0 = digital
  
  void On();
  void Off();
   
private: 
  int rPin, gPin, bPin;
};

#endif
