/*
   Object RGBLed
 
   Intent: Light up a single RGB LED according to three colour inputs, directly to the hardware,
   Interface:
        Language is Low =0, converted at on() stage
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
   Opens:
      In the absence of the three parameter constructor working, need to create bare, then setPins
      Will Need to code flashing lights, that remember the prior colour
      set colour sets the light colour, but dosn't set RGBValue to the right number
      Does on(duration) stop everything for 2 seconds?
      Can I make LOW represent off?
      Can I do colours beyond just HIGH and LOW - with analogWrite(pin, vlaue) where value 0-255
      Does greySequence of colours create a smoother colour sequence
      How to use constructors with parameters
      enable flashing
      is_off and _HIgh defined
      create subroutine for the digital writes...
      add something that makse teh light flash until it is switched off
      When flashing, have a background colour (possibly none) that you are alternating with

*/


#ifndef RGBLed_h
#define rgbled_h

#include "Arduino.h"

class RGBLed
{
  public:
    RGBLed();
    RGBLed(int rPin, int gPin, int bPin);
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
