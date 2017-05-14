/*
  Horn.cpp - Library for Horn
*/

#include "Arduino.h"
#include "Horn.h"

Horn::Horn(int pin)
{
   _pin = pin;
   pinMode(_pin, OUTPUT);
}

void Horn::beep(int duration)
{
   tone(_pin, 2000); 
}

 // if (buzzer) {tone(buzzerPin, 2000);} else {noTone(buzzerPin);}
