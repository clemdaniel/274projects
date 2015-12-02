/**
 * CSCE 274 Project 3
 *		This program implements a PID controller with the objective  
 * following along a wall or other obstacle while maintaining a set distance
 * and correcting for any errors.
 *
 *	Edited by: Daniel Clements, Conor Campbell, Cory Novotny
 */

 #include "timer.h"
 #include "cmod.h"
 #include "iroblib.h"
 #include "oi.h"
 #include "steering.h"
 #include "lights.h"
 #include "sensors.h"
 #include "history.h"
 #include <stdlib.h>

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

  uint16_t wall;
  int currentError; 
  uint8_t kp_gain = 30; //30; //70; 
  uint8_t kd_gain = 5; //5; //30; 
  uint8_t ki_gain = 1; //1;
  int ki_error, kd_error, uk;
  int rightVel = 0;
  int leftVel = 0;
  int defaultVel = 100;
  int maxVel = 200;
	int wallZeros = 0;
	
	//go straight until you hit something
	findWall();	

  // Infinite operation loop
  for(;;) {
    if(UserButtonPressed) {
      powerOffRobot();
      exit(1);
    }
    
    //check bump sensor
    getBumps();		
    
		//if bump occurs -- align back to wall
    alignToWall();

    //if time to calculate PID output
    if (canPID) {
      //update sensor 
      getDockSenses();
      //check wall distance
      wall = getWallDistance();
				
		  //PID Controller 
		  //calculate error
		  currentError = wall - SET_POINT;

		  //add error to history
		  addElement(currentError);

		  //calculate integral and derivative of error
		  ki_error = sum() * CHANGE_TIME;
		  kd_error = slope(CHANGE_TIME);

		  //calculate uk i.e. PID output
		  uk = ((kp_gain * (currentError >> 2)) + (ki_gain * (ki_error >> 6)) + 
		    (kd_gain * (kd_error >> 2))) >> 2;
		  //set wheel velocities based on uk
		  // (Make sure to check velocities for validity before setting) 
		  rightVel = defaultVel + uk;
		  leftVel = defaultVel - uk;

      //check for negative or max velocities
		  if (rightVel < 0) {
		    rightVel = 0;
		  } else if (rightVel > maxVel) {
		    rightVel = maxVel;
		  } 
		  if (leftVel < 0) {
		    leftVel = 0;
		  } else if (leftVel > maxVel) {
		    leftVel = maxVel;
		  } 

		  driveLR(leftVel, rightVel);

      //reset PID timer
      PIDCount = CHANGE_TIME;
      canPID = 0;
    }

        
  }
  return 0;
}

