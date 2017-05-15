/*
    Object RGB
 
    Intent: Light up a single RGB LED according to three colour inputs, directly to the hardware,
    Interface:
        Language is 
            Low =0, converted at on() stage
            Three colours: between 0 to 255 - 255 means on, 0 meean off
            durations in milliseconds
            Ngradation of colour
        Hardware
            Three digital Hardware Pins
            Translate From Hardware - High as a parameter need to be convered to LOW as an input to the hardware
    Usage: First setPins, then repeatedly (setColour or NextColour, then switch on or shine to illuminate) then off. the LED
    Choices:
        Assume a differenet HW light for indicators, and headlamps etc. Heep it simple and separate hardware
        retain colour even if off
 */


#ifndef RGB_h
#define RGB_h

#include "Arduino.h"

class RGB
{
public:
    RGB();
    RGB(int rPin, int gPin, int bPin);
    void setPins(int rPin, int gPin, int bPin);
    void setColour(int r, int g, int b);
    void nextColour();
    void on(int duration);
    void on();
    void off();
    void setFlash(bool flashing);
    
    void debug();
    
    //  void setFlash(bool flashing);
    //void set(int r, int g, int b, bool temporary, int duration, bool flashing);
    
private:
    void _ledWrite(int r, int g, int b);
    int _rPin;
    int _gPin;
    int _bPin;
    int _r;
    int _g;
    int _b;
    int _RGBValue;
    bool _isOn;
    int _off = 255;
    
    //  bool _isFlashing;
    
};

#endif
