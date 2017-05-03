/*
  Servo_cpp - Library for Servos
*/

#ifndef Servo_h
#define Servo_h

#include "Arduino.h"
//#include <Servo.h>
#include "ServoMotor.h"

ServoMotor::ServoMotor(){
}

ServoMotor::setPins(int servoPin)
{
    _servoPin = servoPin;
    _servo.attach(servoPin);  // attaches the servo on servoDirPin to the servo object
}


ServoMotor::point(int angle)
{
    _angle = constrain(angle + _offset, _minAngle, _maxAngle);
    _servo.write(_angle);
}


ServoMotor::calibrate(int offset)
{
    _offset = map(offset, 0, 1023, -_offsetAccuracy, _offsetAccuracy);
}


ServoMotor::angle(int reading)
{
    int angle = map(reading, 0, 1023, _minAngle, _maxAngle); // steering is between min and max angle
    return angle;
}



ServoMotor::pointing()
{
    return _angle;
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
