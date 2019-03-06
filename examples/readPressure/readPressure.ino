#include "DLH.h"

DLH pressureSensor;

void setup() {
  Serial.begin(9600);  // start serial for output
  delay(1000);

  Serial.println("Arduino Connected");
}

void loop() {
  
  Serial.println(pressureSensor.readPressure());
  
  delay(500);
}
