/*
 *  This sketch controls a vehicle using the avcs system
 */

#include "WiFi.h"
#include "AVCSIRNav.h"
#include "AVCSMotor.h"
#include "globals.h"

AVCSMotor myMotor;
IRNav nav;

int freq = 5000;
int speedChannelOne = 0;
int speedChannelTwo = 0;
int resolution = 8;

void setup() {
  Serial.begin(115200);
    pinMode(frontRightIR, INPUT);
    pinMode(frontLeftIR, INPUT);
    pinMode(backRightIR, INPUT);
    pinMode(backLeftIR, INPUT);
  myMotor.leftSpeed = 200;
  myMotor.rightSpeed = 200;
  myMotor.driveForward();
//  ledcSetup(speedChannelOne, freq, resolution);
//  ledcAttachPin(speedControlLeft, speedChannelOne);
//  ledcSetup(speedChannelTwo, freq, resolution);
//  ledcAttachPin(speedControlRight, speedChannelTwo);
  
//  Serial.printf("Connecting to %s \n", ssid);
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println(" connected");

//  pinMode(frontRightIR, INPUT);
//  pinMode(frontLeftIR, INPUT);
//  pinMode(backRightIR, INPUT);
//  pinMode(backLeftIR, INPUT);
//
//  pinMode(motorRight1, OUTPUT);
//  pinMode(motorRight2, OUTPUT);
//  pinMode(motorLeft1, OUTPUT);
//  pinMode(motorLeft2, OUTPUT);

//  pinMode(speedControlLeft, OUTPUT);
//  pinMode(speedControlRight, OUTPUT);


//  Udp.begin(localUdpPort);
//  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  Serial.println("Setup done");
}

void loop() {

//  ledcWrite(speedChannelOne, speedVal);
//  ledcWrite(speedChannelOne, speedVal);

  nav.readAll();
  nav.printValues();
  nav.adjustSpeed(myMotor);
  delay(500);

//  int packetSize = Udp.parsePacket();
//  if (packetSize)
//  {
//    // receive incoming UDP packets
//    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
//    int len = Udp.read(incomingPacket, 255);
//    if (len > 0)
//    {
//      incomingPacket[len] = 0;
//    }
//    Serial.printf("UDP packet contents: %s\n", incomingPacket);
//
//    driveStatus = incomingPacket[0]-48;
//
//    Serial.printf("Drive status: %d\n", driveStatus);
//
//    // send back a reply, to the IP address and port we got the packet from
//    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//    Udp.write(replyPacket);
//    Udp.endPacket();
//  }

//  Serial.print(" front right IR: ");
//  Serial.print(frIR);
//  Serial.print(" front left IR: ");
//  Serial.print(flIR);
//  Serial.print(" back right IR: ");
//  Serial.print(brIR);
//  Serial.print(" back left IR: ");
//  Serial.println(blIR);
//  Serial.print(" Drive Status: ");
//  Serial.println(driveStatus);
//  delay(1000);


//  if(driveStatus == 0)
//  {
//    driveStop();
//  }
//  if(driveStatus == 1)
//  {
//    if(!frIR && !flIR)
//    {
//      driveForward();
//    }
//    else if(!flIR && frIR)
//    {
//     driveRight();
//    }
//    else if(!frIR && flIR)
//    {
//      driveLeft();
//    }
//    else
//    {
//      driveStop();
//    }
//  }
}


