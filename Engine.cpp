/*
   Object: Engine
*/

#include "Arduino.h"
#include "Engine.h"
#include "Motor.h"

#define FORWARD LOW
#define BACKWARD HIGH

Engine::Engine(){
}


void Engine::setPins(int dirAPin, int pwmAPin, int dirBPin, int pwmBPin)
{
    _left.setPins(dirAPin, pwmAPin);
    _right.setPins(dirBPin, pwmBPin);
}


void Engine::drive(int speed)
{
    _speed = constrain(speed + _offset, -255, 255);
    bool _motorDir = _speed > 0 ? BACKWARD : FORWARD;
    _left.drive(speed)
    _right.drive(speed);
}


void Engine::calibrate(int offset)
{
    _offset = map(offset, 0, 1023, -_offsetAccuracy, _offsetAccuracy);
}


int Engine::speed()
{
    return _speed;
}


void Engine::debug()
{
    _left.debug();
    _right.debug();
}


