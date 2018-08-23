//
// Created by atton on 7/27/2018.
//

#include "veh_globals.h"
#include "Arduino.h"
#include "AVCSStatus.h"

AVCSStatus::AVCSStatus() {
    vName = KEY_PORT;
    location = START_LOC;
    nextLocation = START_LOC;
    destination = START_LOC;
    nextVertType = L_NINETY;
    destinationAddress = 4;
    passengers = 0;
    currentObjective = PARK;
    positionConstant = K_POSITION;
    deltaConstant = K_DELTA;
    driveStatus = STOP;
    baseSpeed = START_SPEED;
    insideSpeed = START_INSIDE;
    outsideSpeed = START_OUTSIDE;
    intersectionDelay = INTERSECTION_DELAY;
}

void AVCSStatus::updateMotorConstants(char* incomingPacket){

  positionConstant = (incomingPacket[K_POS_ONES]-CHAR_ZERO);
  positionConstant += (incomingPacket[K_POS_TENTHS]-CHAR_ZERO) * .1;
  positionConstant += (incomingPacket[K_DEL_HUNTHS]-CHAR_ZERO) * .01;
  positionConstant += (incomingPacket[K_POS_THOUTHS]-CHAR_ZERO) * .001;

  deltaConstant = (incomingPacket[K_DEL_ONES]-CHAR_ZERO);
  deltaConstant += (incomingPacket[K_DEL_TENTHS]-CHAR_ZERO) * .1;
  deltaConstant += (incomingPacket[K_DEL_HUNTHS]-CHAR_ZERO) * .01;
  deltaConstant += (incomingPacket[K_DEL_THOUTHS]-CHAR_ZERO) * .001;

  baseSpeed = (incomingPacket[T_SPD_ONES]-CHAR_ZERO);
  baseSpeed += (incomingPacket[T_SPD_HUNDOS]-CHAR_ZERO) * 100;
  baseSpeed += (incomingPacket[T_SPD_TENS]-CHAR_ZERO) * 10;

  driveStatus = incomingPacket[TEST_DRIVE_STAT]-CHAR_ZERO;
  currentObjective = incomingPacket[TEST_OBJECTIVE] - CHAR_ZERO;

  intersectionDelay = incomingPacket[ISECT_DELAY_ONES] - CHAR_ZERO;
  intersectionDelay += (incomingPacket[ISECT_DELAY_TENS] - CHAR_ZERO) *10;
  intersectionDelay += (incomingPacket[ISECT_DELAY_HUNDOS] - CHAR_ZERO) *100;

  insideSpeed = incomingPacket[I_SPD_ONES] - CHAR_ZERO;
  insideSpeed += (incomingPacket[I_SPD_TENS] -CHAR_ZERO) * 10;
  insideSpeed += (incomingPacket[I_SPD_HUNDOS]) - CHAR_ZERO * 100;

  outsideSpeed = incomingPacket[O_SPD_ONES] - CHAR_ZERO;
  outsideSpeed += (incomingPacket[O_SPD_TENS] - CHAR_ZERO) * 10;
  outsideSpeed += (incomingPacket[O_SPD_HUNDOS] - CHAR_ZERO) * 100;
}

void AVCSStatus::changeDestination(char* incomingPacket){

    if(DEBUG_COMMS){
        Serial.print("Inc Change Dest: ");
        Serial.println(incomingPacket);
    }

    destination = (incomingPacket[DEST_ONES] - CHAR_ZERO);
    destination += (incomingPacket[DEST_TENS] -CHAR_ZERO) *10;
    destination += (incomingPacket[DEST_HUNDOS] -CHAR_ZERO) *100;

    destinationAddress = incomingPacket[ADDR]-CHAR_ZERO;
    currentObjective = incomingPacket[COBJ]-CHAR_ZERO;
    driveStatus = incomingPacket[DSTATUS]-CHAR_ZERO;
    nextVertType = incomingPacket[NXTVRTTYPE]-CHAR_ZERO;

    Serial.println(incomingPacket);

    if(DEBUG_COMMS){
      String temp = "Change Destination: ";
      temp = temp +
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

void AVCSStatus::changeNext(char* incomingPacket){

    if(DEBUG_COMMS){
        Serial.print("Inc Change Next: ");
        Serial.println(incomingPacket);
    }

    nextLocation = (incomingPacket[NEXTLOC_ONES] -CHAR_ZERO);
    nextLocation += (incomingPacket[NEXTLOC_TENS] -CHAR_ZERO) *10;
    nextLocation += (incomingPacket[NEXTLOC_HUNDOS] -CHAR_ZERO) *100;

    nextVertType = (incomingPacket[NXTVRTTYPE] -CHAR_ZERO);

    driveStatus = (incomingPacket[DSTATUS] -CHAR_ZERO);

    if(DEBUG_COMMS){
      String temp = "After Change Next: ";
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

void AVCSStatus::arriveAtDestination(char *incomingPacket) {

}

void AVCSStatus::resetAll(char *incomingPacket){

    if(DEBUG_COMMS){
        Serial.print("Reset All IncPacket: ");
        Serial.println(incomingPacket);
    }

    location = (incomingPacket[LOC_ONES] - CHAR_ZERO);
    location += (incomingPacket[LOC_HUNDOS] - CHAR_ZERO) * 100;
    location += (incomingPacket[LOC_TENS] - CHAR_ZERO) * 10;

    destination = (incomingPacket[DEST_ONES] -CHAR_ZERO);
    destination += (incomingPacket[DEST_TENS] -CHAR_ZERO) *10;
    destination += (incomingPacket[DEST_HUNDOS] -CHAR_ZERO) *100;

    nextLocation = (incomingPacket[NEXTLOC_ONES] -CHAR_ZERO);
    nextLocation += (incomingPacket[NEXTLOC_TENS] -CHAR_ZERO) *10;
    nextLocation += (incomingPacket[NEXTLOC_HUNDOS] -CHAR_ZERO) *100;

    destinationAddress = incomingPacket[ADDR]-CHAR_ZERO;

    passengers = (incomingPacket[PASS]-CHAR_ZERO);

    currentObjective = incomingPacket[COBJ]-CHAR_ZERO;

    baseSpeed = (incomingPacket[SPD_ONES] - CHAR_ZERO);
    baseSpeed += (incomingPacket[SPD_HUNDOS] - CHAR_ZERO) * 100;
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



