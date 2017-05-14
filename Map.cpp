/*
   Object: Map
*/


#include "Arduino.h"
#include "Map.h"
//#include <ArduinoSTL.h>
#include "Polar.h"


Map::Map()
{
    // no code
}

Map::Map(int slices)
{
   // no code
}


void Map::addReading(int a, int d)
{
    Polar p = Polar(a,d);
    _readings[_number] = p;
    _number++;
}


int Map::numberOfReadings()
{
    return _number;
}


Polar Map::nearest()
{
    int barDistance = _readings[0].distance(); // save the minimum measured distance from obstacles
    int barAngle = 0;
    
    for (int i  = 0; i < _number; i++) {
        Polar t = _readings[i];
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
    
    for (int i  = 0; i < _number; i++) {
        Polar t = _readings[i];
        if (t.distance() > barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
            barAngle = t.angle();       // save the measured angle
            barDistance = t.distance();     // save the measured distance
            
        }
        Polar p = Polar(barAngle,barDistance); // save the minimum measured
        return p;
    } //for
}

/*
void Map::reset()
{
    _readings.clear();
}
*/

void Map::debug()
{
    Serial.print("  Map Contents: {");
    for (int i  = 0; i < _number; i++) {
        Serial.print(" (");
        Serial.print(_readings[i].angle());
        Serial.print(",");
        Serial.print(_readings[i].distance());
        Serial.print(")  ");
    }
    Serial.println("} ");
    Serial.print(_number);
    Serial.print(" readings ");
}
