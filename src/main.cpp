#include <Arduino.h>
#include "Teensy.h"

void RespToKey(void);
uint8_t TestForKey(void);

void setup() {

/*preliminary code to turn right, hit first wall, then drive and hit the second wall*/
   // teensy.left_enc.readAndReset();
   // teensy.right_enc.readAndReset();
   // while (teensy.left_enc.read() < 80 && teensy.right_enc.read() > -115) {
   //  teensy.turnRight();
   // }
   // teensy.left_enc.readAndReset();
   // teensy.right_enc.readAndReset();
   // while (teensy.left_enc.read() < 140 && teensy.right_enc.read() < 75) {
   //    teensy.driveForwardCurve();
   // }
   // teensy.left_enc.readAndReset();
   // teensy.right_enc.readAndReset();
   // while (teensy.left_enc.read() > -380 ) {
   //    teensy.driveBackwardCurve();
   // }
   // teensy.brake();


}

void loop() {
   if (TestForKey()) {
      RespToKey();
   }
   Serial.println(teensy.left_enc.read());
   Serial.println(teensy.right_enc.read());
   delay(1000);

}



uint8_t TestForKey(void) {
  uint8_t KeyEventOccurred;
  KeyEventOccurred = Serial.available();
  return KeyEventOccurred;
}


void RespToKey(void) {
  uint8_t theKey;
  theKey = Serial.read(); //code to get key from keyboard 
  //Serial.println(theKey);
  if (theKey == 102) {
    Serial.println("forward");
    teensy.motor_A.drive(1);
    teensy.motor_B.drive(1);
    teensy.motor_C.drive(1);
    teensy.motor_D.drive(1);
  }
  if (theKey == 98) {
    Serial.println("rev");
    teensy.motor_A.drive(-1);
    teensy.motor_B.drive(-1);
    teensy.motor_C.drive(-1);
    teensy.motor_D.drive(-1);


  }
   if (theKey == 115) {
      Serial.println("stop");
      teensy.motor_A.brake();
      teensy.motor_B.brake();
      teensy.motor_C.brake();
      teensy.motor_D.brake();
   }
  // }
   if (theKey == 108) {
    Serial.println("left");
    teensy.motor_A.drive(-1);
    teensy.motor_C.drive(-1);
    teensy.motor_D.drive(-.4);
    teensy.motor_B.drive(-.4);

    
   
   }
   if (theKey == 114) {
    Serial.println("right");
    teensy.motor_A.drive(1);
    teensy.motor_C.drive(1);
    teensy.motor_D.drive(.4);
    teensy.motor_B.drive(.4);
   
    
  }
  if (theKey == 97) {
    teensy.right_enc.readAndReset();
    teensy.left_enc.readAndReset();
  }
     
  }