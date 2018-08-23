#include "AVCSIRNav.h"
#include <AsyncUDP.h>

#include "veh_globals.h"
#include "Arduino.h"
//#include <iostream>

IRNav::IRNav() {
    leftModifier = 0;
    rightModifier = 0;
}

int IRNav::driveForward(int posit, int oldPosit, unsigned int leftIR,
        unsigned int rightIR, int baseSpeed, float positionConstant,
        float deltaConstant, AVCSStatus vStat) {

    bool isIntersection = false;

    if(vStat.nextVertType == PLUS){
        if(leftIR > IR_BLACK && rightIR > IR_BLACK){
            if(DEBUG_DRIVE){
                Serial.printf("Drive Forward Intersection!");
            }
            isIntersection = true;
        }
    } else if(vStat.nextVertType == L_TEE) {
        if(leftIR > IR_BLACK) {
            if(DEBUG_DRIVE){
                Serial.printf("Drive Forward Intersection!");
            }
            isIntersection = true;
        }
    } else if (vStat.nextVertType == R_TEE) {
        if(leftIR > IR_BLACK) {
            if (DEBUG_DRIVE) {
                Serial.printf("Drive Forward Intersection!");
            }
            isIntersection = true;
        }
    } else {
        rightModifier = STOP;
        leftModifier = STOP;
        vStat.driveStatus = EMERGENCY;
        return STOP;
    }

    if (isIntersection) {
        intersectionStraight(vStat);
        vStat.location = vStat.nextLocation;
    }

    return followLine(posit, oldPosit, leftIR, rightIR, baseSpeed, positionConstant,
                      deltaConstant, vStat);
}

void IRNav::intersectionStraight(AVCSStatus vStat) {
    ledcWrite(SPEED_CHANNEL_LEFT, CAL_SPEED);
    ledcWrite(SPEED_CHANNEL_RIGHT, CAL_SPEED);

    delay(INTERSECTION_DELAY);
}

int IRNav::driveRight(int posit, int oldPosit, unsigned int leftIR,
        unsigned int rightIR, int baseSpeed, float positionConstant,
        float deltaConstant, AVCSStatus vStat){

    bool isIntersection = false;

    if(vStat.nextVertType == PLUS || vStat.nextVertType == TEE){
        if(leftIR > IR_BLACK && rightIR > IR_BLACK){
            if(DEBUG_DRIVE){
                Serial.printf("Drive Forward Intersection!");
            }
            isIntersection = true;
        }
    } else if (vStat.nextVertType == R_TEE || vStat.nextVertType == R_NINETY) {
        if(rightIR > IR_BLACK) {
            if (DEBUG_DRIVE) {
                Serial.printf("Drive Forward Intersection!");
            }
            isIntersection = true;
        }
    } else {
        rightModifier = STOP;
        leftModifier = STOP;
        vStat.driveStatus = EMERGENCY;
        return STOP;
    }

    if (isIntersection) {
        intersectionRight(vStat);
        vStat.location = vStat.nextLocation;
    }

    return followLine(posit, oldPosit, leftIR, rightIR, baseSpeed, positionConstant,
                             deltaConstant, vStat);
}

void IRNav::intersectionRight(AVCSStatus vStat) {
    ledcWrite(SPEED_CHANNEL_LEFT, vStat.insideSpeed);
    ledcWrite(SPEED_CHANNEL_RIGHT, vStat.outsideSpeed);

    delay(INTERSECTION_DELAY);
}

int IRNav::driveLeft(int posit, int oldPosit, unsigned int leftIR,
        unsigned int rightIR, int baseSpeed, float positionConstant,
        float deltaConstant, AVCSStatus vStat) {

    bool isIntersection = false;

    if (vStat.nextVertType == PLUS || vStat.nextVertType == TEE) {
        if (leftIR > IR_BLACK && rightIR > IR_BLACK) {
            if (DEBUG_DRIVE) {
                Serial.printf("Drive Forward Intersection!");
            }
            isIntersection = true;
        }
    } else if (vStat.nextVertType == L_TEE || vStat.nextVertType == L_NINETY) {
        if (leftIR > IR_BLACK) {
            if (DEBUG_DRIVE) {
                Serial.printf("Drive Forward Intersection!");
            }
            isIntersection = true;
        }
    } else {
        rightModifier = STOP;
        leftModifier = STOP;
        vStat.driveStatus = EMERGENCY;
        return STOP;
    }

    if (isIntersection) {
        intersectionLeft(vStat);
        vStat.location = vStat.nextLocation;
    }

    return followLine(posit, oldPosit, leftIR, rightIR, baseSpeed, positionConstant,
            deltaConstant, vStat);
}

void IRNav::intersectionLeft(AVCSStatus vStat){
    ledcWrite(SPEED_CHANNEL_LEFT, vStat.outsideSpeed);
    ledcWrite(SPEED_CHANNEL_RIGHT, vStat.insideSpeed);

    delay(INTERSECTION_DELAY);
}

int IRNav::followLine(int posit, int oldPosit, unsigned int leftIR, unsigned int rightIR, int baseSpeed,
                      float positionConstant, float deltaConstant, AVCSStatus vStat) {

    int correction = (posit - REFERENCE) * positionConstant +
                     (posit - oldPosit) * deltaConstant; // + integralConstant * integralCorrection;
    if (correction > MAX_CORRECT) { correction = MAX_CORRECT; }

    rightModifier = baseSpeed + correction;
    leftModifier = baseSpeed - correction;

    checkMinMax(leftModifier, rightModifier);

    return correction;
}

void IRNav::checkMinMax(int leftMod, int rightMod){
    if (rightModifier > MAX_SPEED) { rightModifier = MAX_SPEED; }
    if (leftModifier > MAX_SPEED) { leftModifier = MAX_SPEED; }
    if (rightModifier < MIN_SPEED) { rightModifier = MIN_SPEED; }
    if (leftModifier < MIN_SPEED) { leftModifier = MIN_SPEED; }
}

int IRNav::driveToAddress(int posit, int oldPosit, unsigned int leftIR, unsigned int rightIR,
        int baseSpeed, float positionConstant, float deltaConstant, int addressCounter,
        AVCSStatus vStat) {

    if(addressCounter * PARK_DISTANCE > vStat.destinationAddress){
        vStat.driveStatus = PARK;
        vStat.currentObjective = PARK;
        return STOP;
    }

    return followLine(posit, oldPosit, leftIR, rightIR, baseSpeed, 
            positionConstant, deltaConstant, vStat);
}
