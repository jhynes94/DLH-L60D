/*
  DLH.cpp - Library for ___.
  Created by Justin HB, March 6, 2019.
*/
#include "DLH.h"


DLH::DLH()
{
}


uint32_t DLH::readPressure(){
  
  uint32_t pressure = 0;
  
  Wire.begin();
  Wire.beginTransmission(0x29);
  
  /*
  Single    0xAA
  Average2  0xAC
  Average4  0xAD
  Average8  0xAE
  Average16 0xAF
  */
  Wire.write(0xAF); //Sets Numbers to average
  Wire.endTransmission();
  delay(63);
  
  
  Wire.requestFrom(0x29, 7); //Read 7 bytes

  uint8_t byteCounter = 0;
  while (Wire.available()) {
    uint8_t c = Wire.read();

    //Log binary code
    //printBinNum(c); Serial.print(" ");

    uint32_t temp = c;
      
    if(byteCounter == 1){
      pressure = temp << 10;
    }
    if(byteCounter == 2){
      pressure += temp << 2;
    }
    if(byteCounter == 3){;
      pressure += (temp & ( 1 << 6 )) >> 6;
      pressure += ((temp & ( 1 << 7 )) >> 7)*2;
    }
    
    byteCounter++;
  }

  return pressure;
}
