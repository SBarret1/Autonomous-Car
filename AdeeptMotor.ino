//#include <vector.h>

/*
   Original Version - Website: www.adeept.com, E-mail: support@adeept.com, Author: Tom, Date: 2016/12/26 

   Intent: 
   Interface: 
   Usage: 
   Choices: 
*/

#include <SPI.h>
#include "RF24.h"
#include <Servo.h>
#include <Horn.h>
#include <Map.h>
#include <Headlamps.h>
#include <ServoMotor.h>
#include <Engine.h>
#include <Rangefinder.h>
#include <ArduinoSTL.h>

//buzzer
   const int buzzerPin = 8;  
   Horn horn(buzzerPin);  
   bool buzzer = false;
   
// Lights
   const int RPin = A3; 
   const int GPin = A4; 
   const int BPin = A5; 
   bool lightSwitch = false;
   Headlamps lights;

//Servo
   const int dirServoPin = 2;              // define pin for signal line of the last servo
   ServoMotor steering;

//Rangefinder
   const int ultrasonicPin = 3;            // define pin for signal line of the last servo
   const int triggerPin = 11;              // define Trig pin for ultrasonic ranging module
   const int echoPin = 12;                 // define Echo pin for ultrasonic ranging module
   int looking;
   Rangefinder rangefinder;
 
// Engine
   const int dirAPin = 7;    // define pin used to control rotational direction of motor A
   const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
   const int dirBPin = 4;    // define pin used to control rotational direction of motor B
   const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B
   // const int snsAPin = 0;    // define pin for detecting current of motor A
   // const int snsBPin = 1;    // define pin for detecting current of motor B
   Engine engine;
   int carSpeed = 0;

//Radio
   RF24 radio(9, 10);                // define the object to control NRF24L01
   byte addresses[5] = "00007";      // define communication address which should correspond to remote control
   int data[9]={512, 512, 0, 0, 1, 1, 512, 512, 512};  // define array used to save the communication data

bool isAutonomous = false;

// #define FORWARD LOW
// #define BACKWARD HIGH


//-------------------------------------------------------------------------
// SETUP function
//-------------------------------------------------------------------------

void setup() {
 
 radio.begin();                      // initialize RF24
   radio.setRetries(0, 15);            // set retries times
   radio.setPALevel(RF24_PA_LOW);      // set power
   radio.openReadingPipe(1, addresses);// open delivery channel
   radio.startListening();             // start monitoring

   Serial.begin(9600); // initialize serial port

   steering.setPins(dirServoPin);           // attaches the servo on servoDirPin to the servo object
   rangefinder.setPins(ultrasonicPin,triggerPin,echoPin);
   engine.setPins(dirAPin,pwmAPin,dirBPin,pwmBPin);
   lights.setPins(RPin, GPin, BPin, RPin, GPin, BPin);
}


//-------------------------------------------------------------------------
// LOOP  function
//-------------------------------------------------------------------------

void loop() {
   receiveData();
   
   if (buzzer) {tone(buzzerPin, 2000);} else {noTone(buzzerPin);}
   if (lightSwitch) {lights.nextColour();lights.on();}

   if (!isAutonomous) { 
       ctrlCar (steering.pointing(), engine.speed());
       rangefinder.point(looking);
   } 

   if (isAutonomous) {
      Map m = rangefinder.makeMap();
      Polar p = m.nearest();
      int dist = p.distance();
      int ang = p.angle();
      int spd = 128;                  // set the speed(0-255) of smart car

      if (ang < 90) {ang = steering.max();} else {ang = steering.min();}  
      if (dist < 20) {ctrlCar(ang, -spd);}
      else if (dist < 50) {ctrlCar(ang, spd);}
      else {ctrlCar(90, spd);}
      delay(1500);   
      ctrlCar(90, 0);   // make the smart car stop for preparation of next scanning
   } //if !isAutonomous
   
   // send motor current to serial port  
   //  float iMotorA = analogRead(snsAPin) * 5.0 / 1024 / 30 / 0.05;
   //  float iMotorB = analogRead(snsBPin) * 5.0 / 1024 / 30 / 0.05;

} // loop



//-------------------------------------------------------------------------
// other functions
//-------------------------------------------------------------------------

void receiveData() {
   if (radio.available()) {             // if receive the data
      while (radio.available()) {         // read all the data
         radio.read( data, sizeof(data) ); // read data
      }
      
      carSpeed = map(data[1], 0, 1023, 0, 511);         // range of speed is -255 to +255
      carSpeed = carSpeed -255; 

      if (data[2]==1) {lightSwitch = true;} else {lightSwitch = false;}
      if (data[3]==1) {isAutonomous = false;Serial.print("Switch to MANUAL mode ");}    
      if (data[4]==1) {isAutonomous = true;Serial.print("Switch to AUTONOMOUS mode ");}    
      if (data[5]==1) {buzzer = true;} else {buzzer = false;}

      engine.calibrate(data[6]);
      steering.calibrate(data[7]);
      looking = rangefinder.normalise(data[8]);  // range of looking is between min and max angle 
   }
}


// make any movement parameter changes due to the hardware deviation
void ctrlCar(float steeringAngle, float motorSpd) {
   steering.point(steeringAngle);
   engine.drive(motorSpd); 
}


