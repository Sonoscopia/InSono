// sketch from:http://tutorial.cytron.com.my/2012/10/11/testing-ultrasonic-ranging-module-sn-hc-sr04/
// with minor modifications by p1nh0

#include "Ultrasonic.h"
#define ECHOPIN 12                            // Pin to receive echo pulse
#define TRIGPIN 13                            // Pin to send trigger pulse

Ultrasonic ultrasonic(ECHOPIN,TRIGPIN);

void setup() {
  Serial.begin(9600);

}

void loop()
{
  Serial.print(ultrasonic.Ranging(CM));
  Serial.println("cm  ");
    
  delay(50);
}




