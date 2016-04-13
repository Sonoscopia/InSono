#include "Utils.h"
#include "Arduino.h"

// average() variables 
int Utils::avgArray[10]; // average array 
int Utils::aValue = 10; // value to average
int Utils::aIt = 0; // average iterator
int Utils::averageSize = 10;
// timer() variables
int Utils::mTime = 0;
// ramp() variables
//int Utils::rampTime = 2000; // ramp time (x rItValue)
//bool Utils::rdir; // ramp direction (false = ascending, true = descending) 
//int Utils::rItValue = 1;
//int Utils::rIt = 0; // ramp iterator 

/************************************************ CONSTRUCTORS ***********************************************/ 
Utils::Utils(){ 
  // INIT default AVERAGE VARIABLES
  for (int i = 0; i < averageSize; i++){
    avgArray[i] = 0;
  }
  // INIT RAMP VARIABLES
  if (rdir == false ){ rIt = 0; }
  else{ rIt = rampTime; }
}

Utils::Utils(int aSize){
  averageSize = aSize; 
  for (int i = 0; i < averageSize; i++){
    avgArray[i] = 0;
  }
  // INIT RAMP VARIABLES
  if (rdir == false ){ rIt = 0; }
  else{ rIt = rampTime; }
}

Utils::Utils(int aSize, int t, bool d, int i){
  //aIt = 0;
  averageSize = aSize; 
  for (int i = 0; i < averageSize; i++){
    avgArray[i] = 0;
  }
  // INIT RAMP VARIABLES
  rampTime = t; 
  rdir = d;
  initDir = rdir;
  rItValue = i;
  if (rdir == false ){ rIt = 0; }
  else{ rIt = rampTime; }
}

/************************************************ METHODS ***********************************************/

int Utils::ramp(){
  if(rdir == false){ // ascending
    rIt += rItValue;
    if(rIt >= rampTime){
      rdir = true; 
    }
  }
  else{ // descending 
    rIt -= rItValue;
    if(rIt <= 0){
      rdir = false;
    }
  }
  //Serial.println(rIt);
  return rIt; 
}

void Utils::rampReset(){
  rdir = initDir;
  if (rdir == false ){ rIt = 0; }
  else{ rIt = rampTime; }
}

float Utils::average(int v){
  avgArray[aIt] = v;
  aIt++;
  // calc mean after 10 values
  if(aIt > averageSize - 1) { 
    aValue = 0; // reset average value
    aIt = 0; // reset average iterator
    for(int j = 0; j< averageSize - 1; j++){
      aValue += avgArray[j]; 
    }
    aValue /= (float)averageSize;
    return aValue;
    }
}

int Utils::voltage2int(float v, float vin){ // v = desired output voltage (must be < vin)
  //if(vin <= v){
    //Serial.println(v * 255.f / vin);
    return v * 255.0 / vin; // returns value from 0~255 corresponding to the desired voltage, where 255 = vin
  //}
}

float Utils::int2voltage(float c, float vout){
  return c * vout / HIGH;
}

float Utils::fmap(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int Utils::timer(){
  return mTime += 1;
}
int Utils::timer(int inc){
  mTime += inc; 
}
void Utils::resetTimer(){
  mTime = 0;
}
