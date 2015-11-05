
#include "oi.h"
#ifndef INCLUDE_SENSORS_H
#define INCLUDE_SENSORS_H

#include <avr/io.h>
#include <stdio.h>
#include "cmod.h"

uint8_t sensorList[52];
uint8_t wheelLeft, wheelRight, bumpLeft, bumpRight;
uint16_t wall, cliffL, cliffFL, cliffFR, cliffR;

void readSensors(void);
int transmit(char* string);
int checkSurroundings(int movementType);

//defines for clarity in checkSurroundings
#define CHECK_FORWARD     0
#define CHECK_TURN        1
#define SAFE_DIRECTION    0
#define UNSAFE_DIRECTION  1

#endif
