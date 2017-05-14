/*
   Object: Map
 
   Intent: Manipulate a set of polar coodinates, with different levels of granularity
   Interface: distnace in cm, angles in degrees
   Usage: create, then addReading/size, then closest/furthest/sum, then reset
   Choices:
   Open: 
        Whats the effect of int, does it round
        reset();
        find out how to do Polar addition (and is there a class I should be using in stead of my own)
        how to deal with the potentially empty reading set.
 
*/

#ifndef Map_h
#define Map_h

#include "Arduino.h"
//#include <ArduinoSTL.h>
#include "Polar.h"

class Map
{
  public:
    Map(int slices);
    Map();
    void addReading(int a, int d);
    int numberOfReadings();
    Polar nearest();
    Polar furthest();
    Polar sum();
    //void reset();
    void debug(); // in degrees

private:
    Polar _readings[10];
    int _number = 0;
};

#endif

