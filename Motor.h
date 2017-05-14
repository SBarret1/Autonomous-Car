/*
   Object: Single Motor
 
   ??
   Intent: Operate a single HW Motor directly
   Interface: 
        Language: Speed 0..255, Calibrate 1..1023
        HW Motor (drive() translates): Speed 0..255, six pins (pwm, direction and current sensing * 2
   Usage: First setPins, calibrate, then repeatedly change speed.
   Choices:
*/

#ifndef Motor_h
#define Motor_h

#include <Servo.h>
#include "Arduino.h"

class Motor
{
  public:
    Motor();
    void setPins(int dirPin, int pwmPin);
    void drive(int speed); // in degrees
    void calibrate(int offset); // in degrees
    int speed(); // in degrees
    void debug(); // in degrees


private:
    Servo _servo;
    int _dirPin;
    int _pwmPin;
    int _speed;
    int _direction;
    int _offset; 
    int _offsetAccuracy = 50;
};

#endif

