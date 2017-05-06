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
    _ultrasonic.setPins(triggerPin,echoPin);
}


void Rangefinder::point(int angle)
{
    _looking=angle;
    _servoMotor.point(_looking);
}


void Rangefinder::calibrate(int offset)
{
    _servoMotor.calibrate(offset);
}


int Rangefinder::getDistance()
{
    return _ultrasonic.getDistance();
}


float Rangefinder::normalise(float thou)
{
    _servoMotor.angle(thou);
}


Polar Rangefinder::makeMap()
{
    float barDegree = _minAngle;
    float barDistance = _maxDistance;
    byte distance;                  // save the current the measured distance from obstacles
    Map m;

    _servoMotor.point(_minAngle);
    
    // start to scan distance. During this progress, we will get the distance and angle from the closest obstacle
    for (byte lookingAngle = _minAngle; lookingAngle < _maxAngle; lookingAngle += 10) {
        _servoMotor.point(lookingAngle); // steer pan tilt to corresponding position
        delay(50);                // wait 50ms between pings (about 20 pingsc). 29ms should be the shortest delay between pings.
        //receiveData();
        distance = getDistance();// detect the current distance from obstacle with angle of pan tilt stable
        m.addReading(lookingAngle,distance);
        }
    } //for
    
    _servoMotor.point(90); // servo of pan tilt turns to default position
    delay(200);

    return  m.closestReading(int max);
}


void Rangefinder::debug()
{
    _servoMotor.debug();
    _ultrasonic.debug();
    
}
