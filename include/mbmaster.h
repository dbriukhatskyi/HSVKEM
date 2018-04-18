/*
 * mbmaster.h
 *
 * Created: 21.11.2016 16:49:45
 *  Author: dmitry
 */ 


#ifndef MBMASTER_H_
#define MBMASTER_H_

void forceAllCoils(uint8_t coils);
void forceSingleCoil(uint8_t coil, bool value);


#endif /* MBMASTER_H_ */