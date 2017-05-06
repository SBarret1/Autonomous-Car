/*
  Map_h - Library to enable a rangefinder to manipulate a rose map of polar coodinates, with different granularity
 
 Purpose: Enable rangefinder to manipulate a rose map of polar coodinates, with different granularity

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

#ifndef Map_h
#define Map_h

#include "Arduino.h"
#include <vector.h>
#include "Polar.h"

class Map
{
  public:
    Map(int elements);
    void addReading(Polar reading);
    Polar closestReading();
    void debug(); // in degrees

private:
    vector <Polar> _readings;
};

#endif

