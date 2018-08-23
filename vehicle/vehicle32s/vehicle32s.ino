#include <QTRSensors.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Arduino.h>
#include "AVCSStatus.h"
#include "AVCSIRNav.h"
#include "AVCSMotor.h"
#include "veh_globals.h"

AVCSStatus vStat;
AVCSMotor myMotor;
IRNav nav;
AsyncUDP Udp;
QTRSensorsRC qtr((unsigned char[]) {32, 33 , 25, 26, 27, 14, 12, 4}, 8);

int oldPosit = 0;
int posit;
int pile = 0;
int addressCounter = 0;

const int localUdpPort = KEY_PORT;
char* incomingPacket;  // buffer for incoming packets
int packetLength;
int outLength;

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("begin");

    ledcSetup(SPEED_CHANNEL_LEFT, FREQ, RESOLUTION);
    ledcAttachPin(SPEED_CONTROL_LEFT, SPEED_CHANNEL_LEFT);
    ledcSetup(SPEED_CHANNEL_RIGHT, FREQ, RESOLUTION);
    ledcAttachPin(SPEED_CONTROL_RIGHT, SPEED_CHANNEL_RIGHT);

//  const char* super = "mochalatteoreo";
//  const char* secr = "2andahalfcats";

    const char *super = "NETGEAR80";
    const char *secr = "perfectjungle494";

    Serial.printf("Connecting to %s ", super);
    WiFi.begin(super, secr);
    while (WiFi.status() != WL_CONNECTED) {
        delay(PILE_TIMER);
        Serial.print(".");
    }
    Serial.print(" connected on IP: ");
    Serial.print(WiFi.localIP());

    if (Udp.listen(localUdpPort)) {
        Serial.print("UDP listening on ip: ");
        Serial.println(WiFi.localIP());

        Udp.onPacket([](AsyncUDPPacket packet) {

            incomingPacket = (char *) packet.data();
            packetLength = packet.length();
            incomingPacket[packetLength] = 0;
            Serial.println(incomingPacket);
            String tempUpdateString = "Type: ";
            bool sendResponse = false;

            if (incomingPacket[MESSAGE_TYPE] == 48) {
                Serial.println("Updating Motor Constants.");
                vStat.updateMotorConstants(incomingPacket);
            }
            if (incomingPacket[MESSAGE_TYPE] == 49) {
                Serial.println("Changing Destination.");
                vStat.changeDestination(incomingPacket);
            }
            if (incomingPacket[MESSAGE_TYPE] == 50) {
                Serial.println("Changing Next.");
                vStat.changeNext(incomingPacket);
            }
            if (incomingPacket[MESSAGE_TYPE] == 53) {
                vStat.resetAll(incomingPacket);
                sendResponse = true;
                tempUpdateString = tempUpdateString + 5 +
                                   " Name: " + vStat.vName +
                                   " Loc: " + vStat.location +
                                   " Dest: " + vStat.destination +
                                   " NextLoc: " + vStat.nextLocation +
                                   " Addr: " + vStat.destinationAddress +
                                   " Pass: " + vStat.passengers +
                                   " CObj: " + vStat.currentObjective +
                                   " Spd: " + vStat.baseSpeed +
                                   " DStatus: " + vStat.driveStatus +
                                   " NxtVrtType: " + vStat.nextVertType;
            }
            if (incomingPacket[MESSAGE_TYPE] == UPDATE_REQUEST) {
                sendResponse = true;
                tempUpdateString = tempUpdateString + 9 +
                                   " Name: " + vStat.vName +
                                   " Loc: " + vStat.location +
                                   " Dest: " + vStat.destination +
                                   " NextLoc: " + vStat.nextLocation +
                                   " Addr: " + vStat.destinationAddress +
                                   " Pass: " + vStat.passengers +
                                   " CObj: " + vStat.currentObjective +
                                   " Spd: " + vStat.baseSpeed +
                                   " DStatus: " + vStat.driveStatus +
                                   " NxtVrtType: " + vStat.nextVertType;

                if (DEBUG_COMMS) {
                    Serial.print("Request Response:");
                    Serial.println(tempUpdateString);
                }
            }

            if (sendResponse) {
                const char *updateString = tempUpdateString.c_str();
                Udp.broadcastTo(updateString, NETWORK);
            }
        });
        //Send unicast
        Udp.print("Hello Server!");
    }
    Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

    ledcWrite(SPEED_CHANNEL_LEFT, CAL_SPEED);
    ledcWrite(SPEED_CHANNEL_RIGHT, CAL_SPEED);
    for (int j = 0; j < 4; j++) {
        if (j % 2 > 0) { myMotor.driveLeft(); }
        else { myMotor.driveRight(); }

        for (int i = 0; i < 20; i++) {
            delay(10);
            qtr.calibrate();
        }
    }
    myMotor.driveStop();

    Serial.print("Setup done,");
}

void loop() {

    unsigned int sensors[NUM_SENSORS];
    int posit = qtr.readLine(sensors);

    int monkey;
    if (vStat.driveStatus == DRIVE_FORWARD) {

        monkey = nav.driveForward(posit, oldPosit, sensors[LEFT_IR], sensors[RIGHT_IR], vStat.baseSpeed,
                                  vStat.positionConstant, vStat.deltaConstant, vStat);
        ledcWrite(SPEED_CHANNEL_LEFT, nav.leftModifier);
        ledcWrite(SPEED_CHANNEL_RIGHT, nav.rightModifier);
        myMotor.driveForward();

        addressCounter = 0;

        if (DEBUG_DRIVE) {
            Serial.print("drive forward:");
            printStuff(posit, sensors, nav.leftModifier, nav.rightModifier);
        }
    } else if (vStat.driveStatus == DRIVE_LEFT) {
        monkey = nav.driveLeft(posit, oldPosit, sensors[LEFT_IR], sensors[RIGHT_IR], vStat.baseSpeed,
                               vStat.positionConstant, vStat.deltaConstant, vStat);
        ledcWrite(SPEED_CHANNEL_LEFT, nav.leftModifier);
        ledcWrite(SPEED_CHANNEL_RIGHT, nav.rightModifier);
        myMotor.driveForward();

        addressCounter = 0;

        if (DEBUG_DRIVE) {
            printStuff(posit, sensors, nav.leftModifier, nav.rightModifier);
        }
    } else if (vStat.driveStatus == DRIVE_RIGHT) {

        monkey = nav.driveRight(posit, oldPosit, sensors[LEFT_IR], sensors[RIGHT_IR], vStat.baseSpeed,
                                vStat.positionConstant, vStat.deltaConstant, vStat);
        ledcWrite(SPEED_CHANNEL_LEFT, nav.leftModifier);
        ledcWrite(SPEED_CHANNEL_RIGHT, nav.rightModifier);
        myMotor.driveForward();

        addressCounter = 0;

        if (DEBUG_DRIVE) {
            printStuff(posit, sensors, nav.leftModifier, nav.rightModifier);
        }
    } else if (vStat.driveStatus == DRIVE_TO_ADDRESS){
        monkey = nav.driveToAddress(posit, oldPosit, sensors[LEFT_IR], sensors[RIGHT_IR],
                vStat.baseSpeed, vStat.positionConstant, vStat.deltaConstant, addressCounter,
                vStat);
        ledcWrite(SPEED_CHANNEL_LEFT, nav.leftModifier);
        ledcWrite(SPEED_CHANNEL_RIGHT, nav.rightModifier);
        myMotor.driveForward();

        addressCounter++;
        if (DEBUG_DRIVE) {
            printStuff(posit, sensors, nav.leftModifier, nav.rightModifier);
        }

    }else {
        myMotor.driveStop();
        if (DEBUG_DRIVE) {
            printStuff(posit, sensors, nav.leftModifier, nav.rightModifier);
        }
    }

    oldPosit = posit;

    if(pile++ > PILE_TIMER * 2) { 
      printStuff(posit, sensors, nav.leftModifier, nav.rightModifier); 
      pile = 0;
    }
}

void printStuff(int posit, unsigned int sensors[], int leftModifier, int rightModifier){
   String temp = "Type:";
    //temp = temp + 8 + " Pos: " + posit + " OldPos: " + oldPosit[oldPositCounter] + " LeftMod: " + nav.leftModifier + " RightMod: "  + nav.rightModifier  + " LeftIR: " + sensors[7] + " RightIR: " + sensors[0] + " PosConst " + vStat.positionConstant + " DeltaConst " + vStat.deltaConstant + " DeltaDelay: " + vStat.deltaDelay + " Base: " + vStat.baseSpeed + " DStat " + vStat.driveStatus + " Integral: " + vStat.integralCorrection; 
    temp = temp + 8 +
            " Pos: " + posit +
            " OldPos: " + oldPosit +
            " LeftMod: " + nav.leftModifier +
            " RightMod: "  + nav.rightModifier  +
            " LeftIR: " + sensors[7] +
            " RightIR: " + sensors[0] +
            " PosConst " + vStat.positionConstant +
            " DeltaConst " + vStat.deltaConstant +
            " Base: " + vStat.baseSpeed +
            " DStat " + vStat.driveStatus;

    const char *outgoingPacket = temp.c_str();
    Serial.println(outgoingPacket);
    Udp.broadcastTo(outgoingPacket, NETWORK);
}

