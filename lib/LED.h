//#ifndef LED_H
//#define LED_H

#include "Utils.h"

class LED{
public:
  LED(); // default constructor
  LED(int rp, int gp, int bp);
  LED(int l); // RGB LED with brightness control (only!)  
  LED(int rp, int gp, int bp, float r, float g, float b); // float red, green & blue values in volts
  LED(int rp, int gp, int bp, int r, int g, int b); // float red, green & blue values in char (0~255)
  LED(int l, float v); // led pin and brightness control in volts 
  LED(int l, int v); // led pin and brightness control in char (0~255) 
  void on();
  void off();
  // variables
  int rPin, gPin, bPin;
  int red, green, blue; 
private:
  Utils u;
}; 
//#endif

