#include "cmod.h"
#include "timer.h"

void addElement(uint16_t currentError) {
	if (size == 100) {
		size = 0;
	}
	history[size] = currentError;
	size++;
}

int sum() {
	int sum = 0;
	for (int i = 0; i <= size; i++) {
		sum = sum + history[i];
	}
	return sum;
}

int slope(int currentTime) {
	uint16_t currentElement = history[size];
	uint16_t previousElement = history[size -1];
	int difference = currentElement - previousElement;
	int final = difference/currentTime;
	return final;
}