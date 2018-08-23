//
// Created by atton on 8/2/2018.
//
#include "NWKCity.h"
#include "NWKVehicle.h"
#include "network_globals.h"
#include "Arduino.h"
//#include <iostream>

NWKVehicle::NWKVehicle(){
  if(DEBUG_VEHICLE){
    Serial.println("Initialized Vehicle");
  }
}

void NWKVehicle::updateVehicleStatus(char* incomingPacket){

    if(DEBUG_COMMS){
        Serial.print("Inc Vehicle Status: ");
        Serial.println(incomingPacket);
    }

    location = (incomingPacket[LOC_ONES] - CHAR_ZERO);
    location += (incomingPacket[LOC_HUNDS] - CHAR_ZERO) * 100;
    location += (incomingPacket[LOC_TENS] - CHAR_ZERO) * 10;

    passengers = (incomingPacket[PASS]-CHAR_ZERO);

    baseSpeed = (incomingPacket[SPD_ONES] - CHAR_ZERO);
    baseSpeed += (incomingPacket[SPD_HUNDS] - CHAR_ZERO) * 100;
    baseSpeed += (incomingPacket[SPD_TENS] - CHAR_ZERO) * 10;

    driveStatus = (incomingPacket[SPD_ONES] - CHAR_ZERO);

    if(DEBUG_COMMS){
      String temp = "After Update Status: ";
      temp = temp + 1 +
              " Name: " + vName +
              " Loc: " + location +
              " Dest: " + destination +
              " NextLoc: " + nextLocation +
              " Addr: " + destinationAddress +
              " Pass: " + passengers +
              " CObj: " + currentObjective +
              " Spd: " + baseSpeed +
              " DStatus: " + driveStatus +
              " NxtVrtType: " + nextVertType;
      Serial.println(temp);
    }
}

void NWKVehicle::changeVehicleDestination(char* incomingPacket){

    if(DEBUG_COMMS){
        Serial.print("Inc Change Dest: ");
        Serial.println(incomingPacket);
    }

    destination = (incomingPacket[DEST_ONES] - CHAR_ZERO);
    destination += (incomingPacket[DEST_TENS] - CHAR_ZERO) *10;
    destination += (incomingPacket[DEST_HUNDS] - CHAR_ZERO) *100;

    destinationAddress = incomingPacket[ADDR] - CHAR_ZERO;
    
    currentObjective = incomingPacket[COBJ] - CHAR_ZERO;

    driveStatus = incomingPacket[DSTATUS] - CHAR_ZERO;

    if(DEBUG_COMMS){
      String temp = "After Change Dest: ";
      temp = temp + 0 +
              " Name: " + vName +
              " Loc: " + location +
              " Dest: " + destination +
              " NextLoc: " + nextLocation +
              " Addr: " + destinationAddress +
              " Pass: " + passengers +
              " CObj: " + currentObjective +
              " Spd: " + baseSpeed +
              " DStatus: " + driveStatus +
              " NxtVrtType: " + nextVertType;
      Serial.println(temp);
    }
}

void NWKVehicle::changeNextVertex(Edge location, Edge next){

    nextLocation = next.eName;
    nextVertType = location.destType;
//    Serial.printf("location: %d LeftT: %d rightT: %d straight: %d currPath[%d]: %d\n",location.eName, location.leftTurn, location.rightTurn, location.straight, pathIterator, currentPath[pathIterator]);
//    Serial.printf("next: %d LeftT: %d rightT: %d straight: %d currPath[%d]: %d\n",next.eName, next.leftTurn, next.rightTurn, next.straight, pathIterator, currentPath[pathIterator]);

    if(location.leftTurn == next.index){
      Serial.printf("inside left turn\n");
        driveStatus = DRIVE_LEFT;
    } else if(location.rightTurn == next.index){
        Serial.printf("inside right turn\n");
        driveStatus = DRIVE_RIGHT;
    } else if (location.straight == next.index){
        Serial.printf("inside straight \n");
        driveStatus = STRAIGHT;
    } else {
        Serial.printf("fuckall \n");
        driveStatus = EMERGENCY;
    }

}

void NWKVehicle::writeVehiclePath(int src, int dest, int parent[]) {
    pathIterator = 1;
    int pointer = dest;
    for(int j = 0; j < NUM_EDGES; j++){
      currentPath[j] = BIG_NUMBER;
    }
    currentPath[0] = dest;
    while (currentPath[pathIterator-1] != src){
        currentPath[pathIterator] = parent[pointer];
        pointer = parent[pointer];
        pathIterator++;
    }
    pathIterator--;
}

void NWKVehicle::printPath() {
    for(int i = pathIterator; i >= 0; i--){
        Serial.printf("Path[%d]: %d ", i, currentPath[i]);
    }
    Serial.printf("Path Iterator: %d \n", pathIterator);
}

void NWKVehicle::arriveAtDestination() {
    driveStatus = DRIVE_PARK;
}

void NWKVehicle::writeAll(char *incomingPacket) {

    if(DEBUG_COMMS){
        Serial.print("Inc Reset All: ");
        Serial.println(incomingPacket);
    }

    location = (incomingPacket[LOC_ONES] - CHAR_ZERO);
    location = (incomingPacket[LOC_HUNDS] - CHAR_ZERO) * 100;
    location += (incomingPacket[LOC_TENS] - CHAR_ZERO) * 10;

    destination = (incomingPacket[DEST_ONES] -CHAR_ZERO);
    destination += (incomingPacket[DEST_TENS] -CHAR_ZERO) *10;
    destination += (incomingPacket[DEST_HUNDS] -CHAR_ZERO) *100;

    nextLocation = (incomingPacket[NEXTLOC_ONES] -CHAR_ZERO);
    nextLocation += (incomingPacket[NEXTLOC_TENS] -CHAR_ZERO) *10;
    nextLocation += (incomingPacket[NEXTLOC_HUNDS] -CHAR_ZERO) *100;

    destinationAddress = incomingPacket[ADDR]-CHAR_ZERO;

    passengers = (incomingPacket[PASS]-CHAR_ZERO);

    currentObjective = incomingPacket[COBJ]-CHAR_ZERO;

    baseSpeed = (incomingPacket[SPD_ONES] - CHAR_ZERO);
    baseSpeed += (incomingPacket[SPD_HUNDS] - CHAR_ZERO) * 100;
    baseSpeed += (incomingPacket[SPD_TENS] - CHAR_ZERO) * 10;

    driveStatus = incomingPacket[DSTATUS]-CHAR_ZERO;

    nextVertType = incomingPacket[NXTVRTTYPE]-CHAR_ZERO;

    String temp = "Reset All Values: ";
    temp = temp + 5 +
            " Name: " + vName +
            " Loc: " + location +
            " Dest: " + destination +
            " NextLoc: " + nextLocation +
            " Addr: " + destinationAddress +
            " Pass: " + passengers +
            " CObj: " + currentObjective +
            " Spd: " + baseSpeed +
            " DStatus: " + driveStatus +
            " NxtVrtType: " + nextVertType;
    Serial.println(temp);
}
