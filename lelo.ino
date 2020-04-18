#include <SmartInventor.h>

int speed = 60;
int turnSpeed = 60;

void setup()
{
  SmartInventor.DCMotorUse();
}


void loop()
{
  leftWheelsForward(127);
  rightWheelsForward(127);
  delay(5000);
  leftWheelsBack(50);
  rightWheelsForward(50);
  delay(1000);


  stopRobot();
}

void stopRobot() {
  leftWheelsBack(0);
  rightWheelsForward(0);
  delay(1000000);
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
