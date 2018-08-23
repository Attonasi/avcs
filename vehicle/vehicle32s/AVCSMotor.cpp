#include "AVCSMotor.h"
#include "veh_globals.h"

//#include <iostream>

//#define speedControlRight 9
//#define motorRight1 10
//#define motorRight2 12
//#define motorLeft1 26
//#define motorLeft2 27
//#define speedControlLeft 14

AVCSMotor::AVCSMotor() {
    leftSpeed = START_SPEED;
    rightSpeed = START_SPEED;
    pinMode(SPEED_CONTROL_LEFT, OUTPUT);
    pinMode(SPEED_CONTROL_RIGHT, OUTPUT);
    pinMode(motorRight1, OUTPUT);
    pinMode(motorRight2, OUTPUT);
    pinMode(motorLeft1, OUTPUT);
    pinMode(motorLeft2, OUTPUT);
}

AVCSMotor::~AVCSMotor() {/*nothing to destruct*/}

void AVCSMotor::driveForward() {
    digitalWrite(motorRight2, LOW);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
}

void AVCSMotor::driveLeft() {
    digitalWrite(motorRight2, LOW);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
}

void AVCSMotor::driveRight(){
    digitalWrite(motorRight2, HIGH);
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, HIGH);
}

void AVCSMotor::driveStop(){
    digitalWrite(motorRight2, LOW);
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, LOW);
}

void AVCSMotor::printStuff(){
  Serial.print("Left Motor speed: ");
  Serial.print(leftSpeed);
  Serial.print(" Right Motor speed: ");
  Serial.println(rightSpeed);
}

