/*
  Rangefinder_h - Library for Rangefinder on a Servo
 
 Purpose: Hardware layer, operate a Rangefinder
 Contract  ----------------------------------------------
 
 Guarantee: Read Distances, pont, returns a map
 Preconditions: Point should be in angles.
 
 Finite State Machine: First setPins, calibrate, then repeatedly point and ceck distance.
 
 
 INTERNAL ----------------------------------------------
 
 Translation Needed: 0-1023, to x - y degrees
 
 Workarounds:
 
 To Do:
    1. Update Private Varaibles and incorporate into motor.ino
    2. Make MakMap return a direction and or Distance
 
 Issues
    1. Makemap needs to return an angle and distance. need a Vector object?
 
 Design Decisions
    1.

 
*/

#ifndef Rangefinder_h
#define Rangefinder_h

#include "Arduino.h"
#include <Servo.h>

class Rangefinder
{
  public:
    Rangefinder();
    void setPins(int servoPin, int triggerPin, int echoPin);
    void point(int angle); // in degrees
    void calibrate(int offset); // in degrees
    // int angle(int reading); // in degrees
    // int pointing(); // in degrees
    int getDistance();
    void makeMap();
    void debug(); // in degrees


private:
    ServoMotor _servoMotor;
    int _looking = 90;
    int _triggerPin;                  // define Trig pin for ultrasonic ranging module
    int _echoPin;                  // define Echo pin for ultrasonic ranging module

    // int _ultrasonicPin = 3;            // define pin for signal line of the last servo

    /*
    int servoOffset = 0;
    int maxAngle = 135;
    int minAngle = 45;
    float barDegree = 90;
    float barDistance = 0;

    float maxDistance = 200;          // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
*/
};

#endif

