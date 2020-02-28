#include <Arduino.h>
#include "Teensy.h"

void RespToKey(void);
uint8_t TestForKey(void);
void readIRSignal(void);
void checkGlobalEvents(void);
void oreintToBeacon(void);
void checkOffProcedure(void);

typedef enum {
  FIND_BEACON, STOP, CHECKOFF_PROCEDURE
} States_t;


IntervalTimer IR_Signal;
volatile int lastIRsignal = 0;
volatile bool facingSignal = false;
const int IR_THRESHOLD = 300;
States_t  state;

//keeps track of which spot last read IR value should go
volatile int arraySpot = 0;
volatile int last_IR_vals[2];

void setup() {
   IR_Signal.begin(readIRSignal, 250);
   state = FIND_BEACON;
}

void loop() {
  Serial.println(facingSignal);
   if (TestForKey()) {
      RespToKey();
   }
   delay(1000);
   // Serial.println(teensy.left_enc.read());
   // Serial.println(teensy.right_enc.read());

   checkGlobalEvents();
   switch (state) {
     case (FIND_BEACON): {
       oreintToBeacon();
       state = CHECKOFF_PROCEDURE;
     }
     case (CHECKOFF_PROCEDURE):
        checkOffProcedure();
        state = STOP;
      case (STOP):
        teensy.brake();
   }

}

void checkGlobalEvents() {
  //check for tape/line 
}

void checkOffProcedure() {
  /*preliminary code to turn right, hit first wall, then drive and hit the second wall*/
   teensy.left_enc.readAndReset();
   teensy.right_enc.readAndReset();
   while (teensy.left_enc.read() < 80 && teensy.right_enc.read() > -115) {
    teensy.turnRight(1);
   }
   teensy.left_enc.readAndReset();
   teensy.right_enc.readAndReset();
   while (teensy.left_enc.read() < 140 && teensy.right_enc.read() < 75) {
      teensy.driveForwardCurve();
   }
   teensy.left_enc.readAndReset();
   teensy.right_enc.readAndReset();
   while (teensy.left_enc.read() > -380 ) {
      teensy.driveBackwardCurve();
   }
   teensy.brake();
}

void readIRSignal() {
  int IR_val = analogRead(21);
  if (arraySpot < 2) {
    last_IR_vals[arraySpot] = IR_val;
    arraySpot+= 1;
    return;
  }
  if (abs(IR_val - last_IR_vals[0])> 300 ||abs(IR_val - last_IR_vals[1])> 300 ) {
    facingSignal = true;
  } else {
    facingSignal = false;
  }
  last_IR_vals[arraySpot%2] = IR_val;
  arraySpot += 1;
}

void oreintToBeacon() {
  int beaconCount = 0;
  while (!facingSignal) {
      teensy.turnLeft(0.5);
    }
  while (beaconCount < 2) {
    while (facingSignal) {
      teensy.turnRight(0.5);
    }
    while (!facingSignal) {
      teensy.turnLeft(0.5);
    }
    beaconCount +=1;
  }
  teensy.brake();

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
    teensy.driveForward();
  }
  if (theKey == 98) {
    Serial.println("rev");
    teensy.driveBackward();
  }
   if (theKey == 115) {
      Serial.println("stop");
      teensy.brake();
   }
   if (theKey == 108) {
    Serial.println("left");
    teensy.driveBackwardCurve();  
   }
   if (theKey == 114) {
    Serial.println("right");
    teensy.driveForwardCurve();
  }
  if (theKey == 97) {
    teensy.right_enc.readAndReset();
    teensy.left_enc.readAndReset();
  }
     
  }