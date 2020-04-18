#include <SmartInventor.h>

int speed = 60;
int turnSpeed = 60;

void setup()
{
  SmartInventor.DCMotorUse();
}


void loop() {
  
  leftWheelsForward(100);
  rightWheelsForward(10);
  delay(5000);
  leftWheelsForward(0000000000);
  rightWheelsForward(0000000000);

  delay(50000);
}

void leftWheelsForward(int speed) {
    SmartInventor.DCMotor(M1,CCW,speed);
    SmartInventor.DCMotor(M3,CCW,speed);
}

void rightWheelsForward(int speed) {
    SmartInventor.DCMotor(M2,CW,speed);
    SmartInventor.DCMotor(M4,CW,speed);
}

void leftWheelsBack(int speed) {
    SmartInventor.DCMotor(M1,CW,speed);
    SmartInventor.DCMotor(M3,CW,speed);
}

void rightWheelsBack(int speed) {
    SmartInventor.DCMotor(M2,CCW,speed);
    SmartInventor.DCMotor(M4,CCW,speed);
}
