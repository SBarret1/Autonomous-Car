/*
  Object: Button
*/

#include "Arduino.h"
#include "Button.h"

Button::Button()
{
}


void Button::setPins(int pin, TriggerMode trigger, bool pressedSignal)
{
    _pin = pin;
    _trigger = trigger;
    _pressedSignal=pressedSignal;
    _state = false;                 //start off with button off
    _reading = 0;
    _priorReading = 0;

    pinMode(_pin, INPUT_PULLUP);   // Normal is 1, pressed is 0
}


void Button::setTrigger(TriggerMode trigger)
{
    _trigger = trigger;
}


void Button::setPressedSignal (bool pressedSignal)
{
    _pressedSignal = pressedSignal;
}

bool Button::read()     //return button logical state, not physical state
{
    _priorReading = _reading;
    _reading = digitalRead(_pin);

    switch (_trigger) {
        case TOGGLE_ON_PRESS:
            if ((_reading != _priorReading) && (_reading)) {_state = !_state;}
            break;
        case TOGGLE_ON_RELEASE:
            if ((_reading != _priorReading) && (!_reading)) {_state = !_state;}
            break;
        case INSTANT:
            _state=_reading;
            break;
        default:
            Serial.print("error reading button (fell through logic)...");
            break;
    }
    
    return _state;
}


void Button::debug(String a)
{
    Serial.print("  Button -");
    Serial.print(a);
    Serial.print(":   pin ");
    Serial.print(_pin);
    Serial.print(", Trigger ");
    Serial.print(_trigger);
    Serial.print(", and ");
    Serial.print(_pressedSignal);
    Serial.print(" counts as pressed. Current State");
    Serial.print(_state);
    Serial.print(", Reading ");
    Serial.print(_reading);
    Serial.print(", and Prior Reading ");
    Serial.println(_priorReading);
}
