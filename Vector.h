/*
  Vector_h - Library to store a single polar coordinate
 
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

#ifndef Vector_h
#define Vector_h

#include "Arduino.h"

class Vector
{
  public:
    Vector(float angle, float distance);
    float angle();      // in degrees
    float distance();
    void debug(); //


private:
    float _angle;
    float _distance;
};

#endif

