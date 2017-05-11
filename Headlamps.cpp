/*
   Object: Headlamps
*/


#include "Arduino.h"
#include "Headlamps.h"
#include "RGBLed.h"

Headlamps::Headlamps()
{
     _isOn = false;
}


void Headlamps::setPins(int pinFLr, int pinFLg, int pinFLb, int pinFRr, int pinFRg, int pinFRb)
{
    _main.setPins(pinFLr, pinFLg, pinFLb);
}


void Headlamps::on()
{
    _isOn = true;
    _main.setColour(LOW, LOW, HIGH); // yellow light
    _main.on();
}


void Headlamps::off()
{
    _isOn = false;
    _main.off();
}


void Headlamps::nextColour()
{
    _main.nextColour();
    _main.on();
}


void Headlamps::debug()
// Display its inards
{
    Serial.print("       ** Headlamps:  ");
    _ledFL.debug();
    Serial.print("    On: ");
    Serial.println(_isOn);  Serial.print(" ");


    
}

