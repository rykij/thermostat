/* 
Configure Arduino I/O ports
*/

#ifndef INITPORTS_h
#define INITPORTS_h

#include "Arduino.h"

const int sw = 5;

const int ledOn = 7;
const int ledOff = 8;

const int tempSensor = 0;

class InitPorts
{
    public:

    void SetPorts();

};
#endif

void InitPorts::SetPorts()
{
    pinMode(sw, INPUT);
    pinMode(ledOn, OUTPUT);
    pinMode(ledOff, OUTPUT);
    pinMode(tempSensor, INPUT);
}
