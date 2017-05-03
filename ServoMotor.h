/*
  Servo_h - Library for Servos
 
 Purpose: Hardware layer, operate a Servo. Turning
 Contract  ----------------------------------------------
 
 Guarantee: Turn Servo linearly, between minAngle and maxAngle degrees, accounting for assembly offset error
 
 Preconditions: Input should be 0-1023, centred on 512
 
 Finite State Machine: First setPins, calibrate, then repeatedly point.
 
 
 INTERNAL ----------------------------------------------
 
 Translation Needed: 0-1023, to 10 - 170 degrees
 
 Workarounds:
 
 To Do:
 1.
 
 Issues
 
 Design Decisions
 1.

 
*/

#ifndef ServoMotor_h
#define ServoMotor_h

#include "Arduino.h"
#include <Servo.h>

class ServoMotor
{
  public:
    ServoMotor();
    void setPins(int servoPin);
    void point(int angle); // in degrees
    void calibrate(int offset); // in degrees
    int angle(int reading); // in degrees
    int pointing(); // in degrees
    void debug(); // in degrees


private:
    Servo _servo;
    int _servoPin;
    int _angle; // in degrees
    int _offset; // in degrees
    int _maxAngle = 135; // in degrees
    int _minAngle = 45;  // in degrees
    int _offsetAccuracy = 20;
};

#endif

