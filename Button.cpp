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
    _reading = false;
    _priorReading = false;

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
            if ((_reading != _priorReading) && (_reading==_pressedSignal)) {_state = !_state;}
            break;
        case TOGGLE_ON_RELEASE:
            if ((_reading != _priorReading) && (_reading!=_pressedSignal)) {_state = !_state;}
            break;
        case INSTANT:
            if (_pressedSignal) {_state=_reading;} else {_state=!_reading;};

            //_state=_reading;
            break;
        default:
            Serial.print("error reading button (fell through logic)...");
            break;
    }
    
    return _state;
}


void Button::debug(String a)
{
    Serial.print("     Button - ");
    Serial.print(a);
    Serial.print(": Pin ");
    Serial.print(_pin);
    Serial.print(", Trigger is ");

    //Serial.print(_trigger);
    switch (_trigger) {
        case TOGGLE_ON_PRESS:
                Serial.print("TOGGLE_ON_PRESS");
            break;
        case TOGGLE_ON_RELEASE:
                Serial.print("TOGGLE_ON_RELEASE");
            break;
        case INSTANT:
                Serial.print("INSTANT");
            break;
        default:
            Serial.print(" incorrectly set.");
            break;
    }
    Serial.print(", and ");

            //Serial.print(_pressedSignal);
            switch (_pressedSignal) {
                case 0:
                    Serial.print("LOW");
                    break;
                case 1:
                    Serial.print("HIGH");
                    break;
                default:
                    Serial.print("<incorrectly set>");
                    break;
            }
    Serial.print(" counts as pressed.    ");
    Serial.print("Current reading ");
    // Serial.print(_reading);
                            switch (_reading) {
                                case 0:
                                    Serial.print("LOW");
                                    break;
                                case 1:
                                    Serial.print("HIGH");
                                    break;
                                default:
                                    Serial.print("<incorrectly set>");
                                    break;
                            }
    Serial.print(", and prior reading ");
    //Serial.println(_priorReading);
                                    switch (_priorReading) {
                                        case 0:
                                            Serial.print("LOW");
                                            break;
                                        case 1:
                                            Serial.print("HIGH");
                                            break;
                                        default:
                                            Serial.print("<incorrectly set>");
                                            break;
                                    }
    Serial.print("    Current State is ");
    //Serial.print(_state);
    switch (_state) {
        case 0:
            Serial.print("Off");
            break;
        case 1:
            Serial.print("On");
            break;
        default:
            Serial.print("<incorrectly set>");
            break;
    }

    Serial.println("  ");
}
