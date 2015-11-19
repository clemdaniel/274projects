
#include "oi.h"
#ifndef INCLUDE_SENSORS_H
#define INCLUDE_SENSORS_H

#include <avr/io.h>
#include <stdio.h>
#include "cmod.h"

uint16_t getWallDistance(void);
uint16_t[] getBumps(void);
int transmit(char* string);

#endif
