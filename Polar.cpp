/*
  Polar_cpp - Library Library to store a single polar coordinate
*/

#include "Arduino.h"
#include "Polar.h"

Polar::Polar(){
    _angle=0;
    _distance=0;

}

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


Polar Polar::add(Polar p)
{
    return Polar(0,0);
}



void Polar::debug()
{
    
    Serial.print("  Details of Vector:  Angle ");
    Serial.print(_angle);
    Serial.print(" degrees, and Distance ");
    Serial.print(_distance);
    Serial.println("   ");
    
}
