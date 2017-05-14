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
    _left.drive(speed);
    _right.drive(speed);
}


void Engine::calibrate(int offset)
{
    _left.calibrate(offset);
    _right.calibrate(offset);
}


float Engine::speed()
{
    return (_left.speed()+_right.speed())/2;
}


void Engine::debug()
{
    _left.debug();
    _right.debug();
}


