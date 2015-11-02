#include "sensors.h"

void readSensors(void) {

	readWallSignal();
	readCliffSensors();
	readGroupPacket3();
} 

void readWallSignal(void) {
		
		uint16_t wall;
		uint8_t hi, lo;
		byteTx(142);
		byteTx(WallPID);
		hi = byteRx();
		lo = byteRx();
		wall = twoUBytesIntoInt(hi, lo);
		char wallArray[11];
		sprintf(wallArray, "Wall: %i", (int)wall);
		transmit(wallArray);

}

void readCliffSensors(void) {
	
		uint16_t cliffLeft, cliffFrontLeft, cliffFrontRight, cliffRight;
		uint8_t hi, lo;
		byteTx(142);
		byteTx(CliffLeftPID);
		hi = byteRx();
		lo = byteRx();
		cliffLeft = twoUBytesIntoInt(hi, lo);
		char cliffLeftArray[17];
		sprintf(cliffLeftArray, "Cliff Left: %i", (int)cliffLeft);
		transmit(cliffLeftArray);

		byteTx(142);
		byteTx(CliffFrontLeftPID);
		hi = byteRx();
		lo = byteRx();
		cliffFrontLeft = twoUBytesIntoInt(hi, lo);
		char cliffFrontLeftArray[23];
		sprintf(cliffFrontLeftArray, "Cliff Front Left: %i", (int)cliffFrontLeft);
		transmit(cliffFrontLeftArray);

		byteTx(142);
		byteTx(CliffFrontRightPID);
		hi = byteRx();
		lo = byteRx();
		cliffFrontRight = twoUBytesIntoInt(hi, lo);
		char cliffFrontRightArray[24];
		sprintf(cliffFrontRightArray, "Cliff Front Right: %i", (int)cliffFrontRight);
		transmit(cliffFrontRightArray);

		byteTx(142);
		byteTx(CliffRightPID);
		hi = byteRx();
		lo = byteRx();
		cliffRight = twoUBytesIntoInt(hi, lo);
		char cliffRightArray[18];
		sprintf(cliffRightArray, "Cliff Right: %i", (int)cliffRight);
		transmit(cliffRightArray);

}

void readGroupPacket3(void) {
	//read group packet 3
	uint8_t i;
	uint8_t group3Data[10];  /* array for group packet ID 3 data */
	while(UCSR0A & 0x80) /* clear the receive buffer */
	  i = UDR0;
	byteTx(142);  /* sensor opcode */
	byteTx(3);   /* send request for packet 3 */
	for(i = 0; i < 10; i++) //10 is size of group
	{
	  group3Data[i] = byteRx();  /* read each sensor byte */
	}

	//charging state - max length == 17
	char chargingState[17];
	sprintf(chargingState, "Charging State: %i", (int)group3Data[0]);
	transmit(chargingState);

	//voltage - max length == 17
	uint16_t voltage = twoUBytesIntoInt(group3Data[1], group3Data[2]);
	char voltageArray[15];
	sprintf(voltageArray, "Voltage: %i", (int)voltage);
	transmit(voltageArray);

	//signed int
	int16_t current = twoBytesIntoInt(group3Data[3], group3Data[4]);
	char currentArray[16];
	sprintf(currentArray, "Current: %i", (int)current);
	transmit(currentArray);

	//signed int
	int16_t battTemp = group3Data[5];
	char battTempArray[26];
	sprintf(battTempArray, "Battery Temperature: %i", (int)battTemp);
	transmit(battTempArray);

	uint16_t batteryCharge = twoUBytesIntoInt(group3Data[6], group3Data[7]);
	char batteryChargeArray[22];
	sprintf(batteryChargeArray, "Battery Charge: %i", (int)batteryCharge);
	transmit(batteryChargeArray);

	uint16_t batteryCapacity = twoUBytesIntoInt(group3Data[8], group3Data[9]);
	char batteryCapacityArray[24];
	sprintf(batteryCapacityArray, "Battery Capacity: %i", (int)batteryCapacity);
	transmit(batteryCapacityArray);
}

int transmit(char* string) {
    int i;
    int length = strlen(string);
    
    for (i=0; i<length; i++) {
        byteTx(string[i]);
    }

    return length;
}

uint16_t twoUBytesIntoInt(uint8_t hi, uint8_t lo) {
	uint16_t total = (hi << 8);
	total = total | lo;
	return total; 

}

int16_t twoBytesIntoInt(uint8_t hi, uint8_t lo) {
	uint16_t total = (hi << 8);
	total = total | lo;
	return total; 
}