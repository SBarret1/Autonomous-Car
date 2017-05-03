/*
  Servo_cpp - Library for Servos
*/

#ifndef Servo_h
#define Servo_h

#include "Arduino.h"
//#include <Servo.h>
#include "ServoMotor.h"
#include "Rangefinder.h"


ServoMotor::Rangefinder(){
}

ServoMotor::setPins(int servoPin)
{
    _serverMotor.setPins(int servoPin);
}


ServoMotor::point(int angle)
{
    _serverMotor.point(int angle);
}


ServoMotor::calibrate(int offset)
{
    _serverMotor.calibrate(int offset);
}


ServoMotor::getDistance()
{
    float soundVelocity = 340;        // Sound velocity = 340 m/s
    float rangingTimeOut = 2 * maxDistance / 100 / soundVelocity * 1000000; // define the timeout(ms) for ultrasonic ranging module
    
    unsigned long pingTime; // save the high level time returned by ultrasonic ranging module
    float distance;         // save the distance away from obstacle
    
    // set the trigPin output 10us high level to make the ultrasonic ranging module start to measure
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // get the high level time returned by ultrasonic ranging module
    pingTime = pulseIn(echoPin, HIGH, rangingTimeOut);
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
        return maxDistance; // returns the maximum distance(cm)
}



ServoMotor::makeMap()
{
    barDistance = maxDistance; // save the minimum measured distance from obstacles
    byte distance;                  // save the current the measured distance from obstacles
    
    pointUltrasonic(minAngle);
    delay(200);
    
    // start to scan distance. During this progress, we will get the distance and angle from the closest obstacle
    for (byte lookingAngle = minAngle; lookingAngle < maxAngle; lookingAngle += 10) {
        pointUltrasonic(lookingAngle); // steer pan tilt to corresponding position
        delay(50);                // wait 50ms between pings (about 20 pingsc). 29ms should be the shortest delay between pings.
        //receiveData();
        distance = getDistance(); // detect the current distance from obstacle with angle of pan tilt stable
        Serial.println();
        Serial.print("   test theta:  ");
        Serial.print(lookingAngle);
        Serial.print("  test distance: ");
        Serial.print(distance);
        if (distance < barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
            barDegree = lookingAngle;       // save the measured angle
            barDistance = distance;     // save the measured distance
            
        }
    } //for
    Serial.println();
    Serial.print("   theta:  ");
    Serial.print(barDegree);
    Serial.print("  distance: ");
    Serial.print(barDistance);
    pointUltrasonic(90); // servo of pan tilt turns to default position
    delay(200);
}


ServoMotor::debug()
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
