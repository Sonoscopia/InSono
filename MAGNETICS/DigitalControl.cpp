#include "DigitalControl.h"
#include "Arduino.h"

/********************** CONSTRUCTORS **********************/ 
DigitalControl::DigitalControl(){ 
  //default constructor
}
DigitalControl::DigitalControl(int _pin) { // simple constructor (16 steps)
  pin = _pin;
  bpm = 80;
  bars = 1; // how many bars to loop 
  beats = 4; // how many 4n beats per bar
  divisions = 4; // how many divisions per step (4=16th note)
  stepTime = 60.f / bpm * 1000.f; 
  loopTime = bars*beats*stepTime;
  divisionTime = stepTime / divisions;
  steps = bars * beats * divisions; 
  
  pinMode(pin, OUTPUT);
} 

// constructor(pin, bpm, bars, beats, divisions )
DigitalControl::DigitalControl(int _pin, unsigned long _bpm, unsigned short _bars, unsigned short _beats, unsigned short _div){
  
  // set variables
  pin = _pin;
  bpm = _bpm;
  bars = _bars; // how many bars to loop 
  beats = _beats; // how many 4n beats per bar
  divisions = _div; // how many divisions per step (4=16th note)

  // calc variables
  steps = bars * beats * divisions;
  stepTime = 60.f / bpm * 1000.f; 
  loopTime = bars*beats*stepTime;
  divisionTime = stepTime / divisions;
  
  stepIt = 0; // step iterator
  pinMode(pin, OUTPUT);
}

/********************** METHODS **********************/ 
void DigitalControl::analogRun(unsigned long _playHead, unsigned long _smallDiv, int *sData, int *sProb){
  stepData = (int *)sData;
  stepProbability = (int *)sProb;
  // step sequencer
  if(_playHead % divisionTime < _smallDiv) {
    if(stepIt >= steps){ stepIt = 0; }// reset step iterator 
      // probability
      if(random(101) < stepProbability[stepIt]) analogWrite(pin, stepData[stepIt]);
      else analogWrite(pin, LOW);
    
    stepIt++; // iterate steps
  }
}

void DigitalControl::digitalRun(unsigned long _playHead, unsigned long _smallDiv, int *sProb){
  stepProbability = (int *)sProb;
  // step sequencer
  if(_playHead % divisionTime < _smallDiv) {
    if(stepIt >= steps){ stepIt = 0; }// reset step iterator 
      // probability
      if(random(101) < stepProbability[stepIt]){ 
        digitalWrite(pin, HIGH);
        active = true;
      }
      else{
        digitalWrite(pin, LOW);
        active = false;
      }
    
    stepIt++; // iterate steps
  }
}

void DigitalControl::recalc(){
  stepTime = 60.f / bpm * 1000.f; 
  loopTime = bars*beats*stepTime;
  divisionTime = stepTime / divisions;
  steps = bars * beats * divisions;
}



