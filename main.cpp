/*
 * SmartEM.cpp
 *
 * Created: 06.03.2017 16:46:52
 * Author : dmitry
 */ 

#include <avr/io.h>
#include "include/main.h"
#include "include/time.h"
#include "include/pulse_counter.h"
#include "MB/include/mb.h"
#include "MB/include/mbport.h"
#include "include/io.h"


#define RISING_EDGE(cur, prev, bitNum) (!(prev & (1 << bitNum)) && (cur & (1 << bitNum)))
#define FALLING_EDGE(cur, prev, bitNum) (!(cur & (1 << bitNum)) && (prev & (1 << bitNum)))


void processInputs() {
    static uint8_t lastStates1_8 = 0;
    static uint8_t lastStates9_16 = 0;
    
    static uint8_t currentStates1_8 = 0;
    static uint8_t currentStates9_16 = 0;
    
    static uint32_t lastOnTime[16] = { 0 };
        
    debounceInputs();

    currentStates1_8 = PINA;
    currentStates9_16 = PINC;
    
    // polling pulse inputs
    for (uint8_t i = 0; i < 8; i++) {
        if (FALLING_EDGE(currentStates1_8, lastStates1_8, i)) {
            lastOnTime[i] = millis();
        } else if (RISING_EDGE(currentStates1_8, lastStates1_8, i)) {    
            if (millis() - lastOnTime[i] > TRESHOLD_TIME) {
                addPulse(pinNumber(i));
            } 
        }
        
        if (FALLING_EDGE(currentStates9_16, lastStates9_16, i)) {
            lastOnTime[i + 8] = millis();
        } else if (RISING_EDGE(currentStates9_16, lastStates9_16, i)) {    
            if (millis() - lastOnTime[i + 8] > TRESHOLD_TIME) {
                addPulse(pinNumber(i + 8));
            } 
        }
    }
    
    lastStates1_8 = currentStates1_8;
    lastStates9_16 = currentStates9_16;
    
    updatePowerValues();
}


int main(void) {
    initPorts();
    initModbus();
    initTimer();
    
    // Error 2 LED - on
    PORTJ = 0b01000000;

    uint32_t lastUpdate = millis();
    
    initCycleTime();
    
    while (1) {
        if (millis() - lastUpdate > 1000) {
            lastUpdate = millis();
            // Blink CPU Run LED
            PORTJ ^= (1 << 5);
        }

        processInputs();
        eMBPoll();
        updateCycleTime();
    }
}

