/*
 * pulse_counter.h
 *
 * Created: 22.06.2017 13:54:27
 *  Author: dmitry
 */ 


#ifndef PULSE_COUNTER_H_
#define PULSE_COUNTER_H_

void addPulse(uint8_t inpNum);

uint32_t getCount(uint8_t inpNum);

void resetCount(uint8_t inpNum);

uint16_t getPower(uint8_t inpNum);

void updatePowerValues();

#endif /* PULSE_COUNTER_H_ */