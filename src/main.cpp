#include <Arduino.h>
#include "Motor.h"
#include <Interface.h>

Motor m = Motor(10, 9);

void setup() {
  
 // pinMode(10, OUTPUT);
 // pinMode(9, OUTPUT);

  // put your setup code here, to run once:
}

void loop() {
  //m.drive(1);
     interface.motor_A.drive(1);

}