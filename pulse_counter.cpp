/*
 * pulse_counter.cpp
 *
 * Created: 21.06.2017 17:08:23
 *  Author: dmitry
 */ 
#include "include/time.h"

#define PWR_UPD_INTERVAL 1000 // millis
#define PWR_AVG_VAL_COUNT 16 // only powers of 2 allowed
#define NUMBER_OF_COUNTERS 16

static uint32_t pulseCount[NUMBER_OF_COUNTERS] = { 0 };
static uint16_t power[NUMBER_OF_COUNTERS] = { 0 };

// for power calculation
static uint32_t lastValues[NUMBER_OF_COUNTERS * PWR_AVG_VAL_COUNT] = { 0 };
static uint8_t tailIndex = 0;


void addPulse(uint8_t inpNum) {
    pulseCount[inpNum]++;
}

uint32_t getCount(uint8_t inpNum) {
    return pulseCount[inpNum];
}

void resetCount(uint8_t inpNum) {
    pulseCount[inpNum] = 0;

    for (uint8_t i = 0; i < PWR_AVG_VAL_COUNT; i++) {
        lastValues[inpNum * PWR_AVG_VAL_COUNT + i] = 0;
    }
}

uint16_t getPower(uint8_t inpNum) {
    return power[inpNum];
}

void updatePowerValues() {
    static uint32_t lastUpdate = 0;
    
    if (millis() - lastUpdate > PWR_UPD_INTERVAL) {
        lastUpdate = millis();

        for (uint8_t i = 0; i < NUMBER_OF_COUNTERS; i++) {
            uint32_t pwr = ((pulseCount[i] - lastValues[i * PWR_AVG_VAL_COUNT + tailIndex]) * 100L) >> 4; // div 16
            power[i] = pwr;
            lastValues[i * PWR_AVG_VAL_COUNT + tailIndex] = pulseCount[i];
        }

        for (uint8_t i = 0; i < NUMBER_OF_COUNTERS; i++) {
            lastValues[i * PWR_AVG_VAL_COUNT + tailIndex] = pulseCount[i];
        }
        
        tailIndex++;
        tailIndex &= PWR_AVG_VAL_COUNT - 1; // ring buffer
    }
}