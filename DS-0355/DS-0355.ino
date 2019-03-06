#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  Wire.beginTransmission(0x29);
  Wire.write(0xAF);  
  Wire.endTransmission();

  Wire.requestFrom(0x29, 1);
  while (Wire.available()) { // slave may send less than requested
    uint8_t c = Wire.read(); // receive a byte as character
    Serial.println(c, BIN);
  }
}

void loop() {

  Wire.beginTransmission(0x29);
  Wire.write(0xAF);  
  Wire.endTransmission();
  delay(200);
  
  
  uint32_t pressure = 0;
  
  Wire.requestFrom(0x29, 7); //Read 7 bytes

  uint8_t byteCounter = 0;
  while (Wire.available()) { // slave may send less than requested
    uint8_t c = Wire.read(); // receive a byte as character
    printBinNum(c); Serial.print(" ");

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

  Serial.print("\n"); Serial.print(pressure); Serial.print(" "); Serial.println(map(pressure, 0, 262143, -100, 100));

  delay(500);
}


void printBinNum(uint8_t num){
  for(int i=0; i<8; i++){
    Serial.print((num & ( 1 << i )) >> i);
  }
}
