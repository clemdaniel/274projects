#include "timer.h"    // Declaration made available here
#include "sensors.h"


// Timer variables defined here
volatile uint16_t delayTimerCount = 0;            // Definition checked against declaration
volatile uint8_t  delayTimerRunning = 0;          // Definition checked against declaration
volatile uint8_t senseCount = 1;
volatile uint8_t canSense = 0;
volatile uint8_t canPrint = 0;
//PID controller
volatile uint8_t PIDCount = 1;
volatile uint8_t canPID = 0;
//timer
volatile uint8_t startTimer = 0;
volatile uint16_t timerVal = 0;

ISR(USART_RX_vect) {  //SIGNAL(SIG_USART_RECV)
  // Serial receive interrupt to store sensor values
 
  // CSCE 274 students, I have only ever used this method
  // when retrieving/storing a large amount of sensor data.
  // You DO NOT need it for this assignment. If i feel it
  // becomes relevant, I will show you how/when to use it.
}

// Timer 0 interrupt 
// SIGNAL(SIG_OUTPUT_COMPARE0A)
ISR(TIMER0_COMPA_vect) {
    if(delayTimerCount) {
        delayTimerCount--;
    } else {
        delayTimerRunning = 0;
    }
    //decrement sensor counter
    if (senseCount != 0) {
        senseCount--;
    } else {
        //go sense values
        canSense = 1;
    }
    //decrement PID
    if (PIDCount != 0) {
        PIDCount--;
    } else {
        //go calc PID
        canPID = 1;
    }

    if (startTimer == 1) {
      timerVal++;
    }
}

//SIGNAL(SIG_OUTPUT_COMPARE1A)
ISR(TIMER1_COMPA_vect) {
    //go print
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
