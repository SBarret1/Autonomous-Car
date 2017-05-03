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

Things to Try
  .. Simplify Auto/Remote mode
  .. Remove mode array
  Create subroutines for 
    next car parameters
    .. LED shifting
    Read map
  Shift some work to the handset (can deviation remain there?)
  .. Simplify 2 controlcar functions
  ensure direction working OK
  can I read the motor current
  slow car gradually
  speed depends on distance delay
  check out buzzer delay
  are multiple threatds going to help
  
***********************************************************/
#include <SPI.h>
#include "RF24.h"
#include <Servo.h>

RF24 radio(9, 10);                // define the object to control NRF24L01
byte addresses[5] = "00007";      // define communication address which should correspond to remote control
int data[9]={512, 512, 0, 0, 1, 1, 512, 512, 512};  // define array used to save the communication data

Servo dirServo;                  // define servo to control turning of smart car
int dirServoPin = 2;              // define pin for signal line of the last servo

Servo ultrasonicServo;           // define servo to control turning of ultrasonic sensor
int ultrasonicPin = 3;            // define pin for signal line of the last servo

int trigPin = 0;                  // define Trig pin for ultrasonic ranging module
int echoPin = 1;                  // define Echo pin for ultrasonic ranging module
float maxDistance = 200;          // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
float soundVelocity = 340;        // Sound velocity = 340 m/s
float rangingTimeOut = 2 * maxDistance / 100 / soundVelocity * 1000000; // define the timeout(ms) for ultrasonic ranging module

// #define FORWARD HIGH
// #define BACKWARD LOW

const int dirAPin = 7;    // define pin used to control rotational direction of motor A
const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;    // define pin used to control rotational direction of motor B
const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B
const int snsAPin = 0;    // define pin for detecting current of motor A
const int snsBPin = 1;    // define pin for detecting current of motor B
const int buzzerPin = 8;  // define pin for buzzer
const int RPin = A3; 
const int GPin = A4; 
const int BPin = A5; 
int RGBVal = 0;

bool isAutonomous = false;
bool buzzer = false;
bool ledSwitch = false;
int steering = 90;
int looking = 90;
int carSpeed = 0;
int servoOffset = 0;
int motorOffset = 0;

int maxAngle = 135;
int minAngle = 45;

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
  
   dirServo.attach(dirServoPin);  // attaches the servo on servoDirPin to the servo object
   ultrasonicServo.attach(ultrasonicPin);  // attaches the servo on ultrasonicPin to the servo object

   pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
   pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
   pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
   pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode

   pinMode(buzzerPin, OUTPUT); // set buzzerPin to output mode

   pinMode(RPin, OUTPUT);   // set RPin to output mode
   pinMode(GPin, OUTPUT);   // set GPin to output mode
   pinMode(BPin, OUTPUT);   // set BPin to output mode

   pinMode(trigPin, OUTPUT); // set trigPin to output mode
   pinMode(echoPin, INPUT);  // set echoPin to input mode
}


//-------------------------------------------------------------------------
// LOOP  function
//-------------------------------------------------------------------------

