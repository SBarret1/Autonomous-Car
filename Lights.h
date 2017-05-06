/*
  Lights_h - Library for Lights
 
 Purpose: Operate Archibold's RGB LEDs, using the RGB LED library, so they can switch on and offf, and run through difference colour. In Autonomous mode they can indicate his intention/action red for braking,
 
 Contract  ----------------------------------------------
 
 Guarantee:
 
 Preconditions:

 Finite State Machine: First setPins, then cycle thorough colours, then off.
 
 
 INTERNAL ----------------------------------------------
 
 Translation Needed: Needs to translate to Archibald's hardware. Two RGB sharing the same three datta pins (for red, green and blue)
 
 Workarounds:

 To Do:
    1. add something that makse teh light flash until it is switched off
    2. When flashing, have a background colour (possibly none) that you are alternating with
 
 Issues
 
 Design Decisions 
   1. Don't write a fictional carlights object, because it needs tob eb specific to the hard ware. Once I write me second lights (for Bartholemew) I can work out if there are really two levels for this

*/

#ifndef Lights_h
#define Lights_h

#include "Arduino.h"
#include "LED.h"

class Lights
{
  public:
    Lights();
    void setPins(int pinFLr, int pinFLg, int pinFLb, int pinFRr, int pinFRg, int pinFRb);
    void mainLights();
    void mainLightsOff();

    void indicateLeft(int duration);
    void indicateRight(int duration);
    // void cancelIndicating();
    void off();

    void nextColour();
    
    void debug();
    // void hazardLights();
    // void reversingLights();

    
private:
    LED _ledFL;
    LED _ledFR;
    //LED ledFL(int pinFLr, int pinFLg, int pinFLb); // FrontLeft
    //LED ledFR(int pinFRr, int pinFRg, int pinFRb); // FrontRight

    // LED ledBackLeft(int rPin, int gPin, int bPin);
    // LED ledBackRight(int rPin, int gPin, int bPin);

    bool _isLeft;
    bool _isRight;
    bool _isMain;
    bool _isOn;
    
    // bool _isReversing;
    // bool _isHazard;
    // bool _isBrake;

};

#endif
