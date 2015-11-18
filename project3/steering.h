#include "oi.h"
#ifndef INCLUDE_STEERING_H
#define INCLUDE_STEERING_H

#include <avr/io.h>

/*
 *	Constants for turning velocities to achieve an angular
 *  velocity of one.  We set the left and right velocities
 *  equal to 165 mm/s to achieve this condition.
 *  The theoretical value was equal to 132 mm/s, but we 
 *  found 165 mm/s more accurate experimentally.
 */
#define vHiPos		0x00
#define vLoPos		0xa5
#define vHiNeg 		0xff
#define vLoNeg		0x5b

#define PI				3.1415926

void turn(int theta);

void drive(int rate);

void stop(void);

void pentagon(int direction);

#endif
