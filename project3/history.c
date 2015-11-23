#include "cmod.h"
#include "timer.h"
#include "oi.h"
#include "history.h"

volatile int currentSize = 0;
currentElement = 0;

void addElement(uint16_t currentError) {
	if (currentSize != MAX_SIZE) {
		currentSize++;
	}
	if (currentElement == MAX_SIZE) {
		currentElement = 0;
	}
	historyArray[currentElement] = currentError;
	currentElement++;
}

int sum(void) {
	int sum = 0;
	int average = 0;	
	for (int i = 0; i < currentSize; i++) {
		sum = sum + historyArray[i];
	}
	average = (int) (sum / currentSize);
	return average;
}

int slope(int currentTime) {
	uint16_t current = historyArray[currentElement];
	uint16_t previous;
	//account for window going back to beginning
	if (currentElement == 0) {
		previous = historyArray[currentSize - 1];
	}	else {
		previous = historyArray[currentElement - 1];
	}
	int difference = current - previous;
	int final = difference / currentTime;
	return final;
}

void clearHistory(void) {
	currentSize = 0;
	currentElement = 0;
}
