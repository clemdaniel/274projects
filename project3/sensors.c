#include "cmod.h"
#include "timer.h"
#include "oi.h"
#include "sensors.h"

uint16_t getWallDistance(void) {

}

uint16_t getBumps(void) {

}

//print characters containing in char array 
//to serial - returns length of string
//  -useful for debugging
int transmit(char* string) {
    int i;
    int length = strlen(string);
    //point to serial monitor
    setSerialDestination(SERIAL_USB);
    //send data to USB
    for (i=0; i<length; i++) {
        byteTx(string[i]);
    }
    //point back to create
    setSerialDestination(SERIAL_CREATE);
    return length;
}

