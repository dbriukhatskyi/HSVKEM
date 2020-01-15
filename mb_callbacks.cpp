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
#include "include/time.h"
#include "include/io.h"
#include "include/anti_flood.h"

uint8_t states = 0;

inline uint8_t bufferIndex(uint8_t bitIndex) {
    return bitIndex / 8;
}

inline uint8_t bufferOffset(uint8_t bitIndex) {
    return bitIndex & 0x07; // fast version of bitIndex % 8
}

void setHoldingReg(uint16_t addr, uint16_t val) {
    if ((addr < 16) && val) {
        resetCount(addr);
    }
}

uint8_t discreteState(uint8_t i) {
    if (i > 16) {
        return 0;
    }
    
    return filteredInput(i) ? 1 : 0;
}

uint8_t coilState(uint8_t i) {
    if (i < 4) {
        return getPermitValveOpen(i);
    } else if (i < 8) {
        return getForceValveOpen(i - 4);
    } else if (i < 16) {
        return outputState(i - 7);
    }
    
    return 0;
}

void setCoilState(uint8_t i, uint8_t state) {
    if (i < 4) {
        setPermitValveOpen(i, state);
    } else if (i < 8) {
        setForceValveOpen(i - 4, state);
    } else if ((i >= 12) && (i < 15)) {
        output(i - 7, state);
    }
}

//////////////////////////////////////////////////////////////////////////

eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs) {
    eMBErrorCode    eStatus = MB_ENOERR;    
    USHORT addrBase0 = usAddress - 1;
    uint32_t regValue = 0;

    for (uint8_t i = 0; i < usNRegs; i++) {
        if (addrBase0 + i < 32) {
            if (!(i & 0x01)) {
                regValue = getCount((addrBase0 + i) / 2);                
                pucRegBuffer[2 * i] = (regValue >> 8) & 0xFF;
                pucRegBuffer[2 * i + 1] = regValue & 0xFF;
            } else {
                pucRegBuffer[2 * i] = (regValue >> 24) && 0xFF;
                pucRegBuffer[2 * i + 1] = (regValue >> 16) & 0xFF;
                regValue = 0;
            }
        } else if (addrBase0 + i < 48) {
            uint16_t pwr = getPower(addrBase0 + i - 32);
            pucRegBuffer[2 * i] = pwr >> 8;
            pucRegBuffer[2 * i + 1] = pwr & 0xFF;
        } else if (addrBase0 + i == 48) {
            uint16_t result = (uint16_t) getLastCycleTime();
            pucRegBuffer[2 * i] = result >> 8;
            pucRegBuffer[2 * i + 1] = result & 0xFF;
        } else if (addrBase0 + i == 49) {
            uint16_t result = (uint16_t) getMaxCycleTime();
            pucRegBuffer[2 * i] = result >> 8;
            pucRegBuffer[2 * i + 1] = result & 0xFF;
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
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT addrBase0 = usAddress - 1;

    if (eMode == MB_REG_READ) {
        for (USHORT i = 0; i < (usNCoils / 8) + !!(usNCoils & 0x0007); i++) {
            pucRegBuffer[i] = 0;
        }
        
        for (USHORT i = 0; i < usNCoils; i++) {
            pucRegBuffer[bufferIndex(i)] |= (coilState(addrBase0 + i) << bufferOffset(i));
        }
    } else if (eMode == MB_REG_WRITE) {
        for (USHORT i = 0; i < usNCoils; i++) {
            setCoilState(addrBase0 + i, !!(pucRegBuffer[bufferIndex(i)] & (1 << bufferOffset(i))));
        }
    }

    return eStatus;
}

eMBErrorCode eMBRegDiscreteCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNDiscrete) {
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT addrBase0 = usAddress - 1;

    for (USHORT i = 0; i < usNDiscrete; i++) {
        xMBUtilSetBits(pucRegBuffer, i, 1, discreteState(i + addrBase0) );
    }
    
    return eStatus;
}
