#include "timer.h"    // Declaration made available here
#include "sensors.h"


// Timer variables defined here
volatile uint16_t delayTimerCount = 0;            // Definition checked against declaration
volatile uint8_t  delayTimerRunning = 0;          // Definition checked against declaration

volatile uint8_t senseCount = 1;
volatile uint8_t canSense = 0;
volatile uint8_t canPrint = 0;


// Timer 0 interrupt 
// SIGNAL(SIG_OUTPUT_COMPARE0A)
ISR(TIMER0_COMPA_vect) {
    if(delayTimerCount) {
        delayTimerCount--;
    } else {
        delayTimerRunning = 0;
    }
    
    if (senseCount != 0) {
        senseCount--;
    } else {
        canSense = 1;
    }
}

//SIGNAL(SIG_OUTPUT_COMPARE1A)
ISR(TIMER1_COMPA_vect) {
    canPrint = 1;
}

void setupTimer(void) {
  // ---------------------------------------------------
  //  Set up timer 0 to generate interrupts @ 1000Hz -- 1ms
  // ---------------------------------------------------
  TCCR0A = _BV(WGM01);              // Mode = CTC
  TCCR0B = (_BV(CS00) | _BV(CS02)); // CS0 | CS2 = CLK/1024
  OCR0A  = 17;                      // 18432000/(1024*1000) = 18
  TIMSK0 = _BV(OCIE0A);             // Enable output compare A interrupt


  // ---------------------------------------------------
  //  Set up timer 1 to generate interrupts @ 1Hz -- 1 second
  // ---------------------------------------------------
  TCCR1A = 0x00;
  TCCR1B = (_BV(WGM12) | _BV(CS10) | _BV(CS12));  // WGM12 | CS10 | CS12 = CTC Mode, CLK/1024
  OCR1A = 17999;
  //OCR1A  = 35999;                                 // 18432000/(1024*.5) = 36,000
  //OCR1B  = 17999;                                 // 18432000/(1024*1)  = 18,000
  TIMSK1 = _BV(OCIE1A); // | _BV(OCIE1B);             // Enable output compare A and B interrupt

}

// Delay for the specified time in ms without updating sensor values
void delayMs(uint16_t time_ms)
{
  cli();
  delayTimerRunning = 1;
  delayTimerCount = time_ms;
  sei();

  while(delayTimerRunning) {
    asm("nop");
  }
}
