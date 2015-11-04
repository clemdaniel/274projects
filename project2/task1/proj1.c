/**
 * CSCE 274 Project 1 Task 2
 *		This program causes the robot to drive in a clockwise
 *		pentagon when the play button is pressed and a counter-
 *		clockwise pentagon when the advance button is pressed.
 *
 *	Edited by: Daniel Clements, Conor Campbell, Cory Novotny
 */

#include "timer.h"
#include "cmod.h"
#include "iroblib.h"
#include "oi.h"
#include "steering.h"
#include "lights.h"
#include <stdlib.h>
#include "sensors.h"

// Declare Global variables 
int main() {
  // Set up Create and module
  initializeCommandModule();
    
  powerOnRobot();
    // Is the Robot on
  byteTx(CmdStart);
    // Start the create
  baud(Baud57600);
    // Set the baud rate for the Create and Command Module
  defineSongs();
    // Define some songs so that we know the robot is on.
  byteTx(CmdControl);
    // Deprecated form of safe mode. I use it because it will
    // turn of all LEDs, so it's essentially a reset.
  byteTx(CmdFull);
    // We are operating in FULL mode.

  // CSCE 274 students: I would make sure the robot stops. 
  //                    As a precaution for the robot and your grade.
  stop();

  // Play the reset song and wait while it plays.
  byteTx(CmdPlay);
  byteTx(RESET_SONG);
  delayMs(750);

  //Turn power button on
  changePowerLightRed();

  //LED1On;


  // Infinite operation loop
  for(;;) {
    if(UserButtonPressed) {
      powerOffRobot();
      exit(1);
    }
    
    if (canSense) {
        readSensors();
    }
    if (canPrint) {
        //buffer to store strings
        char buffer[50];
        //begin printing the read sensors
        sprintf(buffer, "Wall Signal: %u\n",
            (uint16_t)((sensorList[SenWallSig1] << 8) | (sensorList[SenWallSig0])));
        transmit(buffer);

        sprintf(buffer, "Cliff Left Signal: %u\n",
            (uint16_t)((sensorList[SenCliffLSig1] << 8) | (sensorList[SenCliffLSig0])));
        transmit(buffer);

        sprintf(buffer, "Cliff Front Left Signal: %u\n",
            (uint16_t)((sensorList[SenCliffFLSig1] << 8) | (sensorList[SenCliffFLSig0])));
        transmit(buffer);

        sprintf(buffer, "Cliff Front Right Signal: %u\n",
            (uint16_t)((sensorList[SenCliffFRSig1] << 8) | (sensorList[SenCliffFRSig0])));
        transmit(buffer);

        sprintf(buffer, "Cliff Right Signal: %u\n",
            (uint16_t)((sensorList[SenCliffRSig1] << 8) | (sensorList[SenCliffRSig0])));
        transmit(buffer);

        sprintf(buffer, "Charging State: %u\n",
            (uint8_t)(sensorList[SenChargeState]));
        transmit(buffer);

        sprintf(buffer, "Voltage: %u\n",
            (uint16_t)((sensorList[SenVolt1] << 8) | (sensorList[SenVolt0])));
        transmit(buffer);

        sprintf(buffer, "Current: %i\n",
            (int16_t)((sensorList[SenCurr1] << 8) | (sensorList[SenCurr0])));
        transmit(buffer);

        sprintf(buffer, "Battery Temperature: %i\n",
            (int8_t)(sensorList[SenTemp]));
        transmit(buffer);

        sprintf(buffer, "Battery Charge: %u\n",
            (uint16_t)((sensorList[SenCharge1] << 8) | (sensorList[SenCharge0])));
        transmit(buffer);

        sprintf(buffer, "Battery Capacity: %u\n",
            (uint16_t)((sensorList[SenCap1] << 8) | (sensorList[SenCap0])));
        transmit(buffer);

        uint8_t wheelsAndBump = (uint8_t)(sensorList[SenBumpDrop]);
        uint8_t wheelLeft = (wheelsAndBump & 0x08) >> 3;
        uint8_t wheelRight = (wheelsAndBump & 0x04) >> 2;
        uint8_t bumpLeft = (wheelsAndBump & 0x02) >> 1;
        uint8_t bumpRight = (wheelsAndBump & 0x01);
        
        sprintf(buffer, "Wheel Left Drop: %u\n",
            wheelLeft);
        transmit(buffer);

        sprintf(buffer, "Wheel Right Drop: %u\n",
            wheelRight);
        transmit(buffer);

        sprintf(buffer, "Bump Left Drop: %u\n",
            bumpLeft);
        transmit(buffer);

        sprintf(buffer, "Bump Right Drop: %u\n\n",
            bumpRight);
        transmit(buffer);
        //reset print flag
        canPrint = 0;
    }
  }
}

