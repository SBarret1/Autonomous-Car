/*
  Lights_h - Library for Lights
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
    void cancelIndicating();
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
