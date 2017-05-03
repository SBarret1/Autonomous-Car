/*
   Lights_h - Library for Lights
 
   Spec: Create lights with the six pins necessary, then switch main lights on or off, and indicate left or right or with those off.
*/



#include "Arduino.h"
#include "Lights.h"
#include "LED.h"

Lights::Lights()
{
    _isLeft = false;
    _isRight = false;
    _isMain = false;
    _isOn = false;
}


void Lights::setPins(int pinFLr, int pinFLg, int pinFLb, int pinFRr, int pinFRg, int pinFRb)
{
    _ledFL.setPins(pinFLr, pinFLg, pinFLb);
    _ledFR.setPins(pinFRr, pinFRg, pinFRb);
}


void Lights::mainLights()
{

    _isMain = true;
    _isOn = true;
    _ledFL.setColour(LOW, LOW, HIGH); // yellow light
    _ledFL.shine();
    _ledFR.setColour(LOW, LOW, HIGH); // yellow light
    _ledFR.shine();
}

void Lights::mainLightsOff()
{
    
    _isMain = false;
    _isOn = true;
    _ledFL.setColour(HIGH, HIGH, HIGH); // yellow light
    _ledFL.off();
    _ledFR.setColour(HIGH, HIGH, HIGH); // yellow light
    _ledFR.off();
}

void Lights::off()
{
    _isLeft = false;
    _isRight = false;
    _isMain = false;
    _isOn = false;
    _ledFL.off();
    _ledFR.off();
}


void Lights::nextColour()
{
    _ledFL.nextColour();
    _ledFR.nextColour();
    _ledFL.shine();
    _ledFR.shine();
}


void Lights::debug()
// Display its inards
{
    Serial.print("      Left: ");
    Serial.print(_isLeft);  Serial.print(" ");
    Serial.print("    Right: ");
    Serial.print(_isRight);  Serial.print(" ");
    Serial.print("    Main: ");
    Serial.print(_isMain);  Serial.print(" ");
    Serial.print("    On: ");
    Serial.println(_isOn);  Serial.print(" ");

    Serial.print("       ** Front Left:  ");
    _ledFL.debug();
    // Serial.println(" ");
    Serial.print("        ** Front Right: ");
    _ledFR.debug();
}


/* Code to save for Bartholemew and later
 
 void Lights::indicateLeft(int duration)
 {
 _isLeft = true;
 _isRight = false;
 
 //_isOn = true;
 _ledFL.setColour(LOW, HIGH, HIGH); // yellow light
 _ledFR.setColour(HIGH, HIGH, HIGH); // yellow light
 _ledFL.on(duration);
 _ledFR.on(duration);
 }
 
 
 void Lights::indicateRight(int duration)
 {
 _isRight = true;
 _isLeft = false;
 _ledFL.setColour(HIGH, HIGH, HIGH); // yellow light
 _ledFR.setColour(LOW, HIGH, HIGH); // yellow light
 _ledFL.on(duration);
 _ledFR.on(duration);
 }
 
 
 void Lights::cancelIndicating()
 {
 _isRight = false;
 _isLeft = false;
 _ledFL.setColour(HIGH, HIGH, HIGH); // yellow light
 _ledFR.setColour(HIGH, HIGH, HIGH); // yellow light
 _ledFL.off();
 _ledFR.off();
 }
 */

