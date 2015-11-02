
#include "oi.h"
#ifndef INCLUDE_SENSORS_H
#define INCLUDE_SENSORS_H

#include <avr/io.h>
#include <stdio.h>
#include "cmod.h"

void readSensors(void);
void readGroupPacket3(void);
void readWallSignal(void);
void readCliffSensors(void);
int transmit(char* string);
uint16_t twoUBytesIntoInt(uint8_t hi, uint8_t lo);
int16_t twoBytesIntoInt(uint8_t hi, uint8_t lo);


#endif
