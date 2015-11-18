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
  //Turn power light on
  changePowerLightRed();

  // Infinite operation loop
  for(;;) {
    if(UserButtonPressed) {
      powerOffRobot();
      exit(1);
    }
    
    //check bump sensor -- sensors.c: getBumps

    //if bump occurs
    //realign robot to wall -- steering.c: alignToWall

    //TODO implement timing for when to calculate PID output
    //if (time to calculate PID output)
        //check wall distance -- sensors.c: getWallDistance
    
        //PID Controller 
        //calculate error
        //add error to history

        //calculate integral and derivative of error

        //calculate uk i.e. PID output

        //set wheel velocities based on uk --steering.c: driveLR
        // (Make sure to check velocities for validity before setting)  
   
        //reset PID timer
  }
}

