/*
  Motor_h - Library for H bridge dual Motor
 
 Purpose: Hardware layer, operate a Motor. Changing Speed
 Contract  ----------------------------------------------
 
 Guarantee:  
 
 Preconditions:
 
 Finite State Machine: First setPins, calibrate, then repeatedly change speed.
 
 
 INTERNAL ----------------------------------------------
 
 Translation Needed:
 
 Workarounds:
 
 To Do:
 1.
 
 Issues
 
 Design Decisions
 1.

 
*/

#ifndef Motor_h
#define Motor_h
#include <Servo.h>
#include "Arduino.h"

class Motor
{
  public:
    Motor();
    void setPins(int dirAPin, int pwmAPin, int dirBPin, int pwmBPin);
    void drive(int speed); // in degrees
    void calibrate(int offset); // in degrees
    int speed(); // in degrees
    void debug(); // in degrees


private:
    Servo _servo;
    int _dirAPin;
    int _pwmAPin;
    int _dirBPin;
    int _pwmBPin;
    int _speed; // in degrees
    int _offset; // in degrees
    int _offsetAccuracy = 50;
};

#endif

