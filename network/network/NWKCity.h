//
// Created by atton on 8/2/2018.
//

#ifndef FINAL_PROJECT_CITY_H
#define FINAL_PROJECT_CITY_H

#include "Arduino.h"
#include "NWKVehicle.h"
#include "network_globals.h"
//#include <iostream>

typedef struct edge{
    int eName;
    int destType;
    int weight;
    int index;
    int leftTurn;
    int rightTurn;
    int straight;
} Edge;

class NWKCity {
public:
    Edge edgeArray[NUM_EDGES];
    int adjArray[NUM_EDGES][NUM_EDGES];
    bool visited[NUM_EDGES];
    int cost[NUM_EDGES];
    int parent[NUM_EDGES];

    NWKCity();
    void setShortestPath(int src, int dest);
    void setEdgeVal(int index, int eName, int destType, int weight, int leftTurn, int rightTurn, int straight);
    void initShortestPath();
    void relax(int src, int dest);
    void printCostParent();
};
#endif //FINAL_PROJECT_CITY_H
