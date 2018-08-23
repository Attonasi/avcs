#ifndef AVCSIRNAV_LIBRARY_H
#define AVCSIRNAV_LIBRARY_H

#include "AVCSMotor.h"
#include <Arduino.h>

class IRNav {
public:
    bool backRightTrigger;
    bool backLeftTrigger;
    int leftModifier;
    int rightModifier;
    bool back1;
    bool back2;
    bool front1;
    bool front2;
    IRNav();
    ~IRNav();
    void readAll();
    void adjustSpeed(AVCSMotor myMotor);
    void printValues();
};

#endif