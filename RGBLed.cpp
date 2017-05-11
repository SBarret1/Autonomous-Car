/*
   Object RGBLed
*/

#include "Arduino.h"
#include "RGBLed.h"


RGBLed::RGBLed(int rPin, int gPin, int bPin)
{
    _rPin=rPin;
    _gPin=gPin;
    _bPin=bPin;
    
    _r=HIGH; // HIGH is off
    _g=HIGH; // HIGH is off
    _b=HIGH; // HIGH is off
    
    _RGBValue = 0;
    _isOn = false;
}


void RGBLed::setPins(int rPin, int gPin, int bPin){
    pinMode(_rPin, OUTPUT);   // set RPin to output mode
    pinMode(_gPin, OUTPUT);   // set GPin to output mode
    pinMode(_bPin, OUTPUT);   // set BPin to output mode
    this.off();
    // digitalWrite(_rPin, 255 - _r);
    // digitalWrite(_gPin, 255 - _g);
    // digitalWrite(_bPin, 255 - _b);
}


void RGBLed::setColour(int r, int g, int b)
{
    // Change to a specific colour, but don't automatically turn it on
    // Each colour element should be either HIGH or LOW
    _r=r;
    _g=g;
    _b=b;
}


void RGBLed::nextColour()
// Move to next colour, but don't automatically turn it on
{
    _RGBValue++;
    _RGBValue=_RGBValue%8;
    
    switch(_RGBValue){
        case 0: _r=_off;_g=_off;_b=_off;break;
        case 1: _r=_off;_g=_off;_b=LOW;break;
        case 2: _r=_off;_g=LOW;_b=LOW;break;
        case 3: _r=_off;_g=LOW;_b=_off;break;
        case 4: _r=LOW;_g=LOW;_b=_off;break;
        case 5: _r=LOW;_g=LOW;_b=LOW;break;
        case 6: _r=LOW;_g=_off;_b=LOW;break;
        case 7: _r=LOW;_g=_off;_b=_off;break;
        default: break;
    }
}


void RGBLed::on(int duration)
// Switch light on for a number of milliseconds
{
    _isOn = true;
    on();
    delay(duration);
    off();
}


void RGBLed::on()
//Switch light on with current colour until further notice. C
//Could be flashing
{
    _isOn = true;
    digitalWrite(_rPin, 255 - _r);
    digitalWrite(_gPin, 255 - _g);
    digitalWrite(_bPin, 255 - _b);
}


void RGBLed::off()
// Turn the light off
{
    _isOn = false;
    //_ledWrite( _off, _off, _off);
    digitalWrite(_rPin, 255 - _off);
    digitalWrite(_gPin, 255 - _off);
    digitalWrite(_bPin, 255 - _off);
}

/*
void _ledWrite(int r, int g, int b) {
    // translate to Hardware LOW = 255
    digitalWrite(_rPin, 255 - _r);
    digitalWrite(_gPin, 255 - _g);
    digitalWrite(_bPin, 255 - _b);
}
*/

void RGBLed::debug()
// Display its inards
{
    Serial.print("    Pins: ");
    Serial.print(_rPin);  Serial.print(" ");
    Serial.print(_gPin);  Serial.print(" ");
    Serial.print(_bPin);
    
    Serial.print("    RGB Value: ");
    Serial.print(_RGBValue);
    Serial.print("    Colours: R ");
    Serial.print(_r);  Serial.print("  G ");  Serial.print(_g);  Serial.print("  B ");  Serial.print(_b);
    
    Serial.print("    Lights On: ");
    Serial.println(_isOn);
}


/*
 void LED::setFlash(bool flashing)
 // Set this light to flash when it is turned on
 {
 _isFlashing = flashing;}
 */
