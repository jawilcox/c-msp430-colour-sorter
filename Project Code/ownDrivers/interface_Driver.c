/**************************************************
 * LED_Driver.c
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "interface_Driver.h"

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR0(void)
{
  switch(__even_in_range(P1IV, P1IV_P1IFG7))
  {
  case P1IV_P1IFG2:
    cycleColours();                     // Select next colour
    displayValue();                     // Display current count
    P1IFG &= (BIT2);                    // Clear interrupt
    break;
  }
}

void initialiseLedIndicator()
{
  P1SEL0 &= ~(BIT0 | BIT1);             // Set P1.0 and P1.1 as GPIO
  P1DIR |= BIT0 | BIT1;                 // Set P1.0 and P1.1 as output
  P2DIR |= BIT7;                        // Set P2.7 as output
  P1OUT &= ~(BIT0 | BIT1);              // Set P1.0 and P1.1 low
  P2OUT &= ~(BIT7);                     // Set P2.7 low
}

void setRedLed(int state)
{
  if(state == 1)
  {
    P1OUT |= BIT1;
  }
  else
    P1OUT &= ~(BIT1);
}

void setGreenLed(int state)
{
  if(state == 1)
  {
    P1OUT |= BIT0;
  }
  else
    P1OUT &= ~(BIT0);
}

void setBlueLed(int state)
{
  if(state == 1)
  {
    P2OUT |= BIT7;
  }
  else
    P2OUT &= ~(BIT7);
}

void displayColour(int colour)
{
  switch(colour)
  {
  case 0:                               // Red
    setRedLed(1);
    setGreenLed(0);
    setBlueLed(0);
    break;
  case 1:                               // Green
    setRedLed(0);
    setGreenLed(1);
    setBlueLed(0);
    break;
  case 2:                               // Blue
    setRedLed(0);
    setGreenLed(0);
    setBlueLed(1);
    break;
  case 3:                               // Yellow
    setRedLed(1);
    setGreenLed(1);
    setBlueLed(0);
    break;
  case 4:                               // Brown
    setRedLed(0);
    setGreenLed(0);
    setBlueLed(0);
    break;
  case 5:                               // Orange
    setRedLed(1);
    setGreenLed(1);
    setBlueLed(1);
    break;
  }
}

void initialiseStartSwitch()
{
  P2DIR &= ~(BIT6);                     // Set P2.6 as input
  P2REN |= BIT6;                        // Enable pullup resistor on P2.6
  P2IFG &= ~(BIT6);                     // Clear interrupts on P2.6
  P2IE |= BIT6;                         // Enable interrupts on P2.6
}

void initialiseColourSwitch()
{
  P1DIR &= ~(BIT2);                     // Set P1.2 as input
  P1REN |= BIT2;                        // Enable pullup resistor on P1.2
  P1IFG &= ~(BIT2);                     // Clear interrupts on P1.2
  P1IE |= BIT2;                         // Enable interrupts on P1.2
}