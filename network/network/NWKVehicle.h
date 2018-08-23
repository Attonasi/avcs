//
// Created by atton on 8/2/2018.
//

#ifndef FINAL_PROJECT_NETWORKVEHICLE_H
#define FINAL_PROJECT_NETWORKVEHICLE_H

#include "NWKCity.h"
#include "network_globals.h"

class NWKVehicle {
public:
    int vName; // port#
    int location;
    int nextLocation;
    int destination;
    int destinationAddress;
    int passengers;
    int currentObjective;
    int baseSpeed;
    int driveStatus;
    int nextVertType;
    int currentPath[NUM_EDGES];
    int pathIterator;

    NWKVehicle();
    void updateVehicleStatus(char* incomingPacket);
    void changeVehicleDestination(char* incomingPacket);
    void writeVehiclePath(int src, int dest, int parent[]);
    void changeNextVertex(struct edge location, struct edge next);
    void arriveAtDestination();
    void printPath();
    void writeAll(char* incomingPacket);
};
#endif //FINAL_PROJECT_NETWORKVEHICLE_H
