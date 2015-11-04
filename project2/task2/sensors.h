
#include "oi.h"
#ifndef INCLUDE_SENSORS_H
#define INCLUDE_SENSORS_H

#include <avr/io.h>
#include <stdio.h>
#include "cmod.h"

uint8_t sensorList[52];
uint8_t wheelLeft, wheelRight, bumpLeft, bumpRight;
uint16_t cliffL, cliffFL, cliffFR, cliffR;

void readSensors(void);
int transmit(char* string);

#endif
