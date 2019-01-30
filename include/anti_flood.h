/*
 * anti_flood.h
 *
 * Created: 30.01.2019 16:19:27
 *  Author: Dmitry
 */ 


#ifndef ANTI_FLOOD_H_
#define ANTI_FLOOD_H_

void processAntiFlood();

void setForceValveOpen(uint8_t group, bool value);

bool getForceValveOpen(uint8_t group);

void setPermitValveOpen(uint8_t group, bool value);

bool getPermitValveOpen(uint8_t group);

#endif /* ANTI_FLOOD_H_ */