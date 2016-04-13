// MAGNETICOS
#include "Motor.h"
#include "LED.h"

#define M1 3 // bottom left (pwm)
#define M2 5 // center (pwm)
#define M3 6 // top right (pwm)
#define M4 2 // center right (digital)
#define M5 4 // bottom right (digital)
#define M6 7 // center left (digital)
#define M7 8 // top left (digital)

#define L1 9 // bottom right (pwm)
#define L2 10 // center left (pwm)
#define L3 11 // center top (pwm)
#define L4 12 // center bottom (digital)
#define L5 13 // bottom left (digital replicated)
#define L6 13 // center right (digital replicated)

Motor m1, m2, m3, m4, m5, m6, m7; 
LED led1, led2, led3, led4, led5, led6, led7; 

int loopDelay = 1;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // ANALOG MOTORS
  //m1 = *new Motor(M1, 1000.f, 10000.f, 80, loopDelay); // pin, rampMin, rampMax, probability
  //m2
  //m3
  // DIGITAL MOTORS
  m1 = *new Motor(M4, 30, 30, 100, loopDelay); // pin, durMin, durMax, probability
  m2 = *new Motor(M4, 3000, 3000, 101, loopDelay); // pin, durMin, durMax, probability
  m3 = *new Motor(M4, 3000, 3000, 101, loopDelay); // pin, durMin, durMax, probability
  m4 = *new Motor(M4, 3000, 3000, 101, loopDelay); // pin, durMin, durMax, probability
  m5 = *new Motor(M4, 3000, 3000, 101, loopDelay); // pin, durMin, durMax, probability
  m6 = *new Motor(M4, 3000, 3000, 101, loopDelay); // pin, durMin, durMax, probability
  m7 = *new Motor(M4, 3000, 3000, 101, loopDelay); // pin, durMin, durMax, probability
  //ANALOG LEDS
  /*
  led1 = *new LED(L1, 1.f, 10.f, 80, loopDelay); // pin, stepMin, stepMax, probability [stepped tones]
  //led2 
  led3 = *new LED(L3, 1000, 20000, 80, loopDelay); // pin, durMin, durMax, probability  [contiunuous tones]
  */
  // DIGITAL LEDS
  led1 = *new LED(L1, 200, 10000, 250, 50, loopDelay); // pin, durMin, durMax, interval, probabiltiy [clicks]  
  led2 = *new LED(L2, 200, 10000, 10, 80, loopDelay); // pin, durMin, durMax, interval, probabiltiy [clicks]
  led3 = *new LED(L3, 200, 10000, 15, 80, loopDelay); // pin, durMin, durMax, interval, probabiltiy [clicks]
  led4 = *new LED(L4, 200, 10000, 50, 60, loopDelay); // pin, durMin, durMax, interval, probabiltiy [clicks]
  led5 = *new LED(L5, 200, 10000, 125, 40, loopDelay); // pin, durMin, durMax, interval, probabiltiy [clicks]
}

void loop() {
//  m1.play();
//  m2.play(); 
//  m3.play();
  int rnd = random(50000);
  
//  if(rnd > 25000){
//    digitalWrite(M1, HIGH);
//    digitalWrite(M2, LOW);
//    digitalWrite(M3, HIGH);
//    digitalWrite(M4, LOW);
//    digitalWrite(M5, HIGH);
//    digitalWrite(M6, LOW);
//    digitalWrite(M7, HIGH);
//  }
//  else{
//    digitalWrite(M1, LOW);
//    digitalWrite(M2, HIGH);
//    digitalWrite(M3, LOW);
//    digitalWrite(M4, HIGH);
//    digitalWrite(M5, LOW);
//    digitalWrite(M6, HIGH);
//    digitalWrite(M7, LOW);
//  }

  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, HIGH);
  digitalWrite(M5, HIGH);
  digitalWrite(M6, HIGH);
  digitalWrite(M7, HIGH);
  
  
//  m1.digitalPlay();
//  m2.digitalPlay();
//  m3.digitalPlay();
//  m4.digitalPlay();
//  m5.digitalPlay();
//  m6.digitalPlay();
//  m7.digitalPlay();

//  
//  led1.stepper();
//  led2.stepper();
//  led3.continuous();
//  
  led1.clicks();
  led2.clicks();
  led3.clicks();
  led4.clicks();
  led5.clicks();
  led6.clicks();

//  led5.clicks();
  
  delay(loopDelay);
}
