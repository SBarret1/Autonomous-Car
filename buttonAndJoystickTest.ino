/*
Original Version - Website: www.adeept.com, E-mail: support@adeept.com, Author: Tom, Date: 2016/12/26 

   Intent: Send the signals from the remote to the car, in an array of size [0..9] 
   Interface: 
        HW - two dual axis joy sticks between 0 and 1023 (centred on 512)
        HW - four boolean buttons, that are true for as long as they are pressed
        HW - two potentiometers that lie between 0 and 1023
        
    Usage: Repeadedly read and send
    Translation Needed: Translate joysick X movement as 0 to the left
*/

#include <SPI.h>
#include <String.h>
#include "RF24.h"
#include <Joystick.h>
#include <Button.h>

int data[10];                  // define array used to save the communication data

const int pot6Pin = 5;        // define R6
const int pot5Pin = 4;        // define R1
const int led1Pin = 6;        // define pin for LED1 which is close to NRF24L01 and used to indicate the state of NRF24L01
const int led2Pin = 7;        // define pin for LED2 which is the mode is displayed in the car remote control mode  
const int led3Pin = 8;        // define pin for LED3 which is the mode is displayed in the car auto mode
const int APin = 2;           // define pin for D2
const int BPin = 3;           // define pin for D3
const int CPin = 4;           // define pin for D4
const int DPin = 5;           // define pin for D5
const int ultrasonicPin = 0;  // define pin for direction X of joystick U1
const int MotorPin = 1;       // define pin for direction Y of joystick U1
const int ServoPin = 2;       // define pin for direction X of joystick U2
const int sparePin = 3;       // define pin for direction Y of joystick U2
Joystick LJ;
Joystick RJ;


Button buttonA;
Button buttonB;
Button buttonC;
Button buttonD;

void setup() {
   Serial.begin(9600);
   Serial.println("Handset Setting up: ");

   LJ.setPins(ultrasonicPin, MotorPin, true, false); // X/Y
   RJ.setPins(ServoPin, sparePin, true, false);      // X/Y

   pinMode(led1Pin, OUTPUT);   // set led1Pin to output mode
   pinMode(led2Pin, OUTPUT);   // set led2Pin to output mode
   pinMode(led3Pin, OUTPUT);   // set led3Pin to output mode

   buttonA.setPins(APin, INSTANT, LOW);
   buttonB.setPins(BPin, INSTANT, LOW);
   buttonC.setPins(CPin, INSTANT, LOW);
   buttonD.setPins(DPin, INSTANT, LOW);
}



void loop() {

   // put the values of rocker, switch and potentiometer into the array
   data[0] = 1023-RJ.X();      // steering between 0 and 1023
   data[1] = LJ.Y();;          // speed between 0 and 1023
   data[2] = buttonA.read();         // Switch LED mode as int, switch to 1 is pressed
   data[3] = buttonB.read();         // Set Remote control mode as int, switch to 1 is pressed
   data[4] = buttonC.read();         // Set Autonomous mode as int, switch to 1 is pressed
   data[5] = buttonD.read();         // horn honking as int, switch to 1 is pressed
   data[8] = 1023-LJ.X(); // distance signal between 0 and 1023
   data[9] = RJ.Y();; // distance signal between 0 and 1023
   
 
   digitalWrite(led1Pin,HIGH);

   // delay for a period of time, then turn off the signal LED for next sending
   delay(2);

   digitalWrite(led1Pin,LOW);
   digitalWrite(led2Pin,data[3]);
   digitalWrite(led3Pin,data[4]);
   
   debug();
}



void debug() {
   LJ.debug(" Left", "Looking", "Speed"); 
   RJ.debug("Right", "Steering", "Spare");  
 
   buttonA.debug("A");
   buttonB.debug("B");
   buttonC.debug("C");
   buttonD.debug("D");
 
   Serial.print("    pot5Pin: ");
   Serial.print(data[6]);
   Serial.print("  pot6Pin: ");
   Serial.println(data[7]);
   
}

