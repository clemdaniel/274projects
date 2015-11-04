#include "cmod.h"
#include "timer.h"
#include "oi.h"
#include "sensors.h"

//read sensors from packet 6 of the 
// irobot
void readSensors(void) {
    int i;
    //flush buffer (not neccessary?)
    flushRx();
    //query sensors
    byteTx(142);
    byteTx(6);
    //read sensor data into array
    for (i=0; i<52; i++) {
        sensorList[i] = byteRx();
    }
    //reset sense counter back to 75ms
    senseCount = 75;
    //reset sense flag to not sense
    canSense = 0;
}

//print characters containing in char array 
//to serial - returns length of string
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
