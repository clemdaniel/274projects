#include "lights.h"

/*
 * This function sets up the right LED.
 */
void setupRightLED(void) {
	DDRD |= (1 << 5);
}
/*
 * This function turns on the right LED.
 */
void rightLEDon(void) {
	PORTD &= ~(1 << 5);
} 
/*
 * This function turns off the right LED.
 */
void rightLEDoff(void) {
	PORTD |= (1 << 5);
}
/*
 * This function sets up the left LED.
 */
void setupLeftLED(void) {
	DDRD |= (1 << 6);
}
/*
 * This function turns on the left LED. 
 */
void leftLEDon(void) {
	PORTD &= ~(1 << 6);
} 
/*
 * This function turns off the left LED.
 */
void leftLEDoff(void) {
	PORTD |= (1 << 6);
}
/*
 * This function changes the power light to red. 
 */
void changePowerLightRed(void) {
	byteTx(CmdLeds);
  byteTx(0x00);
  byteTx(255);
  byteTx(255);
}