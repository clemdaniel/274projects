#ifndef INCLUDE_TIMER_H
#define INCLUDE_TIMER_H

  #include <avr/io.h>
  #include <avr/interrupt.h>

  // Interrupts.
  ISR(USART_RX_vect);
  ISR(TIMER0_COMPA_vect);
  ISR(TIMER1_COMPA_vect);

  // Timer functions
  void setupTimer(void);
  void delayMs(uint16_t timeMs);

  // Declaration of timer variables
  extern volatile uint16_t delayTimerCount;
  extern volatile uint8_t  delayTimerRunning;
  
  // Maintain state
  extern volatile uint8_t senseCount;
  extern volatile uint8_t canSense;
  extern volatile uint8_t canPrint;
  extern volatile uint8_t canPID;
  extern volatile uint8_t PIDCount;
  extern volatile uint8_t startTimer;
  extern volatile uint16_t timerVal;
  extern volatile uint16_t lookForDock;
#endif
