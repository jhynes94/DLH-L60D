/*
  DLH.cpp - Library for ___.
  Created by Justin HB, March 6, 2019.
*/
#include "DLH.h"


DLH::DLH(uint32_t command)
{
  measCommand = command;
}

void printBinNum(uint8_t num){
  for(int i=0; i<8; i++){
    Serial.print((num & ( 1 << i )) >> i);
  }
}

void DLH::setMeasurementCommand(uint32_t command){
  measCommand = command;
}


uint32_t DLH::readPressure(){
  
  uint32_t pressure = 0;
  
  Wire.begin();
  Wire.beginTransmission(0x29);
  
  Wire.write(measCommand); //Sets Numbers to average

  Wire.endTransmission();

  switch(measCommand){
	case 0xAA:
	 	delayMicroseconds(4100);
		break;
	case 0xAC:
		delay(8);
		break;
	case 0xAD:
		delay(15);
	 	delayMicroseconds(700);
		break;
	case 0xAE:
		delay(31);
	 	delayMicroseconds(100);
		break;
	case 0xAF:
		delay(61);
	 	delayMicroseconds(900);
		break;
  }
  
  
  Wire.requestFrom(0x29, 7); //Read 7 bytes

  uint8_t byteCounter = 0;
  while (Wire.available()) {
    uint8_t c = Wire.read();

    //Log binary code
    //Serial.begin(9600);
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
