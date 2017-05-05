/*
  Vector_cpp - Library Library to store a single polar coordinate
*/

#ifndef Vector_h
#define Vector_h

#include "Arduino.h"
#include "Vector.h"


Vector::Vector(float angle, float distance){
    _angle=angle;
    _distance=distance;
}

Vector::angle()
{
    return _angle;
}


Vector::distance()
{
    return _distance;
}


Vector::debug()
{
    
    Serial.print("  Details of Vector:  Angle ");
    Serial.print(_angle);
    Serial.print(" degrees, and Distance ");
    Serial.print(_distance);
    Serial.println("   ");
    
}
