//#include <Horn.h>
#include <LED.h>
#include <Lights.h>
#include <SPI.h>


//LED led1;

void setup() {
  Serial.begin(9600); // initialize serial port
  Serial.println("Starting ");
  Serial.println("  Testing LED:- ");  debugLED();
  //Serial.println("  testing Light:- ");  debugLight();
  Serial.println("Finished Testing ");
}

void loop() {
}

void debugLED() {
   const int rPin = A3; 
   const int gPin = A4; 
   const int bPin = A5; 
   
   LED led1 = LED(rPin, gPin, bPin);
   Serial.println("    Created led1"); 
   Serial.print("      ** LED should be off for three seconds"); delay(3000);
     led1.debug(); Serial.print(" ");

   Serial.println("     ** Should flash different colours - ten colours, 1 second each");
   for (int x = 0; x<10; x++) {
       led1.nextColour();
       Serial.print("            next Colour: "); led1.debug(); 
       delay(1000);
       led1.shine();     
   }

   Serial.println("    Functional Test   ");
   led1.off();             Serial.print("      ** LED should be off now:                                ");  led1.debug();  delay(3000);
   led1.setColour(255,255,255);  Serial.print("      ** colour to red, but light still off for three seconds: ");  led1.debug();  delay(3000);
   led1.shine();           Serial.print("      ** should shine red for 3 seconds:                       ");  led1.debug();  delay(3000);
   led1.off();             Serial.print("      ** off again, should be off for three seconds:           ");  led1.debug();  delay(3000);
                           Serial.print("      ** on for 2000: ");
   led1.on(2000); led1.debug(); 

}

void debugLight() {
   const int r1Pin = A0; 
   const int g1Pin = A1; 
   const int b1Pin = A2;
   const int r2Pin = A3; 
   const int g2Pin = A4; 
   const int b2Pin = A5; 

   Serial.println(" ");
   Serial.println("  Lights  ");
   Lights fL(r1Pin,  g1Pin,  b1Pin, r2Pin,  g2Pin,  b2Pin);
   fL.debug();
   delay(5000);
   
   Serial.println(" ");
   Serial.println("    Main Lights (yellow) ");
   fL.mainLights();
   fL.debug();
   delay(2000);
      
   Serial.println(" ");
   Serial.println("    Turn off Lights ");
   fL.off();
   fL.debug();
   delay(2000);
   
   Serial.println(" ");
   Serial.println("    Indicate Left ");
   //fL.indicateLeft(2000);
   fL.debug();
   //delay(2000);
   
   Serial.println(" ");
   Serial.println("    Indicate Right ");
   fL.indicateRight(600);
   delay(150);
   fL.indicateRight(600);
   delay(150);
   fL.indicateRight(600);
   delay(150);
   fL.indicateRight(600);
   fL.debug();
   
   Serial.println(" ");
   Serial.println("    Turn off Lights ");
   fL.cancelIndicating();
   fL.debug();

}

