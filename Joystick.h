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
#include <String.h>

class Joystick
{
  public:
    Joystick();
    void setPins(int xPin, int yPin, bool x, bool y);
    int X();
    int Y();
    void debug(String n, String x, String y);
    
  private:
    int _xPin;
    int _yPin;
    bool _reverseX;
    bool _reverseY;
};

#endif

