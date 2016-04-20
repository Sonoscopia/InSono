#include "Utils.h"
#include "Arduino.h"

Utils::Utils(){ // default constructor
  
}

//RUNNING AVERAGE
void Utils::AverageSetup(int _size){
  iterator = 0;
  averageSize = _size;
  average = (int *) calloc (averageSize, sizeof(int));
  averageValue = 0;
}
float Utils::Average(int _s){ // input sample
  averageValue = 0; // reset average value
  for(int i = 1; i < averageSize; i++){
    average[i-1] = average[i];
    averageValue += average[i-1];
  }
  average[averageSize-1] = _s;
  averageValue += _s;
  averageValue /= averageSize;
  //Serial.println(averageValue);
  return averageValue;  
}
// CALC ELAPSED TIME (true -> IN) (false -> OUT)
void Utils::ElapsedSetup(int _in, int _out, int _res){
  presence = false; // is someone in front of the sensor ?
  elapsedTimeIn = 0; // elapsed time since beginning of presence
  elapsedTimeOut = 0; // elapsed time since lack of presence

  timeResolution = _res;
  thresholdTimeIn = _in; // threshold time with presence to startAll()
  thresholdTimeOut = _out; // threshold time without presence to stopAll()  
}

bool Utils::ElapsedTime(bool _b){
  if(_b){
    elapsedTimeIn += timeResolution;
    if(elapsedTimeIn > thresholdTimeIn){
      presence = true;
      elapsedTimeOut = 0; // reset elapsed time
    }  
  }
  else{
    elapsedTimeOut += timeResolution;
    if(elapsedTimeOut > thresholdTimeOut){
      presence = false;
      elapsedTimeIn = 0;
    }
  }
  return presence; 
}

// CONVERSIONS
int Utils::Voltage2Int(float _v, float _vin){ // v = desired output voltage (must be < vin)
  if(_v <= _vin){
    //Serial.println(v * 255.f / vin);
    return int(_v * 255.f / _vin); // returns value from 0~255 corresponding to the desired voltage, where 255 = vin
  }
  else return LOW; // safety
}
float Utils::Voltage2Float(float _v, float _vin){ // v = desired output voltage (must be < vin)
  if(_v <= _vin){
    //Serial.println(v * 255.f / vin);
    return _v * 255.f / _vin; // returns value from 0~255 corresponding to the desired voltage, where 255 = vin
  }
  else return LOW; // safety
}


