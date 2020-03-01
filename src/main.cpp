#include <Arduino.h>
#include "Teensy.h"
#include <Metro.h>
void RespToKey(void);
uint8_t TestForKey(void);
void readIRSignal(void);
void checkGlobalEvents(void);
void oreintToBeacon(void);
void checkOffProcedure(void);
void calcPushState(void);

typedef enum {
  FIND_BEACON, STOP, CHECKOFF_PROCEDURE
} States_t;


typedef enum {
  CLEAR, RESISTANCE
} States_p;



IntervalTimer IR_Signal;
IntervalTimer Encoder_Signal;

volatile int lastIRsignal = 0;
volatile bool facingSignal = false;
const int IR_THRESHOLD = 100;
States_t  state;
States_p push_state;

static Metro timer = Metro(1000);

//keeps track of which spot last read IR value should go
volatile int arraySpot = 0;
volatile int last_IR_vals[2];

void setup() {
   IR_Signal.begin(readIRSignal, 250);
   Encoder_Signal.begin(calcPushState, 1000000);
   state = FIND_BEACON;
   push_state = CLEAR;
}

int counter = 0;

void loop() {

 // Serial.println(facingSignal);
  // Serial.println(facingSignal);
   if (TestForKey()) {
      RespToKey();
   }
   delay(1000);
  //  Serial.println(teensy.left_enc.read());
  //  Serial.println(teensy.right_enc.read());
 // Serial.println(push_state);

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
   while (teensy.left_enc.read() < 70 && teensy.right_enc.read() > -100) {
    teensy.turnRight(1);
   }
   teensy.left_enc.readAndReset();
   teensy.right_enc.readAndReset();
   while (teensy.left_enc.read() < 140 && teensy.right_enc.read() < 75) {
      teensy.driveForwardCurve(.4);
   }
   teensy.left_enc.readAndReset();
   teensy.right_enc.readAndReset();
   while (teensy.left_enc.read() > -380 ) {
      teensy.driveBackwardCurve(.3);
   }
   teensy.brake();
}

void readIRSignal() {
  int IR_val = analogRead(IR_READ);
  if (arraySpot < 2) {
    last_IR_vals[arraySpot] = IR_val;
    arraySpot+= 1;
    return;
  }
  if (abs(IR_val - last_IR_vals[0])> IR_THRESHOLD 
  ||abs(IR_val - last_IR_vals[1])> IR_THRESHOLD ) {
    facingSignal = true;
  } else {
    facingSignal = false;
  }
  last_IR_vals[arraySpot%2] = IR_val;
  arraySpot += 1;
}

void oreintToBeacon() {
  //int beaconCount = 0;
  while (!facingSignal) {
      teensy.turnLeft(0.5);
      delayMicroseconds(2);
  }
  // while (beaconCount < 2) {
  //   while (facingSignal) {
  //     teensy.turnRight(0.5);
  //     delayMicroseconds(2);

  //   }
  //   while (!facingSignal) {
  //     teensy.turnLeft(0.5);
  //     delayMicroseconds(2);
  //   }
  //   beaconCount +=1;
 // }
  teensy.brake();

}

volatile int lastEncoderValue = 0;
const int PUSH_THRESHOLD = 30;
void calcPushState() {
  int val = teensy.left_enc.read();
 
  if (abs(val - lastEncoderValue) < PUSH_THRESHOLD) {
    push_state = RESISTANCE;
  } else {
    push_state = CLEAR;
  }
  lastEncoderValue = val;
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
    // timer.reset();
    // while (!(timer.check())) {
    //   teensy.driveForward();
    // }
    // teensy.brake();
  }
  if (theKey == 98) {
    Serial.println("rev");
    teensy.driveBackward();
    // timer.reset();
    // while (!(timer.check())) {
    //   teensy.driveBackward();
    // }
    // teensy.brake();
  }
   if (theKey == 115) {
      Serial.println("stop");
      teensy.brake();
   }
   if (theKey == 108) {
    Serial.println("left");
    teensy.driveBackwardCurve(.3);
    // timer.reset();
    
   }
   if (theKey == 114) {
    Serial.println("right");
    teensy.driveForwardCurve(.25);
    // timer.reset();
    // while (!(timer.check())) {
    //   teensy.driveForwardCurve(.25);
    // }
    // teensy.brake();
  }
  if (theKey == 97) {
    teensy.right_enc.readAndReset();
    teensy.left_enc.readAndReset();
  }
     
  }