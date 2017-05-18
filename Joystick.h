/*
   Object: Joystick
   Intent: 
   Interface:
        Two Hardware Pin
   Usage: 
   Choices:
*/


#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

class Joystick
{
  public:
    Joystick();
    void setPins(int xPin, int yPin);
    int X();
    int Y();
    void debug();
    
  private:
    int _xPin;
    int _yPin;
};

#endif

