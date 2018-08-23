#include "AVCSIRNav.h"
#include "AVCSMotor.h"
#include "globals.h"
#include "Arduino.h"
//#include <iostream>

//#define frontRightIR 19
//#define frontLeftIR 18
//#define backRightIR 5
//#define backLeftIR 21

IRNav::IRNav() {
    pinMode(frontRightIR, INPUT);
    pinMode(frontLeftIR, INPUT);
    pinMode(backRightIR, INPUT);
    pinMode(backLeftIR, INPUT);

    backLeftTrigger = false;
    backLeftTrigger = false;
    back1 = false;
    back2 = false;
    front2 = false;
    front1 = false;
    leftModifier = 0;
    rightModifier = 0;
}

IRNav::~IRNav() {/*nothing */}

void IRNav::readAll() {

    if( digitalRead(frontRightIR)){
        front2 = true;
    } else {
        front2 = false;
    }
    if(digitalRead(frontLeftIR)){
        front1 = true;
    } else {
        front1 = false;
    }
    if(digitalRead(backRightIR)){
        back2 = true;
    } else {
        back2 = false;
    }
    if(digitalRead(backLeftIR)){
        back1 = true;
    } else {
        back1 = false;
    }
}

void IRNav::adjustSpeed(AVCSMotor myMotor){
    if(front2){
        leftModifier+=20;
    } else {
        myMotor.leftSpeed -= leftModifier;
        leftModifier = 0;
    }
    if(front1){
        rightModifier+=20;
    } else {
        myMotor.rightSpeed -= rightModifier;
        rightModifier = 0;
    }
    myMotor.leftSpeed += leftModifier;
    myMotor.rightSpeed += rightModifier;
}

void IRNav::printValues() {
    Serial.print("Left Modifier : ");
    Serial.print(leftModifier);
    Serial.print(" Right Modifier: ");
    Serial.println(rightModifier);
    Serial.print("Front Right: ");
    Serial.print(front1);
    Serial.print(" Front Left: ");
    Serial.print(front2);
    Serial.print(" Back Right: ");
    Serial.print(back1);
    Serial.print(" Back Left: ");
    Serial.println(back2);
}
