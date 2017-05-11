/*
   Object: Horn
   Intent: Replicate HW, Want two modes - sound when button pressed, sound for a duration
   Interface: 
        Duration in Milliseconds
        One Hardware Pin
   Usage: 
   Choices: 
   Opens: 
        test if the pin has to be digital or analogue
        test if I need "if (buzzer) {tone(buzzerPin, 2000);} else {noTone(buzzerPin);}" in horn.cpp
        can I get other pitches and volumes working
*/

#ifndef Horn_h
#define Horn_h

#include "Arduino.h"

class Horn
{
  public:
    Horn(int pin);
    void beep(int duration);
  private:
    int _pin;
};

#endif

