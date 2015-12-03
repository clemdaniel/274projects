
#include "oi.h"
#ifndef INCLUDE_SENSORS_H
#define INCLUDE_SENSORS_H

#include <avr/io.h>
#include <stdio.h>
#include "cmod.h"

uint8_t bumpLeft, bumpRight, irSensor;
uint16_t wall;
int red, green, forceField;

void findWall(void);
uint16_t getWallDistance(void);
void getBumps(void);
int transmit(char* string);
void getDockSenses(void);

#endif
