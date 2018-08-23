#include "AVCSMotor.h"
#include "globals.h"

//#include <iostream>

//#define speedControlRight 16
//#define motorRight1 4
//#define motorRight2 0
//#define motorLeft1 2
//#define motorLeft2 15
//#define speedControlLeft 8

AVCSMotor::AVCSMotor() {
    leftSpeed = 0;
    rightSpeed = 0;
    pinMode(speedControlLeft, OUTPUT);
    pinMode(speedControlRight, OUTPUT);
    pinMode(motorRight1, OUTPUT);
    pinMode(motorRight2, OUTPUT);
    pinMode(motorLeft1, OUTPUT);
    pinMode(motorLeft2, OUTPUT);
}

AVCSMotor::~AVCSMotor() {/*nothing to destruct*/}

void AVCSMotor::driveForward() {
    digitalWrite(motorRight2, LOW);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, HIGH);
}

void AVCSMotor::driveLeft() {
    digitalWrite(motorRight2, LOW);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, LOW);
}

void AVCSMotor::driveRight(){
    digitalWrite(motorRight2, LOW);
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
