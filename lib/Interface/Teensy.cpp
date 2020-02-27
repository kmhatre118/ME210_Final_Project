#include "Teensy.h"

TeensyClass teensy;

TeensyClass::TeensyClass() {
    begin();
}

void TeensyClass::driveForward() {
   motor_A.drive(1);
   motor_B.drive(1);
   motor_C.drive(1);
   motor_D.drive(1);
}

void TeensyClass::driveBackward() {
  teensy.motor_A.drive(-1);
  teensy.motor_B.drive(-1);
  teensy.motor_C.drive(-1);
  teensy.motor_D.drive(-1);
}

void TeensyClass::turnLeft() {
  teensy.motor_A.drive(-1);
  teensy.motor_C.drive(-1);
  teensy.motor_D.drive(1);
  teensy.motor_B.drive(1);
}

void TeensyClass::turnRight() {
  teensy.motor_A.drive(1);
  teensy.motor_C.drive(1);
  teensy.motor_D.drive(-1);
  teensy.motor_B.drive(-1);
}

void TeensyClass::brake() {
   teensy.motor_A.brake();
   teensy.motor_B.brake();
   teensy.motor_C.brake();
   teensy.motor_D.brake();
}

void TeensyClass::driveBackwardCurve() {
  teensy.motor_A.drive(-1);
  teensy.motor_C.drive(-1);
  teensy.motor_D.drive(-.3);
  teensy.motor_B.drive(-.3);

}

void TeensyClass::driveForwardCurve() {
   teensy.motor_A.drive(1);
   teensy.motor_C.drive(1);
   teensy.motor_D.drive(.4);
   teensy.motor_B.drive(.4);
}
void TeensyClass::begin() {
  pinMode(MOTOR_FORWARD_A, OUTPUT);
  pinMode(MOTOR_FORWARD_B, OUTPUT);
  pinMode(MOTOR_FORWARD_C, OUTPUT);
  pinMode(MOTOR_FORWARD_D, OUTPUT);
  pinMode(MOTOR_BACK_A, OUTPUT);
  pinMode(MOTOR_BACK_B, OUTPUT);
  pinMode(MOTOR_BACK_C, OUTPUT);
  pinMode(MOTOR_BACK_D, OUTPUT);



  //Sensor inputs
  pinMode(LINE_LEFT, INPUT);
  pinMode(LINE_RIGHT, INPUT);
  pinMode(PRESS_FRONT, INPUT);
  pinMode(PRESS_BACK, INPUT);
  pinMode(IR_READ, INPUT);

 

  //Encoder inputs
  // pinMode(ENCODER_LEFT_A,INPUT);
  // pinMode(ENCODER_LEFT_B,INPUT);
  // pinMode(ENCODER_RIGHT_A,INPUT);
  // pinMode(ENCODER_RIGHT_B,INPUT);
 
 
  //  Set up 5th motor
  pinMode(SERVO_ANALOG_OUT, OUTPUT);
  pinMode(SERVO_DIGITAL_OUT, OUTPUT); 



}