#include "AVCSIRNav.h"
#include "AVCSMotor.h"
#include "globals.h"
#include "Arduino.h"
//#include <iostream>


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

//    int fr1 = analogRead(frontRightIR);
//    int f2 = analogRead(frontLeftIR);
//    Serial.print("front right: ");
//    Serial.print(fr1);
//    Serial.print(" front left: ");
//    Serial.println(f2);
//    int b2 = analogRead(backRightIR);
//    int b1 = analogRead(backLeftIR);
//    Serial.print("back right: ");
//    Serial.print(b2);
//    Serial.print(" back left: ");
//    Serial.println(b1);
    if( analogRead(frontRightIR) > 100){
        front2 = true;
    } else {
        front2 = false;
    }
    if(analogRead(frontLeftIR) > 100){
        front1 = true;
    } else {
        front1 = false;
    }
    if(analogRead(backRightIR) > 100){
        back2 = true;
    } else {
        back2 = false;
    }
    if(analogRead(backLeftIR) > 100){
        back1 = true;
    } else {
        back1 = false;
    }
}

void IRNav::adjustSpeed(AVCSMotor myMotor){
    if(front1){
        leftModifier+=20;
    } else {
        myMotor.leftSpeed -= leftModifier;
        leftModifier = 0;
    }
    if(front2){
        rightModifier+=20;
    } else {
        myMotor.rightSpeed -= rightModifier;
        rightModifier = 0;
    }
    myMotor.leftSpeed += leftModifier;
    myMotor.rightSpeed += rightModifier;
}

void IRNav::printValues() {
    Serial.print("Front Right: ");
    Serial.print(front2);
    Serial.print(" Front Left: ");
    Serial.print(front1);
    Serial.print(" Back Right: ");
    Serial.print(back2);
    Serial.print(" Back Left: ");
    Serial.print(back1);
}
