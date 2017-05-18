/*
  Object: Joystick
*/

#include "Arduino.h"
#include "Joystick.h"

Joystick::Joystick()
{
}

void Joystick::setPins(int xPin, int yPin)
{
   _xPin = xPin;
   _yPin = yPin;
   pinMode(_xPin, INPUT);
   pinMode(_yPin, INPUT);
}


int Joystick::X()
{
    return analogRead(_xPin);
}


int Joystick::Y()
{
    return analogRead(_yPin);
}



void Joystick::debug()
{
    Serial.print("  Joystick: X ");
    Serial.print(X());
    Serial.print(" and Y ");
    Serial.print(Y());
    Serial.print(" and Pins (X)");
    Serial.print(_xPin);
    Serial.print(" and (Y)");
    Serial.println(_yPin);
}
