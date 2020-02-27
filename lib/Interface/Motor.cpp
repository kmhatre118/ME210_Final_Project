#include "Motor.h"
#include <Arduino.h>
Motor::Motor(int In1pin, int In2pin) 
{
  In1 = In1pin;
  In2 = In2pin;
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
}

void Motor::drive(double speed)
{
  int newSpeed = map(abs(speed), 0, 1, 0, 255);
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
