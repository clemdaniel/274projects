/**
 * Editted by: Conor Campbell, Daniel Clements, Cory Novotny
 * Main program file for Task 1
 *
 * CSCE 274 Task 1
 * 
 * This program periodically toggles the LEDs on the command module of the iRobot create
 * and while doing this senses for bumps on the sensor and lights the LEDs according to
 * that.
 */
#include "timer.h"
#include "cmod.h"
#include "iroblib.h"
#include "oi.h"
#include "lights.h"
#include <stdlib.h>
#include <stdbool.h>

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
  //Doesn't need to stop for task 1 since it doesn't move.

  // Play the reset song and wait while it plays.
  byteTx(CmdPlay);
  byteTx(RESET_SONG);
  delayMs(750);

  // Turn the power button on to something. I like red, but here is green.
  // CSCE 274 students: The following should (will) be a function that you write.
  changePowerLightRed(); //power light now red

  // Initialize global variables
  uint8_t bumpbyte, bumpLeft, bumpRight;
  int rightLEDonInt = 0;
  int leftLEDonInt = 1;
  
  //call initial functions
  //setup LEDs
  setupRightLED();
  setupLeftLED();
  leftLEDon(); //start with left LED on

  // Infinite operation loop
  for(;;) {
    while (!bumpRight && !bumpLeft) { //no bumps
      //no bumps are rightLED on
      if (rightLEDonInt == 1 && leftLEDonInt == 0 && !bumpRight && !bumpLeft) {
        rightLEDoff();
        rightLEDonInt = 0;
        leftLEDon();
        leftLEDonInt = 1;
      } //no bumps and left LED on
      else if (rightLEDonInt == 0 && leftLEDonInt == 1 && !bumpRight && !bumpLeft) {
        rightLEDon();
        rightLEDonInt = 1;
        leftLEDoff();
        leftLEDonInt = 0;
      } //no bumps and LEDs off
      else if (rightLEDonInt == 0 && leftLEDonInt == 0 && !bumpRight && !bumpLeft) {
        rightLEDon();
        rightLEDonInt = 1;
      }//no bumps and both LEDs on 
      else if (rightLEDonInt == 1 && leftLEDonInt == 1 && !bumpRight && !bumpLeft) {
        leftLEDon();
        leftLEDonInt = 1;
      }

      delayMs(100); //delay for tenth of a second
      //update bump sensors
      byteTx(CmdSensors);
      byteTx(SenOverC);
      bumpbyte = byteRx();
      bumpRight = bumpbyte & (1 << 0);
      bumpLeft = bumpbyte & (1 << 1);
    }

    //update bump sensors again
    byteTx(CmdSensors);
    byteTx(SenOverC);
    bumpbyte = byteRx();
    bumpRight = bumpbyte & (1 << 0);
    bumpLeft = bumpbyte & (1 << 1);
    //turn on LEDs according to bump sensors
    if (bumpRight) {
      rightLEDon();
      rightLEDonInt = 1;
    } else {
      rightLEDoff();
      rightLEDonInt = 0;
    }
    if (bumpLeft) {
      leftLEDon();
      leftLEDonInt = 1;
    } else {
      leftLEDoff();
      leftLEDonInt = 0;
    }

    delayMs(10);
    if(UserButtonPressed) {
      powerOffRobot();
      exit(1);
    }
  }
}

