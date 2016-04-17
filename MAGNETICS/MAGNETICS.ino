// MAGNETICOS

#include "DigitalControl.h"


// Motor pins
#define M1 3 // bottom left (pwm)
#define M2 5 // center (pwm)
#define M3 6 // top right (pwm)
#define M4 2 // center right (digital)
#define M5 4 // bottom right (digital)
#define M6 7 // center left (digital)
#define M7 8 // top left (digital)
// LED pins 
#define L1 9 // bottom right (pwm)
#define L2 10 // center left (pwm)
#define L3 11 // center top (pwm)
#define L4 12 // center bottom (digital)
#define L5 13 // bottom left (digital replicated)
#define L6 13 // center right (digital replicated)

#define n4 1 // default
#define n8 2
#define nt8 3
#define n16 4
#define nt16 6
#define n32 8
#define nt32 12
#define n64 16
#define n128 32

unsigned long bpm = 75;

unsigned long playHead = 0; //
unsigned long smallestDivTime;
unsigned long biggestLoopTime;

 
// DIGITAL

//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int probDataL5[] =    {100,  0, 50,  0,100,  0, 50,  0,100,  0, 50,  0,100,  0, 50,  0};
DigitalControl led5;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int probDataL4[] =    {  0, 50,  0, 50,  0, 50,  0, 50,  0, 50,  0, 50,  0, 50,  0, 50};
DigitalControl led4;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int probDataM4[] =    { 50,  0,  0,  0,  0,  0,  0, 50, 50,  0,  0,  0,  0,  0,  0,  0};
DigitalControl motor4;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int probDataM5[] =    { 90, 90, 90, 90, 90, 90, 90, 90,  0,  0,  0,  0,  0,  0,  0,  0};
DigitalControl motor5; // este motor está perro
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int probDataM6[] =    {  0,  0, 50,  0,  0,  0,  0,  0,  0, 50, 50,  0,  0,  0,  0,  0};
DigitalControl motor6;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int probDataM7[] =    {  0, 60, 50,  0,  0,  0,  0,  0,  0, 50, 50,  0,  0, 33,  0, 75};
DigitalControl motor7;

// ANALOG

//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int stepDataL3[] =    {  0, 16, 32, 48, 64, 80, 96,112,128,144,160,176,192,208,234,255};
int probDataL3[] =    { 80, 10, 70,  5, 60,  0, 50, 40,  0, 30, 60,  0, 40, 20,  0, 50};
DigitalControl led3;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
//int stepDataL2[] =  {128, 64, 32, 16,128, 64, 32, 16,128, 64, 32, 16,128, 64, 32, 16};
int stepDataL2[] =    { 96,176,128, 96,176,208,192,112,255,144,160, 64,255,234,176, 64};
int probDataL2[] =    {  0, 10,  0,  0, 30,  0,  0,  0, 30, 40,  0,  0,  0,  0,  0, 40};
DigitalControl led2;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int stepDataL1[] =    {128, 16, 32, 48, 64, 80, 96,112,128,144,160,176,192,208,234,255};
int probDataL1[] =    {  0, 10, 20, 30,  0, 10, 20, 30,  0, 10, 20, 30, 0, 10, 20, 40};
DigitalControl led1;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int stepDataM3[] =  {240,216,169,129,199,215,253,194,204,151,212,139,225,178,198,143};
//int stepDataM3[] =    { 71, 29, 89,  6,118, 52, 36,118, 15,113, 92, 13,124, 30,111, 75};
int probDataM3[] =    {  0,  0, 60, 30, 10,  0, 20, 10,  0,  0, 40,  0, 60,  0, 20, 40};
DigitalControl motor3;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int stepDataM2[] =    {240,216,169,129,199,215,253,194,204,151,212,139,225,178,198,143};
int probDataM2[] =    { 80,  0,  0,  0,  0,  0,  0,  0, 60,  0,  0,  0,  0,  0,  0,  0};
DigitalControl motor2;
//STEPS:                 1   2   3   4|  5   6   7   8|  9  10  11  12| 13  14  15  16
int stepDataM1[] =    {240,216,169,129,199,215,253,194,204,151,212,139,225,178,198,143};
int probDataM1[] =    {  0,  0,  0,  0, 80,  0,  0,  0,  0,  0,  0,  0, 60,  0,  0,  0};
DigitalControl motor1;



