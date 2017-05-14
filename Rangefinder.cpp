/*
  Rangefinder_cpp - Library for Rangefinders
*/

#include "Arduino.h"
//#include <Servo.h>
#include "ServoMotor.h"
#include "Rangefinder.h"
#include "Ultrasonic.h"
#include "Polar.h"
#include "Map.h"



Rangefinder::Rangefinder(){
}

void Rangefinder::setPins(int servoPin, int triggerPin, int echoPin)
{
    _servoMotor.setPins(servoPin);
    _servoMotor.point(90);
    _ultrasonic.setPins(triggerPin,echoPin);
}


void Rangefinder::point(int angle)
{
    _servoMotor.point(angle);
}


void Rangefinder::calibrate(int offset)
{
    _servoMotor.calibrate(offset);
}


int Rangefinder::getDistance()
{
    return _ultrasonic.getDistance();
}


int Rangefinder::normalise(float thou)
{
    return (int) _servoMotor.normalise(thou);
}


Map Rangefinder::makeMap()
{
    Map map(10);
    
    float width = (_maxAngle - _minAngle)/(_slices-1);
    _servoMotor.point(_minAngle);

    for (int lookingAngle = _minAngle; lookingAngle < _maxAngle; lookingAngle += width) {
        _servoMotor.point(lookingAngle);
        delay(50);                // wait 50ms between pings (about 20 pingsc). 29ms should be the shortest delay between pings.
        int distance = getDistance();// detect the current distance from obstacle with angle of pan tilt stable
        map.addReading(lookingAngle,distance);
    } //for
    _servoMotor.point(90); // servo of pan tilt turns to default position
    delay(200);

    return  map;
}


void Rangefinder::debug()
{
    //slices and width, min and max
    _servoMotor.debug();
    _ultrasonic.debug();
    
}
