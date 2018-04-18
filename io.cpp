/*
 * io.cpp
 *
 * Created: 21.04.2017 15:47:49
 *  Author: dmitry
 */ 

#include <avr/io.h>
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

bool input(uint8_t addr) {
    switch (addr) {
        case 9:
            return PINC && (1 << 1);
        case 10:
            return PINC && (1 << 0);
        case 11:
            return PINC && (1 << 3);
        case 12:
            return PINC && (1 << 2);
        case 13:
            return PINC && (1 << 4);
        case 14:
            return PINC && (1 << 5);
        case 15:
            return PINC && (1 << 7);
        case 16:
            return PINC && (1 << 6);
    }

    return false;
}