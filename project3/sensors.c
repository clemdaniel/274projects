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

    return hi << 8 | lo;
}

//determines whether bumps sensor is active
// returns array of binary results for
// left followed by right e.g. [0,0]
// 1 - bump : 0 - no bump
uint16_t* getBumps(void) {
    uint16_t bumps;
    uint16_t ret[2];
    byteTx(CmdSensors);
    byteTx(BumpAndWheeldropPID);
    bumps = byteRx(); 
    
    ret[0] = bumps & (1 << 1);
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

