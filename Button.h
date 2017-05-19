/*
   Object: Button
   Intent: 
   Interface:
        One Hardware Pin
   Usage: 
   Choices: use enums for communication
 
   To Do: 
        Need to account for HW reading high as off.
        Test if pin can read into a boolean variable
*/


#ifndef Button_h
#define Button_h

#include "Arduino.h"

enum TriggerMode { TOGGLE_ON_PRESS, TOGGLE_ON_RELEASE, INSTANT};

class Button
{
  public:
    Button();
    void setPins(int pin,  TriggerMode trigger, bool pressedSignal);
    void setTrigger(TriggerMode trigger); // what triggers the button to toggle on and off
    void setPressedSignal(bool pressedSignal); // true means high is on
    bool read();
    void debug(String a);
    
  private:
    void _setOn();
    void _setOff();

    int _pin;
    TriggerMode _trigger;   // instant or toggle etc.
    bool _pressedSignal;             // does high count as pressed or not pressed.
    bool _state;            // is it on or off
    bool _priorReading;
    bool _reading;

};

#endif

