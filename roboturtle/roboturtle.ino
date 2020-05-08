#include <SmartInventor.h>

int MAX_FORWARD_SPEED = 127;
long stepDelay = 100;

const int NUM_SONAR = 7;
uint8_t FAR_RIGHT = 22;
uint8_t FRONT = 23;
uint8_t FAR_LEFT = 24;
uint8_t REAR_LEFT = 28;
uint8_t FRONT_RIGHT = 29;
uint8_t REAR_RIGHT = 30;
uint8_t FRONT_LEFT = 31;
uint8_t SONAR_RCV_ADDRESSES[NUM_SONAR] = {REAR_RIGHT, FAR_RIGHT, FRONT_RIGHT, FRONT, FRONT_LEFT, FAR_LEFT, REAR_LEFT};
uint8_t SONAR_BROADCAST = 27;

long distances[NUM_SONAR] = {0};

long OBSTACLE_DISTANCE_THRESH = 30;

long MAX_DURATION = 29000;
long MAX_CM = 450;

int index = 0;
void straight();
void stepRight();
void stepLeft();

void setup() {
  SmartInventor.DCMotorUse();
  Serial.begin(9600); 

  for(int i=0; i<NUM_SONAR; i++) {
    pinMode(SONAR_RCV_ADDRESSES[i], INPUT);
  }
  pinMode(SONAR_BROADCAST, OUTPUT);
}

void loop() {
  moveForward(0.0);
  delay(1000);
  // straight();
  // stepLeft();
  // stepRight();

  // I can type anything I want in a comment

  // this is where I leave helpful notes for myself and other developers
  
  straight();
  straight();
  straight();
  stepRight();
straight();
straight();
straight();
straight();
stepLeft();
straight();

straight();
straight();
straight();
straight();
straight();


stepRight();
straight();



}



void straight() {
  moveForward(0.5);
  delay(650);
  moveForward(0.0);
  delay(stepDelay);
}

void stepRight() {
  moveRight(1.0);
  delay(550);
  moveForward(0.0);
  delay(stepDelay);
}

void stepLeft() {
  moveLeft(1.0);
  delay(550);
  moveForward(0.0);
  delay(stepDelay);
}

void stopRobot() {
  moveForward(0.0);
  delay(100000);
}

int minDistanceIndex() {
  int minimum = 10000;
  int minIndex = 0;
  for(int i=0; i<NUM_SONAR;i++) {
    if(distances[i] == 0) {
      continue;
    }
    if (distances[i] < minimum) {
      minimum = distances[i];
      minIndex = i;
    }
  }
  return minIndex;
}

void pingSonar() {
   digitalWrite(SONAR_BROADCAST, LOW);
   delayMicroseconds(2);
   digitalWrite(SONAR_BROADCAST, HIGH);
   delayMicroseconds(10);
   digitalWrite(SONAR_BROADCAST, LOW);  
}

long durationAtAddress(uint8_t sonarAddress) {
  return pulseIn(sonarAddress, HIGH, MAX_DURATION);
}

long microsecondsToCentimeters(long microseconds) {
  if (microseconds == 0) {
    return MAX_CM;
  }
  return microseconds / 29 / 2;
}

void moveForward(float forwardIntensity) {
  int s = (int)(forwardIntensity * (float)MAX_FORWARD_SPEED);
  leftWheelsForward(s);
  rightWheelsForward(s);
}

void moveLeft(float intensity) {
  leftWheelsBack(127 * intensity);
  rightWheelsForward(127 * intensity);
}

void moveRight(float intensity) {
  leftWheelsForward(127 * intensity);
  rightWheelsBack(127 * intensity);
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
