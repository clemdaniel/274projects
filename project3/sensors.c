#include "cmod.h"
#include "timer.h"
#include "oi.h"
#include "sensors.h"

//determines the wall sensor strength
// value from 0-4095,
// 4095 => as close to wall as possible 
uint16_t getWallDistance(void) {
    uint8_t hi, lo;
    byteTx(CmdSensors);
    byteTx(WallPID);
    hi = byteRx();
    lo = byteRx();

    return (hi << 8) | lo;
}

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
    //wheel drop and bump sensors read
    uint8_t wheelsAndBump = (uint8_t)(sensorList[SenBumpDrop]);
    //seperate sensor values accordingly
    bumpLeft = (wheelsAndBump & 0x02) >> 1;
    bumpRight = (wheelsAndBump & 0x01);

    wall = (uint16_t)((sensorList[SenWallSig1]) << 8) | (sensorList[SenWallSig0]);

    //reset sense counter back to 75ms
    senseCount = 75;
    //reset sense flag to not sense
    canSense = 0;
}

//determines whether bumps sensor is active
// returns array of binary results for
// left followed by right e.g. [0,0]
// 1 - bump : 0 - no bump
uint8_t* getBumps(void) {
    uint8_t bumps;
    uint8_t ret[2];
    byteTx(CmdSensors);
    byteTx(BumpAndWheeldropPID);
    bumps = byteRx(); 
    
    ret[0] = (bumps & (1 << 1)) >> 1;
    ret[1] = bumps & (1 << 0);

    return ret;
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