void setup() {
  //Serial.begin(9600);
  randomSeed(analogRead(0));
  
  // simple costructor(pin)
  // complete constructor(pin, bpm, bars, beats, divisions )
   
  // DIGITAL LEDS
  led5 = *new DigitalControl(L5, bpm, 1, 4, nt8);
  led4 = *new DigitalControl(L4, bpm, 1, 4, nt8);
  // DIGITAL MOTORS
  motor4 = *new DigitalControl(M4, bpm, 1, 4, nt8);
  motor5 = *new DigitalControl(M5, bpm, 1, 4, nt8);
  motor6 = *new DigitalControl(M6, bpm, 1, 4, nt8);
  motor7 = *new DigitalControl(M7, bpm, 1, 4, nt8);
  // ANALOG LEDS
  led3 = *new DigitalControl(L3, bpm, 1, 4, n4);
  led2 = *new DigitalControl(L2, bpm, 1, 4, n4);
  led1 = *new DigitalControl(L1, bpm, 1, 4, nt8);
  motor3 = *new DigitalControl(M3, bpm, 1, 4, nt32);
  motor2 = *new DigitalControl(M2, bpm, 1, 4, nt8);
  motor1 = *new DigitalControl(M1, bpm, 1, 4, nt8);
  
  smallestDivTime = led1.divisionTime;
  biggestLoopTime = led2.loopTime; 
  
}

void loop() {
  
  playHead = (playHead+smallestDivTime) % biggestLoopTime;
  //Serial.println(playHead);
  //**********************************************
  // DIGITAL
  led5.digitalRun(playHead, smallestDivTime, probDataL5);
  led4.digitalRun(playHead, smallestDivTime, probDataL4);
  motor4.digitalRun(playHead, smallestDivTime, probDataM4);
  motor5.digitalRun(playHead, smallestDivTime, probDataM5);
  motor6.digitalRun(playHead, smallestDivTime, probDataM6);
  motor7.digitalRun(playHead, smallestDivTime, probDataM7);
  // ANALOG
  led3.analogRun(playHead, smallestDivTime, stepDataL3, probDataL3);
  led2.analogRun(playHead, smallestDivTime, stepDataL2, probDataL2);
  led1.analogRun(playHead, smallestDivTime, stepDataL1, probDataL1);
  motor3.analogRun(playHead, smallestDivTime, stepDataM3, probDataM3);
  motor2.analogRun(playHead, smallestDivTime, stepDataM2, probDataM2);
  motor1.analogRun(playHead, smallestDivTime, stepDataM1, probDataM1);
  
  if (!led1.active){
    randomSeed(analogRead(0));
    led1.divisions = randomDivision(nt16, n128);
    led1.recalc();
    smallestDivTime = led1.divisionTime;
  }
  //**********************************************
  delay(smallestDivTime); // smallest division
}

unsigned long randomDivision(int _min, int _max){
  int minimum, maximum;
  switch(_min){
    case n4:
      minimum = 0;
      break;
    case n8:
      minimum = 1;
      break;
    case nt8:
      minimum = 2;
      break;
     case n16:
      minimum = 3;
      break;
     case nt16:
      minimum = 4;
      break;
     case n32:
      minimum = 5;
      break;
     case nt32:
      minimum = 6;
      break;
     case n64:
      minimum = 7;
      break;
     case n128:
      minimum = 8;
      break; 
     default: 
      minimum = 0;
      break;     
  } 
  switch(_max){
    case n4:
      maximum = 0;
      break;
    case n8:
      maximum = 1;
      break;
    case nt8:
      maximum = 2;
      break;
     case n16:
      maximum = 3;
      break;
     case nt16:
      maximum = 4;
      break;
     case n32:
      maximum = 5;
      break;
     case nt32:
      maximum = 6;
      break;
     case n64:
      maximum = 7;
      break;
     case n128:
      maximum = 8;
      break; 
     default: 
      maximum = 8;
      break;     
  }
    
  int r = (int)random(minimum, maximum); 
  switch(r){
    case 0:
      return n4;
      break;
    case 1:
      return n8;
      break;
    case 2:
      return nt8;
      break;
     case 3:
      return n16;
      break;
     case 4:
      return nt16;
      break;
     case 5:
      return n32;
      break;
     case 6:
      return nt32;
      break;
     case 7:
      return n64;
      break;
     case 8:
      return n128;
      break; 
     default:
      return n4; 
      break;    
  } 
}

