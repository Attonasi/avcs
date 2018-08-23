//
// Created by atton on 7/26/2018.
//

#ifndef VEHICLE32S_AVCSSTATUS_H
#define VEHICLE32S_AVCSSTATUS_H

#include <Arduino.h>
#include "veh_globals.h"

class AVCSStatus {
public:
    int vName;
    int location;
    int nextLocation;
    int destination;
    int destinationAddress;
    int passengers;
    int currentObjective;
    int baseSpeed;
    int insideSpeed;
    int outsideSpeed;
    int driveStatus;
    int intersectionDelay;
    int nextVertType;
    float deltaConstant;
    float positionConstant;

    AVCSStatus();
    void updateMotorConstants(char* incomingPacket);
    void changeDestination(char* incomingPacket);
    void changeNext(char* incomingPacket);
    void arriveAtDestination(char* incomingPacket);
    void resetAll(char* incomingPacket);
};


#endif //VEHICLE32S_AVCSSTATUS_H