void loop() {
   receiveData();
      
   if (buzzer) {tone(buzzerPin, 2000);} else {noTone(buzzerPin);}
   if (ledSwitch) {leds();}

   if (!isAutonomous) { ctrlCar (steering, carSpeed);} 
   
   if (isAutonomous) {

      byte barDistance = maxDistance; // save the minimum measured distance from obstacles
      byte barDegree;                 // save the minimum measured angel from obstacles
      byte distance;                  // save the current the measured distance from obstacles

      pointUltrasonic(minAngle);
      delay(200);

      // start to scan distance. During this progress, we will get the distance and angle from the closest obstacle
      for (byte lookingAngle = minAngle; lookingAngle < maxAngle; lookingAngle += 10) {
         pointUltrasonic(lookingAngle); // steer pan tilt to corresponding position
         delay(50);                // wait 50ms between pings (about 20 pingsc). 29ms should be the shortest delay between pings.
         receiveData();
         distance = getDistance(); // detect the current distance from obstacle with angle of pan tilt stable
         if (distance < barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
            barDegree = lookingAngle;       // save the measured angle
            barDistance = distance;     // save the measured distance
         }
      } //for
      
      pointUltrasonic(90); // servo of pan tilt turns to default position
      delay(200);
      

      int spd = 128;  // set the speed(0-255) of smart car
      
      // According to the result of scanning control action of intelligent vehicles
      int ang = 0;
      if (barDegree < 90) {ang = maxAngle;} else {ang = minAngle;}  
      if (barDistance < 20) {spd=-spd;}

      if (barDistance < 20) {ctrlCar(ang, spd);}
      else if (barDistance < 50) {ctrlCar(ang, spd);}
      else {ctrlCar(90, spd);}
         
      for(int i=0;i<15;i++) {
         delay(100);              // moving time time
         receiveData();
      }
      
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
      
      steering = data[0] = map(data[0], 0, 1023, minAngle, maxAngle); // steering is between min and max angle
      carSpeed = map(data[1], 0, 1023, -255, +255);                   // range of speed is -512 to +512
      ledSwitch = data[2];
      isAutonomous = !data[3];
      //
      buzzer = data[5];
      motorOffset = map(data[6], 0, 1023, -50, 50);
      servoOffset = map(data[7], 0, 1023, -20, 20);
      looking = map(data[8], 0, 1023, minAngle, maxAngle);  // range of looking is between min and max angle 
   }
}



// make any movement parameter changes due to the hardware deviation
void ctrlCar(byte _steeringAngle, byte _motorSpd) {

   _steeringAngle = constrain(_steeringAngle + servoOffset, minAngle, maxAngle);
   dirServo.write(_steeringAngle);
    
   _motorSpd = constrain(_motorSpd + motorOffset, -255, 255);
   bool motorDir = _motorSpd > 0 ? BACKWARD : FORWARD;
   digitalWrite(dirAPin, motorDir);
   digitalWrite(dirBPin, motorDir);
   analogWrite(pwmAPin, _motorSpd);
   analogWrite(pwmBPin, _motorSpd);
}



// make any rangefinder parameter changes due to the hardware deviation
void pointUltrasonic (byte _ultrasonicServoDegree) {

   _ultrasonicServoDegree = constrain(_ultrasonicServoDegree + servoOffset, minAngle, maxAngle);
   ultrasonicServo.write(_ultrasonicServoDegree);
}



float getDistance() {
  unsigned long pingTime; // save the high level time returned by ultrasonic ranging module
  float distance;         // save the distance away from obstacle

  // set the trigPin output 10us high level to make the ultrasonic ranging module start to measure
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // get the high level time returned by ultrasonic ranging module
  pingTime = pulseIn(echoPin, HIGH, rangingTimeOut);

  if (pingTime != 0) {  // if the measure is not overtime
    distance = pingTime * soundVelocity / 2 / 10000;  // calculate the obstacle distance(cm) according to the time of high level returned
    return distance;    // return distance(cm)
  }
  else                  // if the measure is overtime
    return maxDistance; // returns the maximum distance(cm)
}


  
void leds() {
        RGBVal++ ;
        RGBVal=RGBVal%5;

      int r = LOW; int g = LOW; int b = LOW;
      switch(RGBVal){
        case 0: r=HIGH;g=HIGH;b=HIGH;break;
        case 1: r=LOW;g=LOW;b=LOW;break;
        case 2: r=LOW;g=HIGH;b=HIGH;break;
        case 3: r=HIGH;g=LOW;b=HIGH;break;
        case 4: r=HIGH;g=HIGH;b=LOW;break;
        default: break;
      }

      digitalWrite(RPin, r);
      digitalWrite(GPin, g);
      digitalWrite(BPin, b);
  }

