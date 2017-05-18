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
#include "RF24.h"
#include <Joystick.h>

RF24 radio(9, 10);            // define the object to control NRF24L01
byte addresses[] = "00007";  // define communication address which should correspond to remote control
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


void setup() {
  LJ.setPins(ultrasonicPin, MotorPin); // X/Y
  RJ.setPins(ServoPin, sparePin);      // X/Y

  
   Serial.begin(9600);
  
   radio.begin();                      // initialize RF24
   radio.setRetries(0, 15);            // set retries times
   radio.setPALevel(RF24_PA_LOW);      // set power
   radio.openWritingPipe(addresses);   // open delivery channel
   radio.stopListening();              // stop monitoring

   pinMode(led1Pin, OUTPUT);   // set led1Pin to output mode
   pinMode(led2Pin, OUTPUT);   // set led2Pin to output mode
   pinMode(led3Pin, OUTPUT);   // set led3Pin to output mode

   pinMode(APin, INPUT_PULLUP);   // set APin to input mode. Normal is 1, pressed is 0
   pinMode(BPin, INPUT_PULLUP);   // set BPin to input mode. Normal is 1, pressed is 0
   pinMode(CPin, INPUT_PULLUP);   // set CPin to input mode. Normal is 1, pressed is 0
   pinMode(DPin, INPUT_PULLUP);   // set DPin to input mode  . Normal is 1, pressed is 0
}



void loop() {

   // put the values of rocker, switch and potentiometer into the array
   data[0] = 1023-RJ.X();      // steering between 0 and 1023
   data[1] = LJ.Y();;          // speed between 0 and 1023
   data[2] = 1-digitalRead(APin);         // Switch LED mode as int, switch to 1 is pressed
   data[3] = 1-digitalRead(BPin);         // Set Remote control mode as int, switch to 1 is pressed
   data[4] = 1-digitalRead(CPin);         // Set Autonomous mode as int, switch to 1 is pressed
   data[5] = 1-digitalRead(DPin);         // horn honking as int, switch to 1 is pressed
   data[6] = analogRead(pot5Pin);       // moter speed error correction between 0 and 1023
   data[7] = analogRead(pot6Pin);       // steering/ultrasound error correction between 0 and 1023
   data[8] = 1023-LJ.X(); // distance signal between 0 and 1023
   data[9] = RJ.Y();; // distance signal between 0 and 1023
   
   // send array data. If the sending succeeds, open signal LED
   if (radio.write( data, sizeof(data) ))
   digitalWrite(led1Pin,HIGH);

   // delay for a period of time, then turn off the signal LED for next sending
   delay(2);

   digitalWrite(led1Pin,LOW);
   digitalWrite(led2Pin,data[3]);
   digitalWrite(led3Pin,data[4]);
   
   debug();
}



void debug() {
   LJ.debug();
   RJ.debug();
   
   Serial.print("   Looking: ");
   Serial.print(data[8]);
   Serial.print(" Speed: ");
   Serial.print(data[1]);
   
   Serial.print(" Steering: ");   
   Serial.print(data[0]);
   Serial.print(" Spare: ");
   Serial.print(data[9]);

   Serial.print("    A: ");
   Serial.print(data[2]);
   Serial.print(" B: ");
   Serial.print(data[3]);
   Serial.print(" C: ");
   Serial.print(data[4]);
   Serial.print(" D: ");
   Serial.print(data[5]);
 
   Serial.print("    pot5Pin: ");
   Serial.print(data[6]);
   Serial.print("  pot6Pin: ");
   Serial.println(data[7]);
}

