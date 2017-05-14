/*
 Object: Headlamps
 
 Intent: Operate Archibold's RGB LEDs as headlamps - so they can switch on and off, and run through difference colour. In Autonomous mode they can indicate his intention/action (red for braking),
 Interface:
 RGB only High or Low
 three hardware pins - Two RGB sharing the same three datta pins (for red, green and blue)
 Usage: First setPins, then cycle thorough colours (then on?), then off.
 Choices:
 Opens
 should on and setcolour immediately change colour or does it need another on()
 Post Aarchibald - hazard lights, cancel indicator, reversing lights, and indicators
 
 
 */

#ifndef Headlamps_h
#define Headlamps_h

#include "Arduino.h"
#include "RGBLed.h"

class Headlamps
{
public:
    Headlamps();
    void setPins(int pinFLr, int pinFLg, int pinFLb, int pinFRr, int pinFRg, int pinFRb);
    void on();
    void off();
    void nextColour();
    void debug();
    
private:
    RGBLed _main;
    bool _isOn;
};

#endif


