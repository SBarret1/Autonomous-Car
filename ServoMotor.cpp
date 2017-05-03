/*
  Servo_cpp - Library for Servos
*/

#ifndef Servo_h
#define Servo_h

#include "Arduino.h"
#include <Servo.h>

class ServoMotor
{
  public:
    ServoMotor(int servoPin);
    void point(int angle = 90);     // in degrees
    void calibrate(int offset = 0); // in degrees

  private:
    Servo _servo;
    int _servoPin;
    int _angle;          // in degrees
    int _offset;         // in degrees
    int _maxAngle = 135; // in degrees
    int _minAngle = 45;  // in degrees
};


ServoMotor::ServoMotor(int servoPin)
{
    _servoPin = servoPin
    _servo.attach(servoPin);  // attaches the servo on servoDirPin to the servo object
}


ServoMotor::point(int angle)
{
    _angle = constrain(_angle + _offset, _minAngle, _maxAngle);
    _servo.write(_angle);
}


ServoMotor::calibrate(int offset)
{
     _offset = offset
}


ServoMotor::debug()
{
    Serial.print("  Details of Servo:  Pin ");
    Serial.print(_servoPin);
    Serial.print(" facing ");
    Serial.print(_angle);
    Serial.print(" degrees, including an offset of ");
    Serial.print(_offset);
    Serial.print(" degrees. Constrained to between  ");
    Serial.print(_minAngle);
    Serial.print(" and ");
    Serial.print(_maxAngle);
    Serial.println(" degrees. ");
}
