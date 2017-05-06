/*
  Ultrasonic_h - Library for Ultrasonic device only (independent of its servoMotor)
 */

#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(){
}

void Ultrasonic::setPins(int triggerPin, int echoPin)
{
    _triggerPin = triggerPin;
    _echoPin = echoPin;

    pinMode(triggerPin, OUTPUT); // set trigPin to output mode
    pinMode(echoPin, INPUT);  // set echoPin to input mode
}


int Ultrasonic::getDistance()
{
    float soundVelocity = 340;        // Sound velocity = 340 m/s
    float _maxDistance = 200;      // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
    float rangingTimeOut = 2 * _maxDistance / 100 / soundVelocity * 1000000; // define the timeout(ms) for ultrasonic ranging module
    
    unsigned long pingTime; // save the high level time returned by ultrasonic ranging module
    float distance;         // save the distance away from obstacle
    
    // set the trigPin output 10us high level to make the ultrasonic ranging module start to measure
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    
    // get the high level time returned by ultrasonic ranging module
    pingTime = pulseIn(_echoPin, HIGH, rangingTimeOut);
    distance = (pingTime / 2) * 0.0344;
    
    Serial.println("   ");
    Serial.print("    Ping time = ");
    Serial.print(pingTime);
    Serial.print("    distance = ");
    Serial.print(distance);
    Serial.print (" cm     ");
    
    if (distance >= 400 || distance <= 2) {
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.print("Out of range");
        
    }
    
    if (pingTime != 0) {  // if the measure is not overtime
        
        //distance = pingTime * soundVelocity / 2 / 10000;  // calculate the obstacle distance(cm) according to the time of high level returned
        // Serial.print("   getDistance() - distance: ");
        //Serial.println(distance);
        return distance;    // return distance(cm)
    }
    else                  // if the measure is overtime
        return _maxDistance; // returns the maximum distance(cm)
}


void Ultrasonic::debug()
{
    /*
     Serial.print("  Details of Servo:  Pin ");
    Serial.print(_servoPin);
    Serial.print(" facing ");
    Serial.print(_angle);
    Serial.print(" degrees, including an offset of ");
    Serial.print(_offset);
    Serial.print(" degrees. Constrained to between  ");
    Serial.print(_minAngle);
    Serial.print(" and ");
    Serial.print(_maxAngle);
    Serial.println(" degrees. ");
     */
}
