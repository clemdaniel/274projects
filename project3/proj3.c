/**
 * CSCE 274 Project 3
 *		This program implements a PID controller with the objective  
 * following along a wall or other obstacle while maintaining a set distance.
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
  // Infinite operation loop
  for(;;) {
    if(UserButtonPressed) {
      powerOffRobot();
      exit(1);
    }
    
    if (canSense) {
        readSensors();
    }
    
    byteTx(CmdSensors);
    byteTx(IRsensorPacket); //packet for IR control
    uint8_t irSensor = byteRx();
    //if no signal from remote, do not do anything
    if (irSensor != NO_SIGNAL) {
      //check to see which remote signal
      if (irSensor == DRIVE_SIGNAL) {
        if (checkSurroundings(CHECK_FORWARD) == SAFE_DIRECTION) {
          drive(DRIVE_SPEED);
        } else {
          stop();
		    }
      } else if (irSensor == LEFT_SIGNAL) {
        if (checkSurroundings(CHECK_TURN) == SAFE_DIRECTION) {
          turn(TURN_30_DEGREES);
        } else {
          stop();
		}
      } else if (irSensor == RIGHT_SIGNAL) {
        if (checkSurroundings(CHECK_TURN) == SAFE_DIRECTION) {
          turn(-TURN_30_DEGREES);
        } else {
          stop();
		}
      }
    } else {
      stop();
    }
  }
}

