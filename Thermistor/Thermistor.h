/*
Temperature sensor wrapper
*/

#ifndef THERMISTOR_h
#define THERMISTOR_h

#include "Arduino.h"

const int thermistorValue = 3975;

class Thermistor
{
    public:

    Thermistor();
    int GetTemperatureValue(int value);
};
#endif

Thermistor::Thermistor()
{
   int _thermistorValue = 3975;
}

int Thermistor::GetTemperatureValue(int value)
{
  float resistance=(float)(1023-value)*10000/value; //get temperature sensor resistance
  return 1/(log(resistance/10000)/thermistorValue+1/298.15)-273.15;//converted to Celsius 
} 



