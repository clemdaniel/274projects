#include "timer.h"
#include "cmod.h"
#include "oi.h"
#include "steering.h"
#include "lights.h"
#include "iroblib.h"

/**	Turn the robot angle theta
 *		theta in radians (theta * 1000)
 *		positive angles indicate counter-clockwise turns
 *		negative angles indicate clockwise turns
 */
void turn(int theta) {
	uint8_t rHi;
	uint8_t rLo;
	uint8_t lHi;
	uint8_t lLo;

	if (theta > 0) {
		rHi = vHiPos;
		rLo = vLoPos;
		lHi = vHiNeg;
		lLo = vLoNeg;
	} else {
		rHi = vHiNeg;
		rLo = vLoNeg;
		lHi = vHiPos;
		lLo = vLoPos;
		theta *= -1;
	}

	byteTx(CmdDriveWheels);
	byteTx(rHi);
	byteTx(rLo);
	byteTx(lHi);
	byteTx(lLo);

	delayMs(theta);
	stop();
}

/**	Drive the robot at rate 'rate' until stopped
 *		rate in mm/s
 */
void drive(int rate) {
	//rate to hi/lo
	uint8_t hi = 0x00;
	uint8_t lo = 0x00;
  
	hi |= rate >> 8;
	lo |= rate; 

	byteTx(CmdDriveWheels);
	byteTx(hi);
	byteTx(lo);
	byteTx(hi);
	byteTx(lo);
}

/** Specify velocities of wheels separately
 *    rate in mm/s 
 */
void driveLR(int rateLeft, int rateRight) {
	//rates to hi/lo
	uint8_t rHi = 0x00, rLo = 0x00, lHi = 0x00, lLo = 0x00;
  
	lHi |= rateLeft >> 8;
	lLo |= rateLeft; 

	rHi |= rateRight >> 8;
	rLo |= rateRight; 

	byteTx(CmdDriveWheels);
	byteTx(rHi);
	byteTx(rLo);
	byteTx(lHi);
	byteTx(lLo);
}

/** Stop the robot	*/
void stop(void) {
	drive(0);
}

//check bump sensors and act accordingly -- not used currently
void alignToWall() {
	if (bumpLeft && bumpRight) { //both bumps -- clear history after bump
		turn(TURN_60_DEGREES);
	} else if (bumpLeft) {
		turn(TURN_90_DEGREES);
	} else if (bumpRight) {
		turn(TURN_30_DEGREES);
	}
	clearHistory();
} 

/*
This function will control and call other functions to succesfully
	dock the irobot.	
*/
void dock() {
	//follow boundary
	int tempRed = red;
	if (tempRed) {
		followRed();
	} else {
		followGreen();
	}
	followOverlap();
	findDock(tempRed);	
	return;
}

/*
This function will follow the red buoy boundry until 
	it hits the overlap.
*/
void followRed(void) {
	do {
		getBumps();
		if (bumpLeft || bumpRight) {
			turn(-TURN_90_DEGREES);
			drive(100);
			delayMs(1500);
		}
		//scan left
		driveLR(-50, 50);
		while (red) {
			getDockSenses();
			delayMs(50);
		}
		stop(); //stop when red is lost
		//forward 5cm
		drive(100);
		delayMs(500);
		if (green && red) {
			stop();
			return;
		}
		getBumps();
		if (bumpLeft || bumpRight) {
			turn(-TURN_90_DEGREES);
			drive(100);
			delayMs(1500);
		}
		//scan right
		driveLR(50, -50);
		while (!red) {
			getDockSenses();
			delayMs(50);
		}
		stop();
		//forward 5cm
		drive(100);
		delayMs(500);
		stop();
	} while (!(green && red)); 
}

/*
This function will follow the green buoy boundry until 
	it hits the overlap.
*/
void followGreen(void) {
	do {
		getBumps();
		if (bumpLeft || bumpRight) {
			turn(TURN_90_DEGREES);
			drive(100);
			delayMs(1500);
		}
		//scan right
		driveLR(50, -50);
		while (green) {
			getDockSenses();
			delayMs(50);
		}
		stop(); //stop when green is lost
		//forward 5cm
		drive(100);
		delayMs(500);
		if (green && red) {
			stop();
			return;
		}
		getBumps();
		if (bumpLeft || bumpRight) {
			turn(TURN_90_DEGREES);
			drive(100);
			delayMs(1500);
		}
		//scan left
		driveLR(-50, 50);
		while (!green) {
			getDockSenses();
			delayMs(50);
		}
		stop();
		//forward 5cm
		drive(100);
		delayMs(500);
		stop();
	} while (!(green && red)); 
}

/*
This function will follow the overlap of red and green until
	both bumps are detected.
*/
void followOverlap(void) {
	//do until bump
	do {
		//if sensing both, drive
		if (green && red) {
			rightLEDon();
			leftLEDon();
			drive(35);
		} else if (!green && red) { //only red, turn left
			leftLEDoff();
			rightLEDon();
			driveLR(-25, 25);
		} else if (!red && green) { //only green, turn right
			leftLEDon();
			rightLEDoff();
			driveLR(25, -25);
		} else { //no signal, drive (means close to dock)
			rightLEDoff();
			leftLEDoff();
			drive(35);
		}
		getBumps();
		getDockSenses();
		delayMs(50);
	} while (!bumpLeft || !bumpRight);
	stop();
}

/*
This function to keep turning left or right until a 
	charge state is detected.
		The parameter passed to this function decides if it will
		turn left or right first.
*/
void findDock(uint8_t isRed) {
	//actively looking for dock
	lookForDock = 1;
	delayMs(1500);
	if (docked == 1) {
		BLINGBLING();
		changePowerLightGreen();
		stop();
		exit(0);
		return;
	}
	//drive backwords and check for dock
	drive(-100);
	delayMs(100);
	stop();
	delayMs(1500);
	if (docked == 1) {
		BLINGBLING();
		changePowerLightGreen();
		stop();
		exit(0);
		return;
	}
	//begin the turning process
	int i,j;
	for (i=0; i<3; i++) {
		int bound;
		if (i == 0) {
			bound = 2500; 
		} else {
			bound = 4500;
		}
		//right if approach from red, left if approach from green
	 	for (j=0; j<bound; j+=500) {
		 	if (isRed) {
				driveLR(-25, 25);
			} else {
				driveLR(25, -25);
			}
			delayMs(750); //500
			stop();
			delayMs(1500);
			byteTx(CmdSensors);
			byteTx(21);
			if (docked == 1) {
				BLINGBLING();
				changePowerLightGreen();
				stop();
				exit(0);
				return;
			}
		}
		//left if approach from red, right if approach from green
		for (j=0; j<bound; j+=500) {
		 	if (isRed) {
				driveLR(25, -25);
			} else {
				driveLR(-25, 25);
			}
			delayMs(750); //500
			stop();
			delayMs(1500);
			byteTx(CmdSensors);
			byteTx(21);
			if (docked == 1) {
				BLINGBLING();
				changePowerLightGreen();
				stop();
				exit(0);
				return;
			}
		}
	}
	//if still no dock, turn around and reset
	//turn(TURN_180_DEGREES);
	drive(-100);
	delayMs(2000);
	stop();
	//turn(TURN_180_DEGREES);
	//stop();
	getBumps();
	getDockSenses();
	//dock();
	//return;
}

//play hotline bling
void BLINGBLING(void) {
	byteTx(CmdPlay);
	byteTx(HOTLINE_BLING);
	delayMs(750);
}
