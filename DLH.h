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
        
        /*
        Single    0xAA
        Average2  0xAC
        Average4  0xAD
        Average8  0xAE
        Average16 0xAF
        */
        DLH(uint32_t command);
        
        //value = 0-262143
        uint32_t readPressure(void);

        void setMeasurementCommand(uint32_t command);
    private:
        uint32_t _deviceAddress = 0x29;
        uint32_t measCommand = 0xAF;
};

#endif