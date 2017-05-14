/*
  Object: ServoMotor
*/


#include "Arduino.h"
#include <Servo.h>
#include "ServoMotor.h"

ServoMotor::ServoMotor(){
    _angle=90;
}

void ServoMotor::setPins(int servoPin)
{
    _servoPin = servoPin;
    _servo.attach(_servoPin);  // attaches the servo on servoDirPin to the servo object
}


void ServoMotor::point(int angle)
{
    _angle = constrain(angle + _offset, _minAngle, _maxAngle);
    _servo.write(_angle);
}


void ServoMotor::calibrate(int offset)
// convert offset 0..1023 into an angle to offset by
{
    _offset = map(offset, 0, 1023, -_offsetAccuracy, _offsetAccuracy);
}


int ServoMotor::normalise(int input)
// normalise 0..1023 desired angle to point, into an angle betweent the min and max
{
    float angle = map(input, 0, 1023, _minAngle, _maxAngle); // steering is between min and max angle
    return (int) angle;
}


int ServoMotor::pointing()
{
    return _angle;
}

int ServoMotor::minAngle()
{
    return _minAngle;
}

int ServoMotor::maxAngle()
{
    return _maxAngle;
}


void ServoMotor::debug()
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

