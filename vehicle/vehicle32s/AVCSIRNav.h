#ifndef AVCSIRNAV_LIBRARY_H
#define AVCSIRNAV_LIBRARY_H

#include "AVCSStatus.h"
#include "AVCSMotor.h"
#include <Arduino.h>
#include <QTRSensors.h>

class IRNav {
public:
    int leftModifier;
    int rightModifier;
    IRNav();

    int driveForward(int posit, int oldPosit, unsigned int leftIR, unsigned int rightIR,
            int baseSpeed, float positionConstant, float deltaConstant, AVCSStatus vStat);
    int driveLeft(int posit, int oldPosit, unsigned int leftIR, unsigned int rightIR,
            int baseSpeed, float positionConstant, float deltaConstant, AVCSStatus vStat);
    int driveRight(int posit, int oldPosit, unsigned int leftIR, unsigned int rightIR,
            int baseSpeed, float positionConstant, float deltaConstant, AVCSStatus vStat);
    int driveToAddress(int posit, int oldPosit, unsigned int leftIR, unsigned int rightIR,
                       int baseSpeed, float positionConstant, float deltaConstant,
                       int addressCounter, AVCSStatus vStat);
    void intersectionStraight(AVCSStatus vStat);
    void intersectionLeft(AVCSStatus vStat);
    void intersectionRight(AVCSStatus vStat);
    void checkMinMax(int leftMod, int rightMod);
    int followLine(int posit, int oldPosit, unsigned int leftIR, unsigned int rightIR,
                   int baseSpeed, float positionConstant, float deltaConstant, AVCSStatus vStat);
};

#endif
