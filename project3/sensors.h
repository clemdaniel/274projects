
#include "oi.h"
#ifndef INCLUDE_SENSORS_H
#define INCLUDE_SENSORS_H

#include <avr/io.h>
#include <stdio.h>
#include "cmod.h"

uint8_t sensorList[52];
uint8_t castorWheel, wheelLeft, wheelRight, bumpLeft, bumpRight;
uint16_t wall, cliffL, cliffFL, cliffFR, cliffR;

uint16_t getWallDistance(void);
uint8_t* getBumps(void);
int transmit(char* string);
void readSensors(void);

#endif
