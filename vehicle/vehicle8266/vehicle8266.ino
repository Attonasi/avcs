/*
 *  This sketch controls a vehicle using the avcs system
 */

#include "ESP8266WiFi.h"
#include "AVCSIRNav.h"
#include "AVCSMotor.h"
#include "globals.h"

AVCSMotor myMotor;
IRNav nav;

int counter = 150;

void setup() {
  Serial.begin(115200);
  myMotor.leftSpeed = 200;
  myMotor.rightSpeed = 200;
  myMotor.driveStop();
  
//  Serial.printf("Connecting to %s \n", ssid);
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println(" connected");
  
//  Udp.begin(localUdpPort);
//  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  Serial.println("Setup done");
}

void loop() {
  Serial.println("Loop");
  nav.readAll();
  nav.printValues();
  delay(1000);

  myMotor.leftSpeed = counter;
  myMotor.rightSpeed = counter;
  myMotor.driveForward();
  Serial.print(" Speed is: ");
  Serial.println(counter+=10);
}
