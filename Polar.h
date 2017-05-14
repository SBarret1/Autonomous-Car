/*
   Object: Polar
 
   Intent: Manipulate a single polar coordinate - Enable one read of a map and return one parameter with both angle and distance without having to reread the whole map, and allow vecotr addition for netForce
   Interface: angle in degrees, distance in cm (if relevent)
   Usage: Create angle and Distance
   Choices:
*/

#ifndef Polar_h
#define Polar_h

#include "Arduino.h"

class Polar
{
  public:
    Polar();
    Polar(float angle, float distance);
    int angle();      // in degrees
    int distance();
    Polar add(Polar p);
    void debug(); //

private:
    float _angle;
    float _distance;
};

#endif

