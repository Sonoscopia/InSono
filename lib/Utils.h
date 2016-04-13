#ifndef UTILS_H
#define UTILS_H

class Utils{
public: 
  Utils(); // default constructor
  Utils(int aSize); // average size
  //Utils(int t, bool d); // ramp time and ramp direction
  //Utils(int t, bool d, int i); // ramp time, direction and iterator value
  //Utils(int aSize, int t, bool d);
  Utils(int aSize, int t, bool d, int i);
  
  // static functions
  static float average(int v); // average n samples
  
  static int timer();
  static int timer(int inc);
  void resetTimer();
  
  //static int ramp();
  int ramp();
  void rampReset();
  
  int voltage2int(float v, float vin); // convert voltage values to int values (0~255)
  float int2voltage(float c, float vout); // convert int values (0~255) to voltages  
  float fmap(float x, float in_min, float in_max, float out_min, float out_max);

  

  //variables
  // TIMER()
  static int mTime; // timer variable
  // AVERAGE()
  static int avgArray[]; // average array
  static int aValue; // value to average
  static int aIt; // average iterator
  static int averageSize;
  // RAMP()
   int rampTime; // ramp time in ms
   bool rdir; // ramp direction (false = ascending, true = descending) 
   bool initDir; 
   int rItValue;
   int rIt; // ramp iterator
    
  
};

#endif
