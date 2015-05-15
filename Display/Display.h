/* 
TM1637 library wrapper
*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"
#include "TM1637.h"

//pins definitions for TM1637
const int8_t clkPin = 2; //CLK
const int8_t dioPin = 3; //DIO

class Display
{
    public:

    TM1637 SetDisplay();
};
#endif

TM1637 Display::SetDisplay()
{
  TM1637 tm1637(clkPin,dioPin);
}