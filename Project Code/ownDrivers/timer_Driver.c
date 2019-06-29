/**************************************************
 * timer_Driver.c
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "timer_Driver.h"

int currentEdge = 0;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_ISR0(void)
{
  ADCCTL0 |= ADCENC | ADCSC;                            // Start new ADC sample
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_ISR0(void)
{
  if(TA1CCTL2 & 0x01 == CCIFG)                          // Check if capture has occurred
  {
    currentEdge = TA1CCR2;                              // Retrieve current timer count
    setPeriod(currentEdge);                             // Calculate period
    TA1CCTL2 &= ~(CCIFG);                               // Clear capture-compare interrupt flag
    setSampleStatus(1);                                 // Set that a sample has been captured
  }
  if(TA1CTL & 0x01 == TAIFG)                            // Check if timer overflow has occurred
  {
    TA1CTL &= ~(TAIFG);                                 // Clear timer overflow interrupt
  }
}

void initialisePwmTimer(unsigned int period, unsigned int highTime)
{
  TA0CTL |= TACLR;                                      // Clear the timer
  TA0R = 0;                                             // Set initial value
  TA0CCR0 = period;                                     // Set value for timer period
  TA0CCR1 = highTime;                                   // Set value for PWM high time
  TA0CTL |= TASSEL_2 | MC_1;                            // SMCLK (2MHz), up mode
  TA0CCTL1 = OUTMOD_6;                                  // PWM toggle/set
  TA0CCTL0 |= CCIE;                                     // Enable capture-compare interupts
  
  P1DIR |= BIT7;                                        // Set P1.7 to output
  P1SEL0 |= BIT7;                                       // Connect P1.7 to ADC module
}

void updatePwmDutyCycle(unsigned int duty)
{
  TA0CCTL0 &= !(MC_0);                                  // Disable timer
  TA0CCR1 = duty;                                       // Update high time value
  TA0CCTL0 |= MC_1;                                     // Re-enable timer
}

void initialiseSensorTimer()
{
  TA1CTL |= TACLR;                                      // Clear timer 0
  TA1CTL |= TASSEL_2 | MC_0 | TAIE;                     // Select SMCLK, Continuous, interrupt enable
  TA1CCTL2 |= CM_2 | CCIS_0 | CAP | CCIE;               // Set capture -ve edge, CCIxA, capture, interrupt enable
}