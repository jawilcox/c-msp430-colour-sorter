/**************************************************
 * sensor_Driver.c
 * Servo Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "sensor_Driver.h"

void initialiseLedIndicator()
{
  P1SEL0 &= ~(BIT0 | BIT1);
  P1DIR |= BIT0 | BIT1;
  P2DIR |= BIT7;
  P1OUT &= ~(BIT0 | BIT1);
  P2OUT &= ~(BIT7);
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

