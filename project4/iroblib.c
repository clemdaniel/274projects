#include "iroblib.h"
#include "oi.h"
#include "cmod.h"

// Define songs to be played later
void defineSongs(void) {
  // Reset song
  byteTx(CmdSong);
  byteTx(RESET_SONG);
  byteTx(4);
  byteTx(60);
  byteTx(6);
  byteTx(72);
  byteTx(6);
  byteTx(84);
  byteTx(6);
  byteTx(96);
  byteTx(6);

  // Start song
  byteTx(CmdSong);
  byteTx(START_SONG);
  byteTx(6);
  byteTx(69);
  byteTx(18);
  byteTx(72);
  byteTx(12);
  byteTx(74);
  byteTx(12);
  byteTx(72);
  byteTx(12);
  byteTx(69);
  byteTx(12);
  byteTx(77);
  byteTx(24);
  
  // Hotline Bling
  byteTx(CmdSong);
  byteTx(HOTLINE_BLING);
  byteTx(15);
  byteTx(81); // A And
  byteTx(12);
  byteTx(84); // C I
  byteTx(12);
  byteTx(84); // C know
  byteTx(16);
  byteTx(84); // C when
  byteTx(16);
  byteTx(81); // A that
  byteTx(16);
  byteTx(84); // C hot
  byteTx(16);
  byteTx(84); // C line
  byteTx(16);
  byteTx(86); // D bling
  byteTx(32);
  byteTx(79); // G that
  byteTx(16);
  byteTx(81); // A can
  byteTx(12);
  byteTx(79);    // G on-
  byteTx(12);
  byteTx(77);    // F ly
  byteTx(12);
  byteTx(79);    // G mean
  byteTx(16);
  byteTx(79);    // G one
  byteTx(16);
  byteTx(81); // A thing
  byteTx(32);
}

// Ensure that the robot is On.
void powerOnRobot(void) {
  // If Create's power is off, turn it on
  if(!RobotIsOn) {
    while(!RobotIsOn) {
      RobotPwrToggleLow;
      delayMs(500);  // Delay in this state
      RobotPwrToggleHigh;  // Low to high transition to toggle power
      delayMs(100);  // Delay in this state
      RobotPwrToggleLow;
    }
    delayMs(3500);  // Delay for startup
  }

  // Flush the buffer
  while( (UCSR0A & 0x80) && UDR0);
}

// Ensure that the robot is OFF.
void powerOffRobot(void) {
  // If Create's power is on, turn it off
  if(RobotIsOn) {
    while(RobotIsOn) {
      RobotPwrToggleLow;
      delayMs(500);  // Delay in this state
      RobotPwrToggleHigh;  // Low to high transition to toggle power
      delayMs(100);  // Delay in this state
      RobotPwrToggleLow;
    }
  }
}

