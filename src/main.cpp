#include <Arduino.h>
#include "Teensy.h"
#include <Metro.h>


#define LINE_LEFT_THRESH 200
#define LINE_RIGHT_THRESH 110
#define PUSH_THRESHOLD  30
#define IR_THRESHOLD  50

void turnRight(void);
void RespToKey(void);
uint8_t TestForKey(void);
void readIRSignal(void);
void checkGlobalEvents(void);
void oreintToBeacon(void);
void checkOffProcedure(void);
void calcPushState(void);
int testForTape(void);
void handleTape(int tape);

typedef enum {
  FIND_BEACON, STOP, CHECKOFF_PROCEDURE, FORWARD, BACKWARD, FULL_FWD, FULL_BACK
} States_t;


typedef enum {
  CLEAR, RESISTANCE_BACK, RESISTANCE_FWD
} States_p;



IntervalTimer IR_Signal;
IntervalTimer Encoder_Signal;

volatile int lastIRsignal = 0;
volatile bool facingSignal = false;
States_t  state;
States_p push_state;

static Metro timer = Metro(1000);
static Metro push_timer = Metro(3000);
static Metro push_state_timer = Metro(2000);
//static Metro game_timer = Metro(129000);
static Metro game_timer = Metro(129000);


//keeps track of which spot last read IR value should go
volatile int arraySpot = 0;
volatile int last_IR_vals[2];

void setup() {
   IR_Signal.begin(readIRSignal, 250);
   Encoder_Signal.begin(calcPushState, 1000000);
   state = FIND_BEACON;
   push_state = CLEAR;
   game_timer.reset();
}

int counter = 0;

void loop() {

 // Serial.println(facingSignal);
  // Serial.println(facingSignal);
  //  if (TestForKey()) {
  //     RespToKey();
  //  }
  //   delay(1000);
  //   Serial.println(push_state);
  //  Serial.println(analogRead(LINE_LEFT));
  //  Serial.println(analogRead(LINE_RIGHT));
  //  Serial.println(teensy.left_enc.read());
  //  Serial.println(teensy.right_enc.read());
 // Serial.println(push_state);

  //  if (!game_timer.check()) {
  //     checkGlobalEvents();
  //  } else {
  //    state = STOP;
  //  }
  //  switch (state) {
  //    case (FIND_BEACON): {
  //      oreintToBeacon();
  //      turnRight();
  //      state =FORWARD;
  //      break;
  //    }
  //    case (CHECKOFF_PROCEDURE):
  //       checkOffProcedure();
  //       state = STOP;
  //       break;
  //     case (STOP):
  //       teensy.brake();
  //       break;
  //     case (FORWARD):
  //       teensy.driveForwardCurve(.4);
  //       if (push_state == RESISTANCE_FWD ) {
  //         state = FULL_FWD;
  //         push_timer.reset();
  //       }
  //       break;
  //     case (FULL_FWD): {
  //       teensy.driveForward();
  //       if (push_timer.check()) {
  //         state = BACKWARD;
  //       }
  //       break;
  //     }
  //     case (BACKWARD): {
  //       teensy.driveBackwardCurve(.4);
  //       if (push_state == RESISTANCE_BACK) {
  //         state = FULL_BACK; 
  //         push_timer.reset();
  //       }
  //       break;
  //     }
  //     case (FULL_BACK): {
  //       teensy.driveBackward();
  //       if (push_timer.check()) {
  //         state = FORWARD;
  //       }
  //       break;
  //     }
  // }

}

void checkGlobalEvents() {
  int tape = testForTape();
  if (tape) {
   // Serial.println("handling tape");
    handleTape(tape);
  }
}


void handleTape(int tape) {
  push_state_timer.reset();
  switch (tape) {
    case 1: // inside triggered
      if (state == FORWARD || FULL_FWD) {
        teensy.driveBackward();
        delay(500);
        teensy.turnLeft(1);
        delay(500);
      } else if (state == BACKWARD || state == FULL_BACK) {
        teensy.driveForward();
        delay(500);
        teensy.turnRight(1);
        delay(500);
      }
      //if going forward turn left
      //if going backward turn right
      break;
    case 2://outside triggered
      if (state == FORWARD || state == FULL_FWD) {
        teensy.driveBackward();
        delay(500);
        teensy.turnRight(1);
        delay(500);
        teensy.brake();
        break;
      } else if (state == BACKWARD || FULL_BACK) {
        teensy.driveForward();
        delay(500);
        teensy.turnLeft(1);
        delay(500);
        teensy.brake();
      }
      break;
            //if going forward turn right
      //if going backward turn left

    case 3: //both triggered
      //switch directions
      return;
  }

}


//0 - nothing triggered
//1 - inside triggered
//2 - outside triggered
//3 - both triggered
int testForTape() {
  int left = analogRead(LINE_LEFT);
  int right = analogRead(LINE_RIGHT);
  if (left < LINE_LEFT_THRESH && right > LINE_RIGHT_THRESH ) {
    return 2;
  } else if (left > LINE_LEFT_THRESH && right < LINE_RIGHT_THRESH) {
    return 1;
  } else if (left < LINE_LEFT_THRESH && right < LINE_RIGHT_THRESH) {
    return 3;
  } else {
    return 0;
  }
} 

void turnRight() {
   teensy.left_enc.readAndReset();
   teensy.right_enc.readAndReset();
   while (teensy.left_enc.read() < 50 && teensy.right_enc.read() > -80) {
    teensy.turnRight(1);
   }
   teensy.brake();
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
   while (teensy.left_enc.read() < 170 && teensy.right_enc.read() < 95) {
      teensy.driveForwardCurve(.4);
   }
   teensy.left_enc.readAndReset();
   teensy.right_enc.readAndReset();
   while (teensy.left_enc.read() > -400 ) {
      teensy.driveBackwardCurve(.3);
   }
   teensy.brake();
}

void readIRSignal() {
  int IR_val = analogRead(IR_READ);
  Serial.println(IR_val);
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
      teensy.turnLeft(0.6);
      delayMicroseconds(2);
  }
//   while (beaconCount < 2) {
//     while (facingSignal) {
//       teensy.turnRight(0.5);
//       delayMicroseconds(2);

//     }
//     while (!facingSignal) {
//       teensy.turnLeft(0.5);
//       delayMicroseconds(2);
//     }
//     beaconCount +=1;
//  }
  teensy.brake();

}

volatile int lastEncoderValue = 0;
void calcPushState() {
  int val = teensy.left_enc.read();
 // Serial.println(abs(val - lastEncoderValue));
 int diff = val - lastEncoderValue;
 if (!push_state_timer.check()) {
   return;
   lastEncoderValue = val;
 }
  if (diff > 0 && diff < PUSH_THRESHOLD) {
    push_state = RESISTANCE_FWD;
  
  }else if (diff < 0 && abs(diff) < PUSH_THRESHOLD) {
      push_state = RESISTANCE_BACK;
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