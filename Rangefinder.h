/*
   Object: Rangefinder
 
   Intent: Combine a ultrasonic and servo. single read and  map.calibratable
   Inteface: Pointing angle should be in degrees. 90 degrees is straight ahead.
        Language: point in degrees and distance in centimeters, calibrate in ????
   Usage: First setPins, calibrate, then repeatedly point and check distance (returns a Map)
   Choices: Returns a Map that hat can be manipulated without having to reread



 
*/

#ifndef Rangefinder_h
#define Rangefinder_h

#include "Arduino.h"
#include "Polar.h"
#include "Map.h"
#include "Ultrasonic.h"
#include "servoMotor.h"
#include <Servo.h>

class Rangefinder
{
  public:
    Rangefinder();
    void setPins(int servoPin, int triggerPin, int echoPin);
    void point(int angle); // in degrees
    void calibrate(int offset); // in degrees
    int getDistance();
    int normalise(float thou);
    void debug(); // in degrees
    Map makeMap();

private:
    ServoMotor _servoMotor;
    Ultrasonic _ultrasonic;
    int _minAngle = 45;
    int _maxAngle = 135;
    int _slices = 10;

    
    /*
    int _ultrasonicPin = 3;            // define pin for signal line of the last servo
    int servoOffset = 0;
    */
};

#endif

