#ifndef INCLUDE_IROBLIB_H
#define INCLUDE_IROBLIB_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Constants
#define RESET_SONG 0
#define START_SONG 1
#define HOTLINE_BLING 2

void defineSongs(void);
  // Songs
  // Indicator that the robot is Powered on and has reset.
void powerOnRobot(void);
void powerOffRobot(void);
  // Power the create On/Off.
#endif
