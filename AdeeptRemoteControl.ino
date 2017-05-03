/***********************************************************
File name:  AdeeptRemoteControl.ino
Description:  
1.Move the sticker rightside left and right to control the direction of the car, and forward and backward to control the left and right turning of the ultrasonic module.  
2.Move the sticker leftside forward and backward to control the speed of the car going forward and backward.
3.Spin the R1 potentiometer to control the startup speed of the DC motor. 
4.Spin the R6 potentiometer to fine tune the direction of the car. 
5.Press Button A to switch the LED colors and status on the car, between white, red, green, blue and off. Press and hold it and the switching；
6.Press Button B and the car will switch to the remote control mode. At the same time, the LED2 will light up and LED3 go out accordingly, indicating the car now is controlled by the remote control. 
7.Press Button C and the car will switch to the auto-control mode. At the same time, the LED3 will light up and LED2 go out, indicating the car now moves automatically. 
8.Press Button D and the buzzer will beep. As long as you keep pressing, it will keep the beeping. The function is still active under the auto-control mode. 
The car enters the remote control mode automatically after power on. 
You can switch the status of the car by the remote control.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2016/12/26 

Also to try
  shorten data array, or even try sending it wothout the array itself
  don't send all the data every time
  investigate radio librabry - can I tell if teh communication is complete?
  is HIGH/LOW directly invertible
  What data should I send from teh dar (to express in the three LEDs)
  
***********************************************************/
#include <SPI.h>
#include "RF24.h"
RF24 radio(9, 10);            // define the object to control NRF24L01
byte addresses[5] = "00007";  // define communication address which should correspond to remote control
int data[9];                  // define array used to save the communication data
// int mode = 0;
const int pot6Pin = 5;        // define R6
const int pot5Pin = 4;        // define R1
const int led1Pin = 6;        // define pin for LED1 which is close to NRF24L01 and used to indicate the state of NRF24L01
const int led2Pin = 7;        // define pin for LED2 which is the mode is displayed in the car remote control mode  
const int led3Pin = 8;        // define pin for LED3 which is the mode is displayed in the car auto mode
const int APin = 2;           // define pin for D2
const int BPin = 3;           // define pin for D3
const int CPin = 4;           // define pin for D4
const int DPin = 5;           // define pin for D5
const int MotorPin = 1;       // define pin for direction X of joystick U2
const int ServoPin = 2;       // define pin for direction Y of joystick U1
const int ultrasonicPin = 3;  // define pin for direction x of joystick U2

void setup() {
  
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
   // data[3] = 0; // IsAutonomous? FALSE is Remote Controled
}

void loop() {
   // put the values of rocker, switch and potentiometer into the array
   data[0] = analogRead(ServoPin);      // steering between 0 and 1023
   data[1] = analogRead(MotorPin);      // speed between 0 and 1023
   data[2] = 1-digitalRead(APin);         // Switch LED mode as int, switch to 1 is pressed
   data[3] = 1-digitalRead(BPin);         // Set Remote control mode as int, switch to 1 is pressed
   data[4] = 1-digitalRead(CPin);         // Set Autonomous mode as int, switch to 1 is pressed
   data[5] = 1-digitalRead(DPin);         // horn honking as int, switch to 1 is pressed
   data[6] = analogRead(pot5Pin);       // moter speed error correction between 0 and 1023
   data[7] = analogRead(pot6Pin);       // steering/ultrasound error correction between 0 and 1023
   data[8] = analogRead(ultrasonicPin); // distance signal between 0 and 1023

   Serial.print("Steering: ");   
   Serial.print(data[0]);
   Serial.print(" Speed: ");
   Serial.print(data[1]);
   Serial.print("   Looking: ");
   Serial.print(data[8]);

   Serial.print("    A: ");
   Serial.print(data[2]);
   Serial.print(" B: ");
   Serial.print(data[3]);
   Serial.print(" C: ");
   Serial.print(data[4]);
   Serial.print(" D: ");
   Serial.println(data[5]);

   // send array data. If the sending succeeds, open signal LED
   if (radio.write( data, sizeof(data) ))
   digitalWrite(led1Pin,HIGH);

   // delay for a period of time, then turn off the signal LED for next sending
   delay(2);

   digitalWrite(led1Pin,LOW);
   digitalWrite(led2Pin,data[3]);
   digitalWrite(led3Pin,data[4]);

}
