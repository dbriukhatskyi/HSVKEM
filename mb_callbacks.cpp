/*
 * CPPFile1.cpp
 *
 * Created: 27.07.2016 13:43:00
 *  Author: dmitry
 */ 

#define F_OSC 16000000

#include <avr/io.h>
#include "MB/include/mb.h"
#include "MB/include/mbutils.h"
#include "include/pulse_counter.h"

uint8_t states = 0;

inline uint8_t bufferIndex(uint8_t bitIndex) {
    return bitIndex / 8;
}

inline uint8_t bufferOffset(uint8_t bitIndex) {
    return bitIndex & 0x07; // fast version of bitIndex % 8
}

void setHoldingReg(uint16_t addr, uint16_t val) {
    if ((addr < 8) && val) {
        resetCount(addr);
    }
}

eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs) {
    eMBErrorCode    eStatus = MB_ENOERR;    
    USHORT addrBase0 = usAddress - 1;
    uint32_t regValue = 0;

    for (uint8_t i = 0; i < usNRegs; i++) {
        if (addrBase0 + i < 16) {
            if (!(i & 0x01)) {
                regValue = getCount((addrBase0 + i) / 2);                
                pucRegBuffer[2 * i] = (regValue >> 8) & 0xFF;
                pucRegBuffer[2 * i + 1] = regValue & 0xFF;
            } else {
                pucRegBuffer[2 * i] = (regValue >> 24) && 0xFF;
                pucRegBuffer[2 * i + 1] = (regValue >> 16) & 0xFF;
                regValue = 0;
            }
        } else if (addrBase0 + i < 24) {
            uint16_t pwr = getPower(i);
            pucRegBuffer[2 * i] = pwr >> 8;
            pucRegBuffer[2 * i + 1] = pwr & 0xFF;
        } else {
            eStatus = MB_ENOREG;
        }
    }
    
    return eStatus;
}

eMBErrorCode eMBRegHoldingCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode) {
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT addrBase0 = usAddress - 1;
    
    if (eMode == MB_REG_READ) {
        for (uint8_t i = 0; i < usNRegs; i++) {
            pucRegBuffer[2 * i] = 0;
            pucRegBuffer[2 * i + 1] = 0;
        }
    } else if (eMode == MB_REG_WRITE) {
        for (uint8_t i = 0; i < usNRegs; i++) {
            uint16_t regValue = ((uint16_t)pucRegBuffer[2 * i] << 8) | pucRegBuffer[2 * i + 1];
            setHoldingReg(addrBase0 + i, regValue);
        }
    }

    return eStatus;
}

eMBErrorCode eMBRegCoilsCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode) {
    eMBErrorCode    eStatus = MB_ENOREG;

    return eStatus;
}

eMBErrorCode eMBRegDiscreteCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNDiscrete) {
    eMBErrorCode    eStatus = MB_ENOREG;

    return eStatus;
}
