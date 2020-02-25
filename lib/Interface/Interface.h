#ifndef Interface_h
#define Interface_h
 
#include <inttypes.h>
#include "Adafruit_FXOS8700.h"
#include "Motor.h"
#include "Adafruit_Sensor.h"

 
/*----------------------------- Library Constants ---------------------------*/
/* Note: Some lines have been commented out to preserve the original Sparki
 * pin mappings for potential future use
 */
 
 
 
#define ACC_SCL       19 //REMOVE?
#define ACC_SDA       18 //REMOVE?
#define MOTOR_FORWARD_A  3 //MOTOR A
#define MOTOR_FORWARD_B  16 //MOTOR B
#define MOTOR_FORWARD_C  22 //MOTOR C
#define MOTOR_FORWARD_D  9 //MOTOR D
#define MOTOR_BACK_A  4 //MOTOR A
#define MOTOR_BACK_B  17 //MOTOR B
#define MOTOR_BACK_C  23 //MOTOR C
#define MOTOR_BACK_D  10 //MOTOR D
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
 
 
// defines for left and right motors
// #define MOTOR_LEFT_FRONT    0
// #define MOTOR_RIGHT_FRONT   1
// #define MOTOR_LEFT_BACK     2
// #define MOTOR_RIGHT_BACK    3
 
//Blocks
#define FRONT   0
#define BACK   1
 
//Line
#define LEFT   0
#define RIGHT   1
 
#define LINE_THRESHOLD 750
#define ACC_THRESHOLD .1
 
// defines for direction
#define DIR_CCW -1
#define DIR_CW   1
 
class InterfaceClass {
  public:
    InterfaceClass();
 
    void setSpeed(int8_t motor, int8_t speed, int8_t direction);
 
    //uint16_t IRRead();  //This probably needs to be in main w/ interrupts
 
    uint16_t LineRight();
    uint16_t LineLeft(); 
    Adafruit_FXOS8700 accelFront;
    Adafruit_FXOS8700 accelBack;
 
    Motor motor_A = Motor(MOTOR_FORWARD_A, MOTOR_BACK_A);
    Motor motor_B = Motor(MOTOR_FORWARD_B, MOTOR_BACK_B);
    Motor motor_C = Motor(MOTOR_FORWARD_C, MOTOR_BACK_C);
    Motor motor_D = Motor(MOTOR_FORWARD_D, MOTOR_BACK_D);



 
    uint16_t AccelRead(uint8_t side);
    uint16_t PressureRead(uint8_t side);
 
  private:    
    void begin();
    void AccelerometerSetup();
};
 
extern InterfaceClass interface;
 
#endif