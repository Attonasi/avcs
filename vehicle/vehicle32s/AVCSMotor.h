#ifndef VEHICLE_LIBRARY_H
#define VEHICLE_LIBRARY_H

#include <Arduino.h>

class AVCSMotor {
public:
    int leftSpeed;
    int rightSpeed;

    AVCSMotor();
    ~AVCSMotor();
    void driveForward();
    void driveRight();
    void driveLeft();
    void driveStop();
    void printStuff();
};

#endif
