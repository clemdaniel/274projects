#include "cmod.h"
#include "timer.h"
#include "oi.h"
#include "history.h"

volatile int currentSize = 0;

void addElement(uint16_t currentError) {
	if (currentSize == 100) {
		currentSize = 0;
	}
	historyArray[currentSize] = currentError;
	currentSize++;
}

int sum(void) {
	int sum = 0;
	for (int i = 0; i <= currentSize; i++) {
		sum = sum + historyArray[i];
	}
	return sum;
}

int slope(int currentTime) {
	uint16_t currentElement = historyArray[currentSize];
	uint16_t previousElement = historyArray[currentSize - 1];
	int difference = currentElement - previousElement;
	int final = difference / currentTime;
	return final;
}