#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

//used in some functions so you don't have to send a speed
#define DEFAULTSPEED 1



class Motor
{
  public:
    // Constructor. Mainly sets up pins.
   // Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin);   
    Motor(int In1pin, int In2pin);   

    // Drive in direction given by sign, at speed given by magnitude of the 
	//parameter.
    void drive(int speed);  
	
    void brake(); 
	
	
  private:
    //variables for the 2 inputs, PWM input, Offset value, and the Standby pin
	//int In1, In2, PWM, Offset,Standby;
    int In1, In2;	
	//private functions that spin the motor CC and CCW
	void fwd(int speed);
	void rev(int speed);


};

//Takes 2 motors and goes forward, if it does not go forward adjust offset 
//values until it does.  These will also take a negative number and go backwards
//There is also an optional speed input, if speed is not used, the function will
//use the DEFAULTSPEED constant.
void forward(Motor motor1, Motor motor2, int speed);
void forward(Motor motor1, Motor motor2);

//Similar to forward, will take 2 motors and go backwards.  This will take either
//a positive or negative number and will go backwards either way.  Once again the
//speed input is optional and will use DEFAULTSPEED if it is not defined.
void back(Motor motor1, Motor motor2, int speed);
void back(Motor motor1, Motor motor2);

//Left and right take 2 motors, and it is important the order they are sent.
//The left motor should be on the left side of the bot.  These functions
//also take a speed value
void left(Motor left, Motor right, int speed);
void right(Motor left, Motor right, int speed);

//This function takes 2 motors and and brakes them
void brake(Motor motor1, Motor motor2);


#endif