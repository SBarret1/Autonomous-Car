/*
  Motor_cpp - Library for H bridge dual Motor
 */

#include "Arduino.h"
#include "Motor.h"

#define FORWARD LOW
#define BACKWARD HIGH

Motor::Motor(){
}

void Motor::setPins(int dirAPin, int pwmAPin, int dirBPin, int pwmBPin)
{
    _dirAPin = dirAPin;
    _pwmAPin = pwmAPin;
    _dirBPin = dirBPin;
    _pwmBPin = pwmBPin;
    
    pinMode(_dirAPin, OUTPUT);   // set dirAPin to output mode
    pinMode(_pwmAPin, OUTPUT);   // set pwmAPin to output mode
    pinMode(_dirBPin, OUTPUT);   // set dirBPin to output mode
    pinMode(_pwmBPin, OUTPUT);   // set pwmBPin to output mode
}


void Motor::drive(int speed)
{
    _speed = constrain(speed + _offset, -255, 255);
    bool _motorDir = _speed > 0 ? BACKWARD : FORWARD;

    digitalWrite(_dirAPin, _motorDir);
    digitalWrite(_dirBPin, _motorDir);
    analogWrite(_pwmAPin, abs(_speed));
    analogWrite(_pwmBPin, abs(_speed));
}


void Motor::calibrate(int offset)
{
    _offset = map(offset, 0, 1023, -_offsetAccuracy, _offsetAccuracy);
}


int Motor::speed()
{
    return _speed;
}


void Motor::debug()
{
    
    Serial.print("    ctrlCar() - motor Offset:  ");
    Serial.print(_offset);
    Serial.print("   Direction:  ");
    // Serial.print(motorDir);
    Serial.print("  Speed: ");
    Serial.println(_speed);
}


