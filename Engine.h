/*
   Object: Engine
 
   Intent: Operate an H bridge dual Motor
   Interface: 
        Language: Speed 0..25, Calibrate 1..1023
        HW Remote (Readdata() translates): Speed 0..1023, Calibrate 1..1023
        HW Motor (drive() translates): Speed 0..255, six pins (pwm, direction and current sensing * 2
   Usage: First setPins, calibrate, then repeatedly change speed.
   Choices: split into two motors (to manage specifics)
*/

#ifndef Engine_h
#define Engine_h

#include <Servo.h>
#include "Arduino.h"
#include "Motor.h"

class Engine
{
  public:
    Engine();
    void setPins(int dirAPin, int pwmAPin, int dirBPin, int pwmBPin);
    void drive(int speed); // in degrees
    void calibrate(int offset); // in degrees
    float  speed();
    void debug(); // in degrees

private:
    Motor _left;
    Motor _right;
};

#endif

