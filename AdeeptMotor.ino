



/***********************************************************
File name:  AdeeptMotor.ino
Description:  
1. Under remote control mode: 
The car is completely controlled by the remote control. 
2. Under auto-control mode: 
The ultrasonic module will keep detecting obstacles in front 
of the car. When encountering and approaching one, the car will 
go backward, turn to another angle bypassing the obstacle, and 
continue to go forward. 
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2016/12/26 

Done 
  .. Simplify Auto/Remote mode
  .. Remove mode array
  .. Create subroutines for LED shifting
  .. Simplify 2 controlcar functions

Things to Try
  Create subroutines for 
    next car parameters
    Read map
  Shift some work to the handset (can deviation remain there?)

  ensure direction working OK
  can I read the motor current
  slow car gradually
  speed depends on distance delay
  check out buzzer delay
  are multiple threatds going to help
  See if rangefinder hardware is working
  Change buttons to one ping only, boolaean
  
***********************************************************/

#include <SPI.h>
#include "RF24.h"
#include <Servo.h>
#include <Horn.h>
#include <Lights.h>
#include <ServoMotor.h>
#include <Rangefinder.h>
//#include <Vector.h>

//buzzer
   const int buzzerPin = 8;  // define pin for buzzer
   Horn horn(buzzerPin);  //pinMode(buzzerPin, OUTPUT); // set buzzerPin to output mode
   bool buzzer = false;
   
// Lights
   const int RPin = A3; 
   const int GPin = A4; 
   const int BPin = A5; 
   bool lightSwitch = false;
   Lights lights;

//Servo
   const int dirServoPin = 2;              // define pin for signal line of the last servo
   // int steering = 90;
   // Servo dirServo;                  // define servo to control turning of smart car
   ServoMotor steering;

//Rangefinder
   const int ultrasonicPin = 3;            // define pin for signal line of the last servo
   const int triggerPin = 11;                  // define Trig pin for ultrasonic ranging module
   const int echoPin = 12;                  // define Echo pin for ultrasonic ranging module
   Rangefinder rangefinder;
   float looking = 90;
   
   /*
   Servo ultrasonicServo;           // define servo to control turning of ultrasonic sensor
   int servoOffset = 0;
   int maxAngle = 135;
   int minAngle = 45;
   float barDegree = 90;
   float barDistance = 0;
   float maxDistance = 200;          // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
   */


RF24 radio(9, 10);                // define the object to control NRF24L01
byte addresses[5] = "00007";      // define communication address which should correspond to remote control
int data[9]={512, 512, 0, 0, 1, 1, 512, 512, 512};  // define array used to save the communication data

const int dirAPin = 7;    // define pin used to control rotational direction of motor A
const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;    // define pin used to control rotational direction of motor B
const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B
const int snsAPin = 0;    // define pin for detecting current of motor A
const int snsBPin = 1;    // define pin for detecting current of motor B
int carSpeed = 0;
int motorOffset = 0;

bool isAutonomous = false;

#define FORWARD LOW
#define BACKWARD HIGH


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
   //dirServo.attach(dirServoPin);  // attaches the servo on servoDirPin to the servo object

   rangefinder.setPins(ultrasonicPin,triggerPin,echoPin);
   //ultrasonicServo.attach(ultrasonicPin);  // attaches the servo on ultrasonicPin to the servo object

   pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
   pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
   pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
   pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode

   
   pinMode(RPin, OUTPUT);   // set RPin to output mode
   pinMode(GPin, OUTPUT);   // set GPin to output mode
   pinMode(BPin, OUTPUT);   // set BPin to output mode

   // pinMode(trigPin, OUTPUT); // set trigPin to output mode
   // pinMode(echoPin, INPUT);  // set echoPin to input mode

   lights.setPins(RPin, GPin, BPin, RPin, GPin, BPin);
   lights.mainLights();
}


//-------------------------------------------------------------------------
// LOOP  function
//-------------------------------------------------------------------------

void loop() {
   receiveData();
   
   // if (buzzer) {horn.beep(2000);}
   if (buzzer) {tone(buzzerPin, 2000);} else {noTone(buzzerPin);}
   if (lightSwitch) {lights.nextColour();}

   if (!isAutonomous) { 
       ctrlCar (steering.pointing(), carSpeed);
       // rangefinder.point(looking);
       // int i = rangefinder.getDistance();
   } 

   if (isAutonomous) {

      rangefinder.makeMap();
   /*      
    *       int spd = 128;  // set the speed(0-255) of smart car
      int ang = 0;
      if (barDegree < 90) {ang = maxAngle;} else {ang = minAngle;}  
      if (barDistance < 20) {ctrlCar(ang, -spd);}
      else if (barDistance < 50) {ctrlCar(ang, spd);}
      else {ctrlCar(90, spd);}
      for(int i=0;i<15;i++) {
         delay(100);              // moving time time
      //   receiveData();
      }
      
      ctrlCar(90, 0);   // make the smart car stop for preparation of next scanning

       */
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
      
 //     steering = map(data[0], 0, 1023, minAngle, maxAngle); // steering is between min and max angle
 
      carSpeed = map(data[1], 0, 1023, 0, 511);         // range of speed is -255 to +255
      //Serial.print("        receiveData() - Speed:  ");
      //Serial.print(carSpeed);
      carSpeed = carSpeed -255; 
      //Serial.print("  centred:  ");
      //Serial.print(carSpeed);
     
      if (data[2]==1) {lightSwitch = true;} else {lightSwitch = false;}
      // ledSwitch = data[2]; 
      if (data[3]==1) {isAutonomous = false;Serial.print("Switch to MANUAL mode ");}    
      if (data[4]==1) {isAutonomous = true;Serial.print("Switch to AUTONOMOUS mode ");}    
      if (data[5]==1) {buzzer = true;} else {buzzer = false;}

      motorOffset = map(data[6], 0, 1023, -50, 50);

      //servoOffset = map(data[7], 0, 1023, -20, 20);
      steering.calibrate(data[7]);

      looking = rangefinder.normalise(data[8]);  // range of looking is between min and max angle 
   }
}





// make any movement parameter changes due to the hardware deviation
void ctrlCar(float _steeringAngle, float _motorSpd) {

   //_steeringAngle = constrain(_steeringAngle + servoOffset, minAngle, maxAngle);
   //dirServo.write(_steeringAngle);
   steering.point(_steeringAngle);
   
   //   Serial.print("        Control Car - Steering:  ");
   //   Serial.print(_steeringAngle);
    
   _motorSpd = constrain(_motorSpd + motorOffset, -255, 255);
   bool motorDir = _motorSpd > 0 ? BACKWARD : FORWARD;
      
   Serial.print("    ctrlCar() - motor Offset:  ");
   Serial.print(motorOffset);
   Serial.print("   Direction:  ");
   Serial.print(motorDir);
   Serial.print("  Speed: ");
   Serial.println(_motorSpd);

   digitalWrite(dirAPin, motorDir);
   digitalWrite(dirBPin, motorDir);
   analogWrite(pwmAPin, abs(_motorSpd));
   analogWrite(pwmBPin, abs(_motorSpd));

}


