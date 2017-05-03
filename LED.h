/*
  LED_h - Library for an LED
*/

#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED
{
  public:
    LED();
    LED(int rPin, int gPin, int bPin);
    void setPins(int rPin, int gPin, int bPin);
    
    void setColour(int r, int g, int b);
    void nextColour();
    void on(int duration);
    void shine();
    void off();

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
