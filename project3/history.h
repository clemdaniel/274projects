//#include "oi.h"
#ifndef INCLUDE_HISTORY_H
#define INCLUDE_HISTORY_H

#include <avr/io.h>
#include <stdio.h>

#define MAX_SIZE 10 //25 -- Window size

void addElement(uint16_t currentError);
int sum(void);
int slope(int currentTime);
void clearHistory(void);

//private variables
uint16_t historyArray[MAX_SIZE];
extern volatile int currentSize;
int currentElement;

#endif
