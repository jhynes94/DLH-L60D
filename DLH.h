/*
  DLH.cpp - Library for ___.
  Created by Justin HB, March 6, 2019.
*/

#ifndef DLH_h
#define DLH_h

#include "Arduino.h"
#include <Wire.h>

class DLH
{
    public:
        DLH();
        
        //value = 0-262143
        uint32_t readPressure(void);
    private:
        uint32_t _deviceAddress = 0x29;
};

#endif