#ifndef Teensy_h
#define Teensy_h

#include <Arduino.h>
#include <inttypes.h>
#include "Motor.h"
#include <Encoder.h>


/*----------------------------- Library Constants ---------------------------*/

#define ACC_SCL       19 //REMOVE?
#define ACC_SDA       18 //REMOVE?
#define MOTOR_FORWARD_A  4 //MOTOR A
#define MOTOR_FORWARD_B  17 //MOTOR B
#define MOTOR_FORWARD_D 22 //MOTOR C
#define MOTOR_FORWARD_C  10 //MOTOR D
#define MOTOR_BACK_A  3 //MOTOR A
#define MOTOR_BACK_B  16 //MOTOR B
#define MOTOR_BACK_D  23 //MOTOR C
#define MOTOR_BACK_C  9 //MOTOR D
#define LINE_LEFT       0
#define LINE_RIGHT      1
#define PRESS_FRONT     14 //REMOVE?
#define PRESS_BACK      15 //REMOVE?
#define IR_READ         21
#define ENCODER_LEFT_A    2
#define ENCODER_LEFT_B    5
#define ENCODER_RIGHT_A    7
#define ENCODER_RIGHT_B    8
#define SERVO_ANALOG_OUT    6 //REMOVE?
#define SERVO_DIGITAL_OUT    20  //REMOVE?
 
//Blocks
#define FRONT   0
#define BACK   1
 
//Line
#define LEFT   0
#define RIGHT   1
 
#define LINE_THRESHOLD 750
#define ACC_THRESHOLD .1

class TeensyClass
{
  public:
    TeensyClass();
    
    Motor motor_A = Motor(MOTOR_FORWARD_A, MOTOR_BACK_A);
    Motor motor_B = Motor(MOTOR_FORWARD_B, MOTOR_BACK_B);
    Motor motor_C = Motor(MOTOR_FORWARD_C, MOTOR_BACK_C);
    Motor motor_D = Motor(MOTOR_FORWARD_D, MOTOR_BACK_D);
    Encoder left_enc = Encoder(ENCODER_LEFT_A, ENCODER_LEFT_B);
    Encoder right_enc = Encoder(ENCODER_RIGHT_A, ENCODER_RIGHT_B);

    void driveForward();
    void driveBackward();
    void driveBackLeft();
    void turnRight(double speed);
    void turnLeft(double speed);
    void brake();
    void driveForwardCurve();
    void driveBackwardCurve();



    
	
  private:
    void begin();
    

};
extern TeensyClass teensy;

#endif