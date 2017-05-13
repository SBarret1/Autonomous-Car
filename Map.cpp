/*
   Object: Map
*/


#include "Arduino.h"
#include "Map.h"
#include <ArduinoSTL.h>
#include "Polar.h"


Map::Map()
{

}


void Map::addReading(Polar reading)
{
    _readings.push_back(reading);
}


int Map::numberOfReadings()
{
    return _readings.size();
}


Polar Map::nearest()
{
    int barDistance = _readings[0].distance(); // save the minimum measured distance from obstacles
    int barAngle = 0;
    
    for (int i  = 0; i < _readings.size(); i++) {
        Polar t = _readings.at(i);
        if (t.distance() < barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
            barAngle = t.angle();       // save the measured angle
            barDistance = t.distance();     // save the measured distance
            
        }
        Polar p = Polar(barAngle,barDistance); // save the minimum measured
        return p;
    } //for
}


Polar Map::furthest()
{
    int barDistance = _readings[0].distance(); // save the minimum measured distance from obstacles
    int barAngle = 0;
    
    for (int i  = 0; i < _readings.size(); i++) {
        Polar t = _readings.at(i);
        if (t.distance() > barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
            barAngle = t.angle();       // save the measured angle
            barDistance = t.distance();     // save the measured distance
            
        }
        Polar p = Polar(barAngle,barDistance); // save the minimum measured
        return p;
    } //for
}


void Map::reset()
{
    _readings.clear();
}


Map::debug()
{
    Serial.print("  Map Contents: {");
    for (int i  = 0; i < _readings.size(); i++) {
        Serial.print(" (");
        Serial.print(_readings[i].angle());
        Serial.print(",");
        Serial.print(_readings[i].distance());
        Serial.print(")  ");
    }
    Serial.println("} ");
    Serial.print(_readings[i].size());
    Serial.print(" readings ")
}
