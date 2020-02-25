#include "Interface.h"
#include "Arduino.h"
#include <Wire.h>
 
InterfaceClass interface;
 
/*-------------------- Module Code: Public Functions -----------------------*/
 
InterfaceClass::InterfaceClass()
{
 begin();
}
 
void InterfaceClass::setSpeed(int8_t motor, int8_t speed, int8_t direction) {
 
  // switch (motor) {
  //   case MOTOR_LEFT_FRONT:
  //     break;
  //   case MOTOR_RIGHT_FRONT:
  //     break;
  //   case MOTOR_LEFT_BACK:
  //     break;
  //   case MOTOR_RIGHT_BACK:
  //     break;
  //   default:    // Should never get into an unhandled state
  //     Serial.println("Motor Error");
  // }
 
  // switch (direction) {
  //   case DIR_CCW:
  //     break;
  //   case DIR_CW:
  //     break;
  //   default:    
  //     Serial.println("Direction Error");
  // }
 
}
 
uint16_t InterfaceClass::LineRight() {
  int lineSignal;
  lineSignal = analogRead(LINE_RIGHT);
 
  return (lineSignal < LINE_THRESHOLD);
}
 
uint16_t InterfaceClass::LineLeft() {
  int lineSignal;
  lineSignal = analogRead(LINE_LEFT);
 
  return (lineSignal < LINE_THRESHOLD);
}
 
/*Digital version
uint16_t interfaceClass::LineRight() {
  int lineSignal;
  lineSignal = digitalRead(LINE_RIGHT);
 
  return lineSignal;
}
 
uint16_t interfaceClass::LineLeft() {
  int lineSignal;
  lineSignal = digitalRead(LINE_LEFT);
 
  return lineSignal;
}
*/
 
uint16_t InterfaceClass::AccelRead(uint8_t side) {
  //This might not work with I2C - we'll figure it out
  int isAccelerating;
  float ax, ay, az;
 
  sensors_event_t aevent, mevent;
 
  switch (side) {
    case FRONT:
      accelFront.getEvent(&aevent, &mevent);
      break;
    case BACK:
      accelBack.getEvent(&aevent, &mevent);
      break;
    default:    // Should never get into an unhandled state
      Serial.println("Acceleration Error");
  }
  ax = aevent.acceleration.x;
  ay = aevent.acceleration.y;
  az = aevent.acceleration.z;
 
  isAccelerating = (abs(ax) > ACC_THRESHOLD) || (abs(ay) > ACC_THRESHOLD) || (abs(az) > ACC_THRESHOLD);
 
  return isAccelerating;
}
 
 
uint16_t InterfaceClass::PressureRead(uint8_t side) {
  int pressure = 0;
   
  switch (side) {
    case FRONT:
      pressure = analogRead(PRESS_FRONT); 
      break;
    case BACK:
      pressure = analogRead(PRESS_BACK); 
      break;
    default:    
      Serial.println("Direction Error");
  }
 
  return pressure;
}
 
/*-------------------- Module Code: Private Functions ----------------------*/
 
void InterfaceClass::AccelerometerSetup() {
  accelFront = Adafruit_FXOS8700(0x1200A, 0x1200B);
  accelBack = Adafruit_FXOS8700(0x8700A, 0x8700B);
 
  if (!accelFront.begin(ACCEL_RANGE_2G)) {
    /* There was a problem detecting the FXOS8700 ... check your connections */
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while (1);
  }
 
  if (!accelBack.begin(ACCEL_RANGE_2G)) {
    /* There was a problem detecting the FXOS8700 ... check your connections */
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while (1);
  }
 
  sensor_t accel, mag;
  accelFront.getSensor(&accel, &mag);
  accelBack.getSensor(&accel, &mag);
 
}
 
//  Setup for RaptorClass functionality
void InterfaceClass::begin( ) { 
  Wire.begin();
  Serial.begin(9600);
  Wire.setSDA(ACC_SDA);
  Wire.setSCL(ACC_SCL);
 
  //Sensor inputs
  pinMode(LINE_LEFT, INPUT);
  pinMode(LINE_RIGHT, INPUT);
  pinMode(PRESS_FRONT, INPUT);
  pinMode(PRESS_BACK, INPUT);
  pinMode(IR_READ, INPUT);
 
  //Motor outputs
  pinMode(MOTOR_FORWARD_A, OUTPUT);
  pinMode(MOTOR_FORWARD_B, OUTPUT);
  pinMode(MOTOR_FORWARD_C, OUTPUT);
  pinMode(MOTOR_FORWARD_D, OUTPUT);
  pinMode(MOTOR_BACK_A, OUTPUT);
  pinMode(MOTOR_BACK_B, OUTPUT);
  pinMode(MOTOR_BACK_C, OUTPUT);
  pinMode(MOTOR_BACK_D, OUTPUT);
  analogWrite(MOTOR_FORWARD_A,0);
  analogWrite(MOTOR_FORWARD_B,0);
  analogWrite(MOTOR_FORWARD_C,0);
  analogWrite(MOTOR_FORWARD_D,0);
  analogWrite(MOTOR_BACK_A,0);
  analogWrite(MOTOR_BACK_B,0);
  analogWrite(MOTOR_BACK_C,0);
  analogWrite(MOTOR_BACK_D,0);
 
  //Encoder inputs
  pinMode(ENCODER_LEFT_A,INPUT);
  pinMode(ENCODER_LEFT_B,INPUT);
  pinMode(ENCODER_RIGHT_A,INPUT);
  pinMode(ENCODER_RIGHT_B,INPUT);
 
 
  //  Set up 5th motor
  pinMode(SERVO_ANALOG_OUT, OUTPUT);
  pinMode(SERVO_DIGITAL_OUT, OUTPUT);
  digitalWrite(SERVO_DIGITAL_OUT, LOW);
  analogWrite(SERVO_ANALOG_OUT, 0);
 
  AccelerometerSetup();
 
}