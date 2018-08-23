#include <WiFi.h>
#include <AsyncUDP.h>
#include "network_globals.h"
#include "NWKCity.h"
#include "NWKVehicle.h"
//#include <iostream>

char* incomingPacket;  // buffer for incoming packets
uint8_t packetLength;

AsyncUDP Udp;
NWKVehicle car_zero;
NWKVehicle car_one;
NWKVehicle car_two;
NWKVehicle car_three;
NWKVehicle car_four;

NWKVehicle carArray[NUM_CARS] = {car_zero, car_one, car_two, car_three, car_four};
NWKCity city;


void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println("Start setup");

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

    if (Udp.listen(KEY_PORT)) {
        Serial.print("UDP listening on ip: ");
        Serial.println(WiFi.localIP());

        Udp.onPacket([](AsyncUDPPacket packet) {
            incomingPacket = (char *) packet.data();
            packetLength = packet.length();
            incomingPacket[packetLength] = 0;
            bool sendToVehicle = false;
            String tempString = "Type: ";

            int carKey = incomingPacket[NAME_ONES] - CHAR_ZERO;
            carKey += (incomingPacket[NAME_TENS] - CHAR_ZERO) * 10;
            carKey += (incomingPacket[NAME_HUNDS] - CHAR_ZERO) * 100;
            carKey += (incomingPacket[NAME_THOUS] - CHAR_ZERO) * 1000;
            carKey -= VEHICLE_ZERO;

            if (DEBUG) {
                Serial.print("Inc: ");
                Serial.println(incomingPacket);
            }

            if (incomingPacket[TYPE] == 48) {

                sendToVehicle = true;

                carArray[carKey].changeVehicleDestination(incomingPacket);

                city.setShortestPath(carArray[carKey].location % 100,
                                     carArray[carKey].destination % 100);

                city.printCostParent();

                carArray[carKey].writeVehiclePath(carArray[carKey].location % 100,
                                                  carArray[carKey].destination % 100,
                                                  city.parent);
                Serial.printf("Edge: %d Next vert Type: %d \n", city.edgeArray[carArray[carKey].location%100].eName, city.edgeArray[carArray[carKey].location%100].destType);
                carArray[carKey].nextVertType = city.edgeArray[carArray[carKey].location%100].destType;

                carArray[carKey].printPath();

                tempString = tempString + 1 +
                             " Name: " + carArray[carKey].vName +
                             " Loc: " + carArray[carKey].location +
                             " Dest: " + carArray[carKey].destination +
                             " NextLoc: " + carArray[carKey].nextLocation +
                             " Addr: " + carArray[carKey].destinationAddress +
                             " Pass: " + carArray[carKey].passengers +
                             " CObj: " + carArray[carKey].currentObjective +
                             " Spd: " + carArray[carKey].baseSpeed +
                             " DStatus: " + carArray[carKey].driveStatus +
                             " NxtVrtType: " + carArray[carKey].nextVertType;

                if (DEBUG_COMMS) {
                    Serial.print("Changing Destination for Vehicle: ");
                    Serial.println(carKey);
                    Serial.println(tempString);
                }
            }

            if (incomingPacket[TYPE] == UPDATE_STATUS) {

                carArray[carKey].updateVehicleStatus(incomingPacket);

                if (carArray[carKey].location == carArray[carKey].destination
                    && carArray[carKey].currentObjective > PARK) {
                    sendToVehicle = true;
                    Serial.print("Vehicle arriving at destination: ");
                    Serial.println(carKey);
                    carArray[carKey].arriveAtDestination();

                    tempString = tempString + DRIVE_TO_ADDRESS +
                                 " Name: " + carArray[carKey].vName +
                                 " Loc: " + carArray[carKey].location +
                                 " Dest: " + carArray[carKey].destination +
                                 " NextLoc: " + carArray[carKey].nextLocation +
                                 " Addr: " + carArray[carKey].destinationAddress +
                                 " Pass: " + carArray[carKey].passengers +
                                 " CObj: " + carArray[carKey].currentObjective +
                                 " Spd: " + carArray[carKey].baseSpeed +
                                 " DStatus: " + carArray[carKey].driveStatus +
                                 " NxtVrtType: " + carArray[carKey].nextVertType;

                    if (DEBUG_COMMS) {
                        Serial.print("Drive to address: ");
                        Serial.println(carKey);
                        Serial.println(tempString);
                    }
                }
                else if (carArray[carKey].location == carArray[carKey].nextLocation
                         && carArray[carKey].currentObjective > PARK) {
                    sendToVehicle = true;

                    Serial.print("Vehicle requesting new directions: ");
                    Serial.println(carKey);
                    carArray[carKey].changeNextVertex(city.edgeArray[carArray[carKey].currentPath[carArray[carKey].pathIterator]],
                                                      city.edgeArray[carArray[carKey].currentPath[carArray[carKey].pathIterator-1]]);

                    carArray[carKey].pathIterator -= 1;

                    carArray[carKey].printPath();

                    String tempString = "Type: ";
                    tempString = tempString + CHANGE_NEXT_VERT +
                                 " Name: " + carArray[carKey].vName +
                                 " Loc: " + carArray[carKey].location +
                                 " Dest: " + carArray[carKey].destination +
                                 " NextLoc: " + carArray[carKey].nextLocation +
                                 " Addr: " + carArray[carKey].destinationAddress +
                                 " Pass: " + carArray[carKey].passengers +
                                 " CObj: " + carArray[carKey].currentObjective +
                                 " Spd: " + carArray[carKey].baseSpeed +
                                 " DStatus: " + carArray[carKey].driveStatus +
                                 " NxtVrtType: " + carArray[carKey].nextVertType;

                    if (DEBUG_COMMS) {
                        Serial.print("Changing Destination for Vehicle: ");
                        Serial.println(carKey);
                        Serial.println(tempString);
                    }
                }
            }

            if (incomingPacket[TYPE] == 5) {

                sendToVehicle = true;

                Serial.print("Vehicle Reset: ");
                Serial.println(carKey);
                carArray[carKey].writeAll(incomingPacket);
                String tempString = "Type: ";

                tempString = tempString + 5 +
                                  " Name: " + carArray[carKey].vName +
                                  " Loc: " + carArray[carKey].location +
                                  " Dest: " + carArray[carKey].destination +
                                  " NextLoc: " + carArray[carKey].nextLocation +
                                  " Addr: " + carArray[carKey].destinationAddress +
                                  " Pass: " + carArray[carKey].passengers +
                                  " CObj: " + carArray[carKey].currentObjective +
                                  " Spd: " + carArray[carKey].baseSpeed +
                                  " DStatus: " + carArray[carKey].driveStatus +
                                  " NxtVrtType: " + carArray[carKey].nextVertType;
            }

            if (sendToVehicle) {
                const char *updateString = tempString.c_str();
                Udp.broadcastTo(updateString, carKey + VEHICLE_ZERO);
            }
        });
        Udp.print("Network Initiated");
    }
    Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), KEY_PORT);

    for (int i = 0; i < NUM_CARS; i++) {
        carArray[i].vName = VEHICLE_ZERO + i;
        carArray[i].currentPath[0] = START_LOCATION;
        carArray[i].pathIterator = ZERO;
        carArray[i].baseSpeed = START_SPEED;
        carArray[i].currentObjective = ZERO;
        carArray[i].destination = START_LOCATION;
        carArray[i].nextLocation = START_LOCATION;
        carArray[i].location = START_LOCATION;
        carArray[i].nextVertType = L_TEE;
        carArray[i].passengers = ZERO;
        carArray[i].driveStatus = PARK;
    }

    city.setEdgeVal(E_ZERO_I, E_ZERO, L_TEE, E_ZERO_W, NO_TURN, NO_TURN, E_ONE_I);
    city.setEdgeVal(E_ONE_I, E_ONE, L_NINETY, E_ONE_W, E_TWO_I, NO_TURN, NO_TURN);
    city.setEdgeVal(E_TWO_I, E_TWO, PLUS, E_TWO_W, NO_TURN, E_SEVEN_I, E_EIGHT_I);
    city.setEdgeVal(E_THREE_I, E_THREE, L_NINETY, E_THREE_W, E_ZERO_I, NO_TURN, NO_TURN);
    city.setEdgeVal(E_FOUR_I, E_FOUR, TEE, E_FOUR_W, NO_TURN, E_FIVE_I, E_SIX_I);
    city.setEdgeVal(E_FIVE_I, E_FIVE, TEE, E_FIVE_W, E_ONE_I, NO_TURN, NO_TURN);
    city.setEdgeVal(E_SIX_I, E_SIX, PLUS, E_SIX_W, E_EIGHT_I, NO_TURN, E_SEVEN_I);
    city.setEdgeVal(E_SEVEN_I, E_SEVEN, L_NINETY, E_SEVEN_W, E_NINE_I, NO_TURN, NO_TURN);
    city.setEdgeVal(E_EIGHT_I, E_EIGHT, PLUS, E_EIGHT_W, E_THIRTEEN_I, NO_TURN, E_FOURTEEN_I);
    city.setEdgeVal(E_NINE_I, E_NINE, L_NINETY, E_NINE_W, E_FIFTEEN_I, NO_TURN, NO_TURN);
    city.setEdgeVal(E_TEN_I, E_TEN, L_TEE, E_TEN_W, E_FOUR_I, NO_TURN, E_THREE_I);
    city.setEdgeVal(E_ELEVEN_I, E_ELEVEN, PLUS, E_ELEVEN_W, E_SIX_I, NO_TURN, E_FIVE_I);
    city.setEdgeVal(E_TWELVE_I, E_TWELVE, L_NINETY, E_TWELVE_W, E_TEN_I, NO_TURN, NO_TURN);
    city.setEdgeVal(E_THIRTEEN_I, E_THIRTEEN, PLUS, E_THIRTEEN_W, E_ELEVEN_I, NO_TURN, E_TWELVE_I);
    city.setEdgeVal(E_FOURTEEN_I, E_FOURTEEN, L_NINETY, E_FOURTEEN_W, E_SEVENTEEN_I, NO_TURN, NO_TURN);
    city.setEdgeVal(E_FIFTEEN_I, E_FIFTEEN, PLUS, E_FIFTEEN_W, NO_TURN, E_FOURTEEN_I, E_THIRTEEN_I);
    city.setEdgeVal(E_SIXTEEN_I, E_SIXTEEN, PLUS, E_SIXTEEN_W, NO_TURN, E_TWELVE_I, E_ELEVEN_I);
    city.setEdgeVal(E_SEVENTEEN_I, E_SEVENTEEN, L_NINETY, E_EIGHT_W, E_SIXTEEN_I, NO_TURN, NO_TURN);

    Serial.println("Setup Finished");
}

void loop() {
    String temp = "Type: ";
    temp = temp + 9;
    const char *outgoing = temp.c_str();
    for (int i = 0; i < NUM_CARS; i++) {
        Udp.broadcastTo(outgoing, carArray[i].vName);
//        if (DEBUG_COMMS) {
//            Serial.print("Request Sent to: ");
//            Serial.println(carArray[i].vName);
//            Serial.println(outgoing);
//        }
    }

    delay(300);
}
