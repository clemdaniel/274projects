#include "cmod.h"
#include "timer.h"
#include "oi.h"
#include "sensors.h"

//drive straight until you hit something
void findWall(void) {
	drive(100);
	for (;;) {
		delayMs(100);
		getBumps();
		if (bumpLeft || bumpRight) {
			stop();			
			break; //escape for loop
		}
	}
}

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

//determines whether bump sensors are active
void getBumps(void) {
	uint8_t bumps;
		byteTx(CmdSensors);
	byteTx(BumpAndWheeldropPID);
	bumps = byteRx(); 
	bumpLeft = bumps & (1 << 1);
	bumpRight = bumps & (1 << 0);
}

//print characters containing in char array 
//to serial - returns length of string
//	-useful for debugging
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

void getDockSenses(void) {
	byteTx(CmdSensors);
	byteTx(IRsensorPacket); //packet for IR control
	irSensor = byteRx();
	red = 0;
	green = 0;
	forceField = 0;
	if (irSensor == RED_BUOY) {
		red = 1;
	} else if (irSensor == GREEN_BUOY) {
		green = 1;
	} else if (irSensor == FORCE_FIELD) {
		forceField = 1;
	} else if (irSensor == R_AND_G) {
		red = 1;
		green = 1;
	} else if (irSensor == R_AND_F) {
		red = 1;
		forceField = 1;
	} else if (irSensor == G_AND_F) {
		green = 1;
		forceField = 1;
	} else if (irSensor == ALL_THREE) {
		red = 1;
		green = 1;
		forceField = 1;
	}
}

int isDocked(void) {
	byteTx(CmdSensors);
	byteTx(DOCK);
	uint8_t chargingSources = byteRx();
	if (chargingSources == 2) {
		docked = 1;
	} else {
		docked = 0;
	}
}


