/*
  Ultrasonic_h - Library for Ultrasonic device only (independent of its servoMotor)
 
 Purpose: Hardware layer, operate a Untrasonic sensor
 Contract  ----------------------------------------------
 
 Guarantee: Read Distances
 Preconditions:
 
 Finite State Machine: First setPins, then repeatedly check distance.
 
 
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

#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"
#include "Polar.h"

class Ultrasonic
{
  public:
    Ultrasonic();
    void setPins(int triggerPin, int echoPin);
    int getDistance();
    void debug(); // in degrees


private:
    int _triggerPin;               // define Trig pin for ultrasonic ranging module
    int _echoPin;                  // define Echo pin for ultrasonic ranging module
};

#endif

