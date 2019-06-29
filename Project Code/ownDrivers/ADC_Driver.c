/**************************************************
 * ADC_Driver.c
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "ADC_Driver.h"

int rate = 0;

#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void)
{
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
  {
    case ADCIV_ADCIFG:                          // When conversion complete
      rate = (ADCMEM0 * 25) / 10;               // Scale ADC value, range = 0 to 2500
      //updatePwmDutyCycle(rate);               // Set new duty cycle to timer
      //displayNumberCounts(rate);              // Display new duty cycle value
    break;
  }
}

void initialiseAdcModule()
{
  P8DIR &= ~(BIT1);                             // Set P8.1 as input
  P8SEL0 |= BIT1;                               // Connect P8.1 to ADC module
  
  SYSCFG2 |= ADCPCTL9;                          // Set pin A9 (8.1) as ADC input
  ADCCTL0 |= ADCSHT_2 | ADCON;                  // ADC Sample Hold Select 2 | ADC On/enable
  ADCCTL1 |= ADCSHP;                            // ADC Sample/Hold Pulse Mode
  ADCCTL2 |= ADCRES;                            // ADC Resolution 10-Bit
  ADCMCTL0 |= ADCINCH_9;                        // ADC Input Channel 9
  ADCIFG &= ~(ADCIFG0);                         // Clear interrupts
  ADCIE |= ADCIE0;                              // Enable interrupts
  ADCCTL0 |= ADCENC;                            // Enable sampling
}