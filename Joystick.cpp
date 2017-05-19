/*
  Object: Joystick
*/

#include "Arduino.h"
#include "Joystick.h"
#include <String.h>

Joystick::Joystick()
{
}

void Joystick::setPins(int xPin, int yPin, bool x, bool y)
{
   _xPin = xPin;
   _yPin = yPin;
   pinMode(_xPin, INPUT);
   pinMode(_yPin, INPUT);
   _reverseX = x;
   _reverseY = y;
}


int Joystick::X()
{
    int x = 0;
    if (_reverseX) {x = 1023-analogRead(_xPin);} else {x = analogRead(_xPin);};
    return x;
}


int Joystick::Y()
{
    int y = 0;
    if (_reverseY) {y = 1023-analogRead(_yPin);} else {y = analogRead(_yPin);};
    return y;

}



void Joystick::debug(String n, String x, String y)
{
    Serial.print("    ");
    Serial.print(n);
    Serial.print(" Joystick ");
    Serial.print(" X axis ");
    Serial.print(x);
    Serial.print(" - ");
    Serial.print(X());
    if (_reverseX) {Serial.print(" ** reversing input ");};
    Serial.print(" on Pin ");
    Serial.print(_xPin);
    Serial.print("  and Y axis ");
    Serial.print(y);
    Serial.print(" - ");
    Serial.print(Y());
    if (_reverseY) {Serial.print(" ** reversing input ");};
    Serial.print(" on Pin ");
    Serial.println(_yPin);
}
