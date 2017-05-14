/*
   Object: ServoMotor
 
   Intent: Operate servo HW - Turn Servo linearly, between minAngle and maxAngle degrees, accounting for assembly offset error
        Language: 
            angle is degrees 
                point() uses degrees and talkes into account the offset
                readdata() takes 0..1023 and converts int angle (ignoring offset)
 
            offset is ???
   Interface: 
        Input should be 0-1023, centred on 512
        HW Map input to 10 - 170 degrees
   Usage: First setPins, calibrate, then repeatedly point.
   Choices: 
        Translate 0..1023 to degrees in readDta()
        Apply offset at the point of use
        Language of architecture is degrees

 
*/

#ifndef ServoMotor_h
#define ServoMotor_h

#include "Arduino.h"
#include <Servo.h>

class ServoMotor
{
  public:
    ServoMotor();
    void setPins(int servoPin);
    void point(int angle); // in degrees
    void calibrate(int offset);
    int normalise(int reading);
    int pointing();
    int maxAngle();
    int minAngle();
    void debug();


private:
    Servo _servo;
    int _servoPin;
    int _angle; // in degrees, not 1023
    int _offset; // in degrees, not 1023
    int _maxAngle = 135; // in degrees
    int _minAngle = 45;  // in degrees
    int _offsetAccuracy = 20;
};

#endif

