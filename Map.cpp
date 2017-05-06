/*
  Map_h - Library to enable a rangefinder to manipulate a rose map of polar coodinates, with different granularity
*/


#include "Arduino.h"
#include <vector>
#include "Polar.h"


Map::Map(){
    
}

void Map::addReading(Polar reading)
{
    _readings.push_back(reading);
}


Polar Map::closestReading(int max)
{
    
    
    barDistance = max; // save the minimum measured distance from obstacles
    barAngle = 0;
    
    for (int i  = 0; i < readings.size(); i++) {
        Polar t = readings.at(i);
        if (t.distance() < barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
            barAngle = t.angle();       // save the measured angle
            barDistance = t.distance();     // save the measured distance
            
        }
        Polar p = Polar(barAngle,barDistance); // save the minimum measured
        return p;
    } //for
}


Map::debug()
{
    
}
