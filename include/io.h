/*
 * io.h
 *
 * Created: 30.01.2019 15:31:00
 *  Author: Dmitry
 */ 


#ifndef IO_H_
#define IO_H_

#define INPUTS_COUNT 16
#define TRESHOLD_TIME 20
#define DEBOUNCE_TIME 50

#define TOGGLE_BIT(word, bit) word ^= (1 << (bit))
#define SET_BIT(word, bit) word |= (1 << (bit))
#define RESET_BIT(word, bit) word &= ~(1 << (bit))
#define PIN_STATE(port, pin) (!!((port) & (1 << (pin))))

int pinNumber(int inputNumber);

bool input(uint8_t addr);

void debounceInputs();

bool filteredInput(uint8_t addr);

void output(uint8_t addr, uint8_t state);

uint8_t outputState(uint8_t addr);


#endif /* IO_H_ */