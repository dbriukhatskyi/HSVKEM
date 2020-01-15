/*
 * io.cpp
 *
 * Created: 21.04.2017 15:47:49
 *  Author: dmitry
 */ 

#include <avr/io.h>
#include "include/time.h"
#include "include/io.h"

uint32_t debounceStart[INPUTS_COUNT + 1] = { 0 };
bool lastStates[INPUTS_COUNT + 1] = { 0 };

int pinNumber(int inputNumber) {
    switch (inputNumber) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return inputNumber;
            
        case 8:
            return 1;
        case 9:
            return 0;
        case 10:
            return 3;
        case 11:
            return 2;
        case 12:
            return 4;
        case 13:
            return 5;
        case 14:
            return 7;
        case 15:
            return 6;
    }
    
    return 0;
}

bool input(uint8_t addr) {
    switch (addr) {
        case 1:
            return ((~PINA) & (1 << 0));
        case 2:
            return ((~PINA) & (1 << 1));
        case 3:
            return ((~PINA) & (1 << 2));
        case 4:
            return ((~PINA) & (1 << 3));
        case 5:
            return ((~PINA) & (1 << 4));
        case 6:
            return ((~PINA) & (1 << 5));
        case 7:
            return ((~PINA) & (1 << 6));
        case 8:
            return ((~PINA) & (1 << 7));
            
        case 9:
            return ((~PINC) & (1 << 1));
        case 10:
            return ((~PINC) & (1 << 0));
        case 11:
            return ((~PINC) & (1 << 3));
        case 12:
            return ((~PINC) & (1 << 2));
        case 13:
            return ((~PINC) & (1 << 4));
        case 14:
            return ((~PINC) & (1 << 5));
        case 15:
            return ((~PINC) & (1 << 7));
        case 16:
            return ((~PINC) & (1 << 6));
    }

    return false;
}

void debounceInputs() {
    for (int i = 1; i <= INPUTS_COUNT; i++) {
        if (input(i)) {
            if (!lastStates[i]) {
                debounceStart[i] = millis();
            }           
             
            lastStates[i] = true;
        } else {
            lastStates[i] = false;
        }
    }
}

bool filteredInput(uint8_t addr) {
    if (input(addr) && lastStates[addr] && (millis() - debounceStart[addr] > DEBOUNCE_TIME)) {
        return true;
    }
    
    return false;
}

uint8_t outputState(uint8_t ordinal) {
    switch (ordinal) {
        case 1:
            return PIN_STATE(PINK, 0);
        case 2:
            return PIN_STATE(PINK, 1);
        case 3:
            return PIN_STATE(PINK, 2);
        case 4:
            return PIN_STATE(PINK, 3);
        case 5:
            return PIN_STATE(PINK, 4);
        case 6:
            return PIN_STATE(PINK, 5);
        case 7:
            return PIN_STATE(PINK, 6);
        case 8:
            return PIN_STATE(PINK, 7);
    }

    return 0;
}

void output(uint8_t ordinal, uint8_t state) {
    switch (ordinal) {
        case 1:
            if (state) {
                SET_BIT(PORTK, 0);
            } else {
                RESET_BIT(PORTK, 0);
            }
            break;
        case 2:
            if (state) {
                SET_BIT(PORTK, 1);
            } else {
                RESET_BIT(PORTK, 1);
            }
            break;
        case 3:
            if (state) {
                SET_BIT(PORTK, 2);
            } else {
                RESET_BIT(PORTK, 2);
            }
            break;
        case 4:
            if (state) {
                SET_BIT(PORTK, 3);
            } else {
                RESET_BIT(PORTK, 3);
            }
            break;
        case 5:
            if (state) {
                SET_BIT(PORTK, 4);
            } else {
                RESET_BIT(PORTK, 4);
            }
            break;
        case 6:
            if (state) {
                SET_BIT(PORTK, 5);
            } else {
                RESET_BIT(PORTK, 5);
            }
            break;
        case 7:
            if (state) {
                SET_BIT(PORTK, 6);
            } else {
                RESET_BIT(PORTK, 6);
            }
            break;
        case 8:
            if (state) {
                SET_BIT(PORTK, 7);
            } else {
                RESET_BIT(PORTK, 7);
            }
            break;
    }        
}

////
/*
void toggle(uint8_t relay) {
    PORTK ^= (1 << relay);
}

void turnOn(uint8_t relay) {
    PORTK |= (1 << relay);
}

void turnOff(uint8_t relay) {
    PORTK &= ~(1 << relay);
}

void out(uint8_t relay, uint8_t state) {
    //TODO
}
*/


/*
void toggle(uint8_t relay);
void turnOn(uint8_t relay);
void turnOff(uint8_t relay);

typedef void(*action_t)(uint8_t);

#define QUEUE_SIZE 32

struct queue_t {
    action_t actions[QUEUE_SIZE];
    uint8_t arguments[QUEUE_SIZE];
    uint32_t triggerTimes[QUEUE_SIZE];
    bool active[QUEUE_SIZE];
};

queue_t tasks;
uint8_t lastTask = 0;
*/

/*
void toggleNextRelay() {
    static uint8_t relayNumber = 0;
        
    PORTK ^= (1 << relayNumber);
    relayNumber = (relayNumber + 1) & 0x07;
    
    if (relayNumber > 7) {
        relayNumber = 0;
        PORTK = 0xFF;
    }
}



void addTask(action_t task, uint8_t arg, uint32_t timeMillis) {
    uint8_t emptySlot = 0xFF;

    for (uint8_t i = 0; i < QUEUE_SIZE; i++) {
        uint8_t slot = (i + lastTask) & (QUEUE_SIZE - 1);

        if (!tasks.active[i]) {
            emptySlot = i;
            lastTask = i;
        }
    }
}

void processTasks() {

}
*/