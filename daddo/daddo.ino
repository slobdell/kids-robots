#include <SmartInventor.h>

int MAX_FORWARD_SPEED = 127;


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

int index = 0;

void setup() {
  SmartInventor.DCMotorUse();
  Serial.begin(9600); 

  for(int i=0; i<NUM_SONAR; i++) {
    pinMode(SONAR_RCV_ADDRESSES[i], INPUT);
  }
  pinMode(SONAR_BROADCAST, OUTPUT);
}

void loop() {
   index = (index + 1) % NUM_SONAR;
   pingSonar();

   distances[index] = distanceAtAddress(SONAR_RCV_ADDRESSES[index]);

   int minIndex = minDistanceIndex();
   // rear right
   if(index % NUM_SONAR == 0) {
    if (minIndex == 0) {
    //Serial.println("rear right");
     moveForward(0.5);
   } else if (minIndex == 1) {
    //Serial.println("far right");
     moveLeft();
   } else if (minIndex == 2) {
    //Serial.println("front right");
     moveLeft();
   } else if (minIndex == 3) {
    //Serial.println("forward");
     moveForward(0.5);
   } else if (minIndex == 4) {
    //Serial.println("front left");
     moveRight();
   } else if (minIndex == 5) {
    //Serial.println("far left");
     moveRight();
   } else if (minIndex == 6) {
    //Serial.println("rear left");
     moveForward(0.5);
   
   }
   //Serial.print(distances[minIndex]);
   //Serial.println(" cm");
   }
   

   //if(index % NUM_SONAR == 0) {
   delay(50); 
   //}
   
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

long distanceAtAddress(uint8_t sonarAddress) {
  return microsecondsToCentimeters(
    pulseIn(sonarAddress, HIGH)
  );
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void moveForward(float forwardIntensity) {
  int s = (int)(forwardIntensity * (float)MAX_FORWARD_SPEED);
  leftWheelsForward(s);
  rightWheelsForward(s);
}

void moveLeft() {
  leftWheelsBack(50);
  rightWheelsForward(25);
}

void moveRight() {
  leftWheelsForward(25);
  rightWheelsBack(50);
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
