/*
 
LED_h - Library to operate a single RGB LED
 
 Purpose: Operate a single RGB LED, directly to the hardware, with inputs 0 to 255 for each colour

 
 Contract  ----------------------------------------------
 
   Preconditions: Each input needs to be between 0 and 255. 255 means on, 0 meean off

   Guarantee: Light up the LED according to the three inputs
 
   Finite State Machine: First setPins, then repeatedly (setColour or NextColour, then switch on or shine to illuminate) then off.
 
 
 INTERNAL ----------------------------------------------
 
   Translation Needed: From Hardware - High as a parameter need to be convered to LOW as an input to the hardware


 
   Workarounds:
       In the absence of the three parameter constructor working, need to create bare, then setPins
 
   To Do:
       Will Need to code flashing lights, that remember the prior colour
 
   Issues
       1. set colour sets the light colour, but dosn't set RGBValue to the right number
       2. Does on(duration) stop everything for 2 seconds?
       3. Can I make LOW represent off?
       4. Can I do colours beyond just HIGH and LOW - with analogWrite(pin, vlaue) where value 0-255
 
*/

#include "Arduino.h"
#include "LED.h"


LED::LED()
{
    _rPin=0;
    _gPin=0;
    _bPin=0;
    
    _r=_off;
    _g=_off;
    _b=_off;
    _RGBValue = 50;
    
    _isOn = false;
}


LED::LED(int rPin, int gPin, int bPin)
{
    _rPin=rPin;
    _gPin=gPin;
    _bPin=bPin;
    
    pinMode(_rPin, OUTPUT);   // set RPin to output mode
    pinMode(_gPin, OUTPUT);   // set GPin to output mode
    pinMode(_bPin, OUTPUT);   // set BPin to output mode
    
    _r=HIGH; // HIGH is off
    _g=HIGH; // HIGH is off
    _b=HIGH; // HIGH is off
    
    _RGBValue = 0;
    _isOn = false;
}


void LED::setPins(int rPin, int gPin, int bPin){
    _rPin=rPin;
    _gPin=gPin;
    _bPin=bPin;
    pinMode(_rPin, OUTPUT);   // set RPin to output mode
    pinMode(_gPin, OUTPUT);   // set GPin to output mode
    pinMode(_bPin, OUTPUT);   // set BPin to output mode
    _r=_off; // HIGH is off
    _g=_off; // HIGH is off
    _b=_off; // HIGH is off
    
    //_ledWrite(_r,_g,_b);
    digitalWrite(_rPin, 255 - _r);
    digitalWrite(_gPin, 255 - _g);
    digitalWrite(_bPin, 255 - _b);
    _RGBValue = 0;
    _isOn = false;
}


void LED::setColour(int r, int g, int b)
{
    // Change to a specific colour, but don't automatically turn it on
    // Each colour element should be either HIGH or LOW
    _r=r;
    _g=g;
    _b=b;
}


void LED::nextColour()
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


void LED::on(int duration)
// Switch light on for a number of milliseconds
{
    _isOn = true;
    //_ledWrite(_r,_g,_b);
    digitalWrite(_rPin, 255 - _r);
    digitalWrite(_gPin, 255 - _g);
    digitalWrite(_bPin, 255 - _b);
    delay(duration);
    off();
}


void LED::shine()
//Switch light on with current colour until further notice. C
//Could be flashing
{
    _isOn = true;
    //_ledWrite(_r,_g,_b);
    digitalWrite(_rPin, 255 - _r);
    digitalWrite(_gPin, 255 - _g);
    digitalWrite(_bPin, 255 - _b);
}


void LED::off()
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

void LED::debug()
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
