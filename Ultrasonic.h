/*
   Object: Ultrasonic
 
   Intent: Hardware layer, operate a Ultrasonic sensor only (independent of its servoMotor)
   Interface: Return distance in cm.
        HW: two pins analogue echo and digital trigger.
   Usage: First setPins, then repeatedly check distance.

 
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
    void debug();

private:
    int _triggerPin;    // define Trig pin for ultrasonic ranging module
    int _echoPin;       // define Echo pin for ultrasonic ranging module
};

#endif

