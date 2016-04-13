/*
CAIXA A
*/

#define ECHOPIN 12                            // Pin to receive echo pulse
#define TRIGPIN 13                            // Pin to send trigger pulse

#define REDPIN 11
#define GREENPIN 10
#define BLUEPIN 9

// MOTOR 1 PIN : Grande
#define M1 6 
// MOTOR 2 PIN : Medio
#define M2 5
// MOTOR 1 PIN : Pequeno
#define M3 6


int mean[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // mean distance values
int meanIt = 0; // mean iterator
float distance = 0.f; 
int thresh = 80; // threshold distance

int inactivityTime = 3000; // time(ms) needed for deactivation 

int time = 0; // time in milliseconds used to (de)activate motors and leds
int loopDelay = 10; // void loop() delay in milliseconds

int rampTime = 12500; // ramp time in ms
bool rdir = true; // ramp direction (false = ascending, true = descending)
int ctime = rampTime; // time used for composition

int fadeTime = 5000; // light fade out time in ms
int fadeIt = 0; // fade iterator

void setup(){
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(MOTORPIN, OUTPUT);
  
  analogWrite(MOTORPIN, LOW);
  analogWrite(REDPIN, LOW);  
  analogWrite(GREENPIN, LOW); 
  analogWrite(BLUEPIN, LOW);
}

void loop(){
  readDistance();
  if(distance < thresh && distance > 0) {
    time = 0; // reset timer
    play();
    lightUp();
  }
  if(distance > thresh && time > inactivityTime){
    time = 0; // reset timer
    stopMotor();
    lightOut();
  }
  
  timer();
//  Serial.println(time);
  delay(loopDelay);                                    // Wait 50mS before next ranging
}

void play(){
  if(rdir == false){ // ascending
    ctime += loopDelay;
    if(ctime > rampTime){
      rdir = true; 
    }
  }
  else{ // descending 
    ctime -= loopDelay;
    if(ctime <= 0){
      rdir = false;
    }
  }
  float m = fmap(ctime, 0.f, rampTime, 0.f, 8.f);
//  Serial.println(m);
  analogWrite(MOTORPIN, voltage2int(m, 12)); 
}

void stopMotor(){
  ctime = rampTime; // reset ctime
  rdir = false; // reset rdir  
  analogWrite(MOTORPIN, LOW);
}

void lightUp(){
  analogWrite(REDPIN, voltage2int(3.3, 5)); // if 5V = 255, 3.3V = 168 
  analogWrite(GREENPIN, voltage2int(3.3, 5)); // if 5V = 255, 3.3V = 168 
  analogWrite(BLUEPIN, voltage2int(3.3, 5)); // if 5V = 255, 3.3V = 168 
  
  fadeIt = 0; // reset fade iterator
}

void lightOut(){
  
  analogWrite(REDPIN, LOW);  
  analogWrite(GREENPIN, LOW); 
  analogWrite(BLUEPIN, LOW);
}

void timer(){
  time += loopDelay; 
}

void readDistance(){
  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
  int dist = pulseIn(ECHOPIN, HIGH);        // Read in times pulse
  dist= dist/58;                        // Calculate distance from time of pulse
  //Serial.println(dist);                     
  average(dist);
}

void average(int d){
//  distance = 0; 
  mean[meanIt] = d; 
  meanIt++;
  // calc mean after 10 values
  if(meanIt > 9) { 
    distance = 0; // reset average distance
    meanIt = 0; // reset mean iterator
    for(int j = 0; j< 9; j++){
      distance += mean[j]; 
    }
    distance /= 10.f;
//    Serial.println(distance);
  }
}
int voltage2int(int v, int vin){ // v = desired output voltage (must be < vin)
  return v * 255.f / vin; // returns value from 0~255 corresponding to the desired voltage, where 255 = vin
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
