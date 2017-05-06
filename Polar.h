/*
  Polar_h - Library to store a single polar coordinate
 
 Purpose: Enable one read of a map and return one parameter with both angle and distance without having to reread teh whole map
 
 Contract  ----------------------------------------------
 
 Guarantee:
 Preconditions:
 
 Finite State Machine:
 
 
 INTERNAL ----------------------------------------------
 
 Translation Needed:
 
 Workarounds:
 
 To Do:
    1.
 
 Issues
    1.
 
 Design Decisions
    1.

 
*/

#ifndef Polar_h
#define Polar_h

#include "Arduino.h"

class Polar
{
  public:
    Polar(float angle, float distance);
    int angle();      // in degrees
    int distance();
    void debug(); //


private:
    float _angle;
    float _distance;
};

#endif

