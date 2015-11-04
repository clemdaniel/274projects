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

    uint8_t wheelsAndBump = (uint8_t)(sensorList[SenBumpDrop]);
    wheelLeft = (wheelsAndBump & 0x08) >> 3;
    wheelRight = (wheelsAndBump & 0x04) >> 2;
    bumpLeft = (wheelsAndBump & 0x02) >> 1;
    bumpRight = (wheelsAndBump & 0x01);
    cliffL = (uint16_t)((sensorList[SenCliffLSig1] << 8) | (sensorList[SenCliffLSig0]));
    cliffFL = (uint16_t)((sensorList[SenCliffFLSig1] << 8) | (sensorList[SenCliffFLSig0]));
    cliffFR = (uint16_t)((sensorList[SenCliffFRSig1] << 8) | (sensorList[SenCliffFRSig0]));
    cliffR = (uint16_t)((sensorList[SenCliffRSig1] << 8) | (sensorList[SenCliffRSig0]));
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
