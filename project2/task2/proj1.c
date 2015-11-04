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
    
    byteTx(142);
    byteTx(17); //packet for IR
    uint8_t irSensor = byteRx();
    if (irSensor != NO_SIGNAL) {
      if (irSensor == 0x82) {
        if (checkSurroudings(CHECK_FORWARD) == SAFE_DIRECTION) {
          drive(100);
        }
      } else if (irSensor == LEFT_SIGNAL) {
        if (checkSurroudings(CHECK_TURN) == SAFE_DIRECTION) {
          turn(523);
        }
      } else if (irSensor == RIGHT_SIGNAL) {
        if (checkSurroudings(CHECK_TURN) == SAFE_DIRECTION) {
          turn(-523);
        }
      }
    } else {
      stop();
    }
  }
}

