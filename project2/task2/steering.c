#include "timer.h"
#include "cmod.h"
#include "oi.h"
#include "steering.h"

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
  
  //skeleton left here for future use when driving backward may
  //be necessary
	//if (rate > 0) {
		hi |= rate >> 8;
		lo |= rate; 
	//} else if (rate < 0) {
		//use two compliment
		//not currently necessary
	//}

	byteTx(CmdDriveWheels);
	byteTx(hi);
	byteTx(lo);
	byteTx(hi);
	byteTx(lo);
}

/** Stop the robot	*/
void stop(void) {
	drive(0);
}

/** Make the robot drive in a pentagon shape
 *		direction only -1 or 1
 *			1 indicates counter-clockwise
 * 	  	-1 indicates clockwise
 */
void pentagon(int direction) {
	int i;
	for (i=0; i<5; i++) {
				//drive at 100mm/s        
				drive(100);
        //drive for 8000ms = 8s, 8s * 100 mm/s = 800 mm = 80cm
				delayMs(8000); 
        stop();
				//turn at angle 3*pi/5 radians
				//(don't turn after the last leg)
        if (i != 4) turn((int)(direction*3*PI/5) * 1000);
    } 
}
 
