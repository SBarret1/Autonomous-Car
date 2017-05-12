/*
  Polar_cpp - Library Library to store a single polar coordinate
*/

#include "Arduino.h"
#include "Polar.h"


Polar::Polar(float angle, float distance){
    _angle=angle;
    _distance=distance;
}

int Polar::angle()
{
    return _angle;
}


int Polar::distance()
{
    return _distance;
}


int Polar::add(Polar p)
{
    return 0;
}



void Polar::debug()
{
    
    Serial.print("  Details of Vector:  Angle ");
    Serial.print(_angle);
    Serial.print(" degrees, and Distance ");
    Serial.print(_distance);
    Serial.println("   ");
    
}
