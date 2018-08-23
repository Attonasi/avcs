//
// Created by atton on 8/3/2018.
//

#include "NWKCity.h"
#include "network_globals.h"
#include "Arduino.h"
//#include <iostream>

NWKCity::NWKCity() {
Serial.println("City?");

}

void NWKCity::setEdgeVal(int index, int eName, int destType, int weight, int leftTurn, int rightTurn,
                         int straight){
    edgeArray[index].eName = eName;
    edgeArray[index].destType = destType;
    edgeArray[index].weight = weight;
    edgeArray[index].index = index;
    edgeArray[index].leftTurn = leftTurn;
    edgeArray[index].rightTurn = rightTurn;
    edgeArray[index].straight = straight;
}

void NWKCity::initShortestPath() {
    for(int i = 0; i < NUM_EDGES; i++) {
        visited[i] = false;
        cost[i] = BIG_NUMBER;
        parent[i] = BIG_NUMBER;
    }
}

void NWKCity::relax(int curr_index, int next_index){
    if(cost[curr_index] + edgeArray[next_index].weight < cost[next_index]){
        cost[next_index] = cost[curr_index] + edgeArray[next_index].weight;
        parent[next_index] = curr_index;
    }
}

void NWKCity::setShortestPath(int src, int dest){

    initShortestPath();
    cost[src] = edgeArray[src].weight;
    int lowest;
    int indx;
    
    //Go through all vertices until dest is found because this is a directedish graph
    for (int i = 0; i < NUM_EDGES; i++) {
        if (cost[dest] < BIG_NUMBER) { break; }
        lowest = BIG_NUMBER;
        // Find lowest index in cost
        for (int j = 0; j < NUM_EDGES; j++) {
            if (lowest > cost[j] && !visited[j]) {
                lowest = cost[j];
                indx = j;
            }
        }
        visited[indx] = true;
        // Update cost Array with edge values
        if (edgeArray[indx].leftTurn != NO_TURN) {
            relax(indx, edgeArray[indx].leftTurn);
        }
        if (edgeArray[indx].rightTurn != NO_TURN) {
            relax(indx, edgeArray[indx].rightTurn);
        }
        if (edgeArray[indx].straight != NO_TURN) {
            relax(indx, edgeArray[indx].straight);
        }
    }
}

void NWKCity::printCostParent() {
    for(int i = 0; i < NUM_EDGES; i++){
        Serial.printf("Cost[%d]: %d parent[%d]: %d Visted[%d]: %d\n", i, cost[i], i, parent[i], i, visited[i]);
    }
}

