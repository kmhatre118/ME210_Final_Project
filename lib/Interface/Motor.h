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
    void drive(double speed);  
	
    void brake(); 
	
	
  private:
    //variables for the 2 inputs, PWM input, Offset value, and the Standby pin
	//int In1, In2, PWM, Offset,Standby;
    int In1, In2;	
	//private functions that spin the motor CC and CCW
	void fwd(int speed);
	void rev(int speed);


};



#endif