#include "DLH.h"

/*
Single    0xAA
Average2  0xAC
Average4  0xAD
Average8  0xAE
Average16 0xAF
*/
DLH pressureSensor(0xAF); //Set # to Average

void setup() {
  Serial.begin(9600);  // start serial for output
  delay(1000);

  Serial.println("Arduino Connected");
}

void loop() {
  
  Serial.println(pressureSensor.readPressure());
  
  delay(500);
}