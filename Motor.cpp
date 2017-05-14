/*
   Object: Motor
*/

#include "Arduino.h"
#include "Motor.h"

#define FORWARD LOW
#define BACKWARD HIGH

Motor::Motor(){
}

void Motor::setPins(int dirPin, int pwmPin)
{
    _dirPin = dirPin;
    _pwmPin = pwmPin;
    pinMode(_dirPin, OUTPUT);   // set dirAPin to output mode
    pinMode(_pwmPin, OUTPUT);   // set pwmAPin to output mode
}


void Motor::drive(int speed)
{
    _speed = constrain(speed + _offset, -255, 255);
    bool _motorDir = _speed > 0 ? BACKWARD : FORWARD;

    digitalWrite(_dirPin, _motorDir);
    analogWrite(_pwmPin, abs(_speed));
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


