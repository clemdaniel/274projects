#include "cmod.h"
#include "timer.h"
#include "oi.h"
#include "sensors.h"

void readSensors(void) {
    int i;
    
    //flushRx();
    
    transmit("1 ");
    
    //query sensors
    byteTx(142);
    byteTx(6);
    
    //flushRx();
    transmit("2 ");
    
    for (i=0; i<52; i++) {
        transmit("fl ");
        sensorList[i] = byteRx();
    }
    
    senseCount = 75;
    canSense = 0;
}

int transmit(char* string) {
    int i;
    int length = strlen(string);
    
    setSerialDestination(SERIAL_USB);
    
    for (i=0; i<length; i++) {
        byteTx(string[i]);
    }
    
    setSerialDestination(SERIAL_CREATE);

    return length;
}
