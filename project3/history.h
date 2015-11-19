#include "oi.h"
#ifndef INCLUDE_HISTORY_H
#define INCLUDE_HISTORY_H

#include <avr/io.h>
#include <stdio.h>

void addElement(uint16_t currentError);
int sum(void);
int slope(time);

uint16_t history[100];
int size = 0;


#endif