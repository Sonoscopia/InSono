#ifndef UTILS_H
#define UTILS_H

class Utils{
public: 
  Utils(); // default constructor  
  // Average
  void AverageSetup(int _size); // function (average sample size)
  float Average(int _s); // function(input sample)
  int *average;
  float averageValue;
  // Elapsed Time
  void ElapsedSetup(int _in, int _out, int _res);
  bool ElapsedTime(bool _b);
  int thresholdTimeIn; // threshold time with presence to startAll()
  int thresholdTimeOut; // threshold time without presence to stopAll()
  int timeResolution; // ms delay time in loop()
  // Conversions
  int Voltage2Int(float _v, float _vin); // (voltage, VIN)
  float Voltage2Float(float _v, float _vin);
  
private: 
  int averageSize; // average sample size
  int iterator; // average iterator

  bool presence; // is someone in front of the sensor ?
  int elapsedTimeIn; // elapsed time since beginning of presence
  int elapsedTimeOut; // elapsed time since lack of presence
};

#endif
