/*
  Servo_h - Library for Servos
*/

#ifndef ServoMotor_h
#define ServoMotor_h

#include "Arduino.h"
#include <Servo.h>

class ServoMotor
{
  public:
    ServoMotor(int servoPin);
    void point(int angle); // in degrees
    void calibrate(int offset); // in degrees
    void debug(); // in degrees


private:
    int _servoPin;
    int _angle; // in degrees
    int _offset; // in degrees
};

#endif

