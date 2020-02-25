#include "Motor.h"
#include <Arduino.h>
Motor::Motor(int In1pin, int In2pin) 
{
  In1 = In1pin;
  In2 = In2pin;
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
}

void Motor::drive(int speed)
{
  int newSpeed = map(speed, -1, 1, 0, 255);
  if (speed>=0) fwd(newSpeed);
  else rev(newSpeed);
}


void Motor::fwd(int speed)
{

  analogWrite(In1, speed);
  analogWrite(In2, 0);
 
}

void Motor::rev(int speed)
{
  analogWrite(In1, 0);
  analogWrite(In2, speed);
}

void Motor::brake()
{
   analogWrite(In1, 0);
   analogWrite(In2, 0);
}


void forward(Motor motor1, Motor motor2, int speed)
{
	motor1.drive(speed);
	motor2.drive(speed);
}
void forward(Motor motor1, Motor motor2)
{
	motor1.drive(DEFAULTSPEED);
	motor2.drive(DEFAULTSPEED);
}


void back(Motor motor1, Motor motor2, int speed)
{
	int temp = abs(speed);
	motor1.drive(-temp);
	motor2.drive(-temp);
}
void back(Motor motor1, Motor motor2)
{
	motor1.drive(-DEFAULTSPEED);
	motor2.drive(-DEFAULTSPEED);
}
void left(Motor left, Motor right, int speed)
{
	int temp = abs(speed)/2;
	left.drive(-temp);
	right.drive(temp);
	
}


void right(Motor left, Motor right, int speed)
{
	int temp = abs(speed)/2;
	left.drive(temp);
	right.drive(-temp);
	
}
void brake(Motor motor1, Motor motor2)
{
	motor1.brake();
	motor2.brake();
}