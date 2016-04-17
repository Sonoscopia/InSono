#ifndef DIGITALCONTROL_H
#define DIGITALCONTROL_H

class DigitalControl {
public:
  //constructors
  DigitalControl(); // default constructor
  DigitalControl(int pin);
  DigitalControl(int pin, unsigned long _bpm, unsigned short _bars, unsigned short _beats, unsigned short _div); 
  
  //functions
  void analogRun(unsigned long _playHead, unsigned long _smallDiv, int *sData, int *sProb);
  void digitalRun(unsigned long _playHead, unsigned long _smallDiv, int *sProb);
  void recalc(); 
  
  //variables
  int pin; 
  unsigned long bpm;
  unsigned short bars; // how many bars to loop 
  unsigned short beats; // how many 4n beats per bar
  unsigned short divisions; // how many divisions per step (4=16th note)
  const int *stepData;
  const int *stepProbability;
  bool active; 
  
  unsigned long stepTime; // in ms 
  unsigned long loopTime; // how many time it takes to loop all bars
  unsigned long divisionTime; // duration of the smallest division
  unsigned short steps; 
  unsigned short stepIt; // step iterator

  

  
};
#endif

