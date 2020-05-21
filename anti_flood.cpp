/*
 * anti_flood.cpp
 *
 * Created: 30.01.2019 16:19:14
 *  Author: Dmitry
 */ 

#include <avr/io.h>
#include "include/io.h"
#include "include/time.h"

#define GROUPS_COUNT 4
#define FORCE_MAX_DURATION 900000L // 15 min = 900 000 ms

uint8_t sensorInputs[GROUPS_COUNT] = { 1, 2, 3, 4 };
uint8_t valveOutputs[GROUPS_COUNT] = { 1, 2, 3, 4 };

bool sensorNormallyOpen[GROUPS_COUNT] = { false, false, false, false }; // false = flood alarm when input is 0
bool relayStateOnAlarm[GROUPS_COUNT] = { true, true, true, true }; // relay state on alarm, true = energized

bool permitValveOpen[GROUPS_COUNT] = { 0 };
bool forceValveOpen[GROUPS_COUNT] = { 0 };
    
uint32_t forceAppliedTime[GROUPS_COUNT] = { 0 };

void processAntiFlood() {
    for (uint8_t i = 0; i < GROUPS_COUNT; i++) {
        if (permitValveOpen[i]) {
            bool command = sensorNormallyOpen[i] ^ filteredInput(sensorInputs[i]);
            
            if (!command && forceValveOpen[i]) {
                if (millis() - forceAppliedTime[i] < FORCE_MAX_DURATION) {
                    command = true;
                } else {
                    forceValveOpen[i] = false;
                }
            }
            
            output(valveOutputs[i], command ^ relayStateOnAlarm[i]);
        }
        else {
            output(valveOutputs[i], relayStateOnAlarm[i]);
        }
    }    
}

void setForceValveOpen(uint8_t group, bool value) {
    if (value) {
        forceAppliedTime[group] = millis();
    }
            
    forceValveOpen[group] = value;
}

bool getForceValveOpen(uint8_t group) {
    return forceValveOpen[group];
}

void setPermitValveOpen(uint8_t group, bool value) {
    permitValveOpen[group] = value;
}

bool getPermitValveOpen(uint8_t group) {
    return permitValveOpen[group];
}