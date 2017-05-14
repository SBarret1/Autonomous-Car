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
    float soundVelocity = 343;        // Sound velocity = 340 m/s
    float _maxDistance = 200;      // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
    float rangingTimeOut = 2 * (_maxDistance / 100) / (soundVelocity * 1000000); // define the timeout(ms) for ultrasonic ranging module
    
    unsigned long pingTime; // save the high level time returned by ultrasonic ranging module
    float distance;         // save the distance away from obstacle
    
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    
    // get the high level time returned by ultrasonic ranging module
    pingTime = pulseIn(_echoPin, HIGH, rangingTimeOut);
    distance = (pingTime / 2) * 0.0344;
    
    Serial.println("  Distance() ");
    Serial.print("    Ping time = ");
    Serial.print(pingTime);
    Serial.print("    distance = ");
    Serial.print(distance);
    Serial.print (" cm     ");
    
    if (distance >= 400 || distance <= 2) {
        Serial.print("Out of range");
    }
    
    if (pingTime != 0) {  // if the measure is not overtime

        Serial.print (" - returned distance     ");
        return distance;    // return distance(cm)
    }
    else                  // if the measure is overtime
        Serial.print (" - returned maxDistance     ");
    return _maxDistance; // returns the maximum distance(cm)
}


void Ultrasonic::debug()
{
    Serial.print("  Details of Ultrasonic Sensor:  TriggerPin ");
    Serial.print(_triggerPin);
    Serial.print(" , EchoPin ");
    Serial.print(_echoPin);
    Serial.println(" ");

}
