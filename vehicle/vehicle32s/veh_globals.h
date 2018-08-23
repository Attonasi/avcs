//
// Created by atton on 7/22/2018.
//

#ifndef VEHICLE_GLOBALS_H
#define VEHICLE_GLOBALS_H

#define KEY_PORT 4211
#define NETWORK 14100
#define BAUD_RATE 115200
#define PILE_TIMER 500

#define DEBUG 0
#define DEBUG_DRIVE 0
#define DEBUG_COMMS 0

#define DRIVE_FORWARD 1
#define DRIVE_LEFT 2
#define DRIVE_RIGHT 3

#define CHECK_BOTH 3
#define CHECK_LEFT 1
#define CHECK_RIGHT 2

#define INTERSECTION_TYPES 6
#define DRIVE_TYPES 4

#define PLUS 0
#define TEE 1
#define R_TEE 2
#define L_TEE 3
#define L_NINETY 4
#define R_NINETY 5
#define INTERSECTION_DELAY 800

#define START_LOC 100

#define STOP 0

#define PARK 1
#define PICKUP 2
#define DROPOFF 3
#define CHARGE 4
#define EMERGENCY 5
#define MANUAL 9

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4

#define RIGHT_IR 0
#define LEFT_IR 7
#define REFERENCE 3500
#define MAX_SPEED 255
#define MIN_SPEED 0
#define IR_BLACK 500
#define MAX_CORRECT 55
#define CAL_SPEED 170
#define START_SPEED 160
#define START_INSIDE 150
#define START_OUTSIDE 220
#define SPEED_CHANNEL_LEFT 0
#define SPEED_CHANNEL_RIGHT 1
#define FREQ 5000
#define RESOLUTION 8
#define K_DELTA .135
#define K_POSITION .015
#define PARK_DISTANCE 100

#define SPEED_CONTROL_RIGHT 21 //5
#define motorRight1 23  //18
#define motorRight2 22  //19
#define motorLeft1 19 //22
#define motorLeft2 18  //23
#define SPEED_CONTROL_LEFT 5 //21
#define NUM_SENSORS 8

//QTRSensorsRC qtr((unsigned char[]) {32, 33 ,25, 26, 27, 14, 12, 4}, 8);

#define MESSAGE_TYPE 6
#define UPDATE_CONSTANTS 48
#define CHANGE_DESTINATION 49
#define CHANGE_NEXT_VERT 50
#define DRIVE_TO_ADDRESS 51
#define RESET_ALL 53
#define UPDATE_REQUEST 57
#define CHAR_ZERO 48
#define NAME_ONES 17
#define NAME_TENS 16
#define NAME_HUNDOS 15
#define NAME_THOUS 14
#define LOC_ONES 26
#define LOC_TENS 25
#define LOC_HUNDOS 24
#define DEST_ONES 36
#define DEST_TENS 35
#define DEST_HUNDOS 34
#define NEXTLOC_ONES 49
#define NEXTLOC_TENS 48
#define NEXTLOC_HUNDOS 47
#define ADDR 57
#define PASS 65
#define COBJ 73
#define SPD_ONES 82
#define SPD_TENS 81
#define SPD_HUNDOS 80
#define DSTATUS 93
#define NXTVRTTYPE 107

#define K_POS_ONES 12
#define K_POS_TENTHS 14
#define K_POS_HUNTHS 15
#define K_POS_THOUTHS 16
#define K_DEL_ONES 22
#define K_DEL_TENTHS 24
#define K_DEL_HUNTHS 25
#define K_DEL_THOUTHS 26
#define T_SPD_ONES 39
#define T_SPD_TENS 38
#define T_SPD_HUNDOS 37
#define I_SPD_ONES 53
#define I_SPD_TENS 52
#define I_SPD_HUNDOS 51
#define O_SPD_ONES 68
#define O_SPD_TENS 67
#define O_SPD_HUNDOS 66
#define ISECT_DELAY_ONES 87
#define ISECT_DELAY_TENS 86
#define ISECT_DELAY_HUNDOS 85
#define TEST_DRIVE_STAT 99
#define TEST_OBJECTIVE 107

#define UPDATE_STATUS 57
#define INTERSECTION 50
#define CHANGE_DESTINATION 48
#define VEHICLE_RESET 53

#endif //VEHICLE_GLOBALS_H
