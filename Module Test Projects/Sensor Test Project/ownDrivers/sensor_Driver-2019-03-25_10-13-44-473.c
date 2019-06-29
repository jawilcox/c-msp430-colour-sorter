/**************************************************
 * sensor_Driver.c
 * Sensor Test Project
 *
 * Copyright 2018 University of Strathclyde
 *
 * James Wilcox
 **************************************************/

#include "sensor_Driver.h"

unsigned int numSamples = 10;
int sampleAverage[4] = {0,0,0,0};
int sampleComplete = 0;
int previousEdge = 0;
int currentEdge = 0;
int period = 0;
int samples[4] = {0,0,0,0};
int sample_flag = 0;
int identified_colour = 0;

int thres_r = 65;
int thres_g = 62;
int thres_b = 70;

#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_ISR0(void)
{
  if(TA1CCTL2 & 0x01 == CCIFG)                                  // Check if capture has occurred
  {
    currentEdge = TA1CCR2;                                      // Retrieve current timer count
    period = currentEdge - previousEdge;                        // Calculate period
    previousEdge = currentEdge;                                 // Store current timer count
    TA1CCTL2 &= ~(CCIFG);                                       // Clear capture-compare interrupt flag
    setSampleStatus(1);                                         // Set that a sample has been captured
    previousEdge = 0;                                           // reset previousEdge
  }
  if(TA1CTL & 0x01 == TAIFG)                                    // Check if timer overflow has occurred
  {
    previousEdge = 0;                                           // Set variable to 0 on overflow
    TA1CTL &= ~(TAIFG);                                         // Clear timer overflow interrupt
  }
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR0(void)
{
  switch(__even_in_range(P1IV, P1IV_P1IFG7))
  {
  case P1IV_P1IFG2:
    sample_flag = 1;
    P1IFG &= (BIT2);                                    // Clear interrupt
    break;
  }
}

void initialiseSensor()
{
  TA1CTL |= TACLR;                              // Clear timer 0
  TA1CTL |= TASSEL_2 | MC_0 | TAIE;             // Select SMCLK, Continuous, interrupt enable
  TA1CCTL2 |= CM_2 | CCIS_0 | CAP | CCIE;       // Set capture -ve edge, CCIxA, capture, interrupt enable
  
  P8DIR &= ~(BIT3);                             // Set P8.3 as input
  P8SEL0 |= BIT3;                               // Connect P8.3 to timer
  
  P1DIR |= BIT3 | BIT4 | BIT5;                  // Set P1.3-5 as output (select lines)
  P2DIR |= BIT5;                                // Set P2.5 as output (select lines)

  setSensorScaling(0);
  disableSensorLed();
}

void selectDiode(int mode)
{
  switch(mode)
  {
  case 0:                                       // If red diode desired
    P1OUT &= ~(BIT4 | BIT5);                    // P1.4 (S2) = 0, P1.5 (S3) = 0
    break;
  case 1:                                       // If blue diode desired
    P1OUT &= ~(BIT4);                           // P1.4 (S2) = 0
    P1OUT |= BIT5;                              // P1.5 (S3) = 1
    break;
  case 2:                                       // If clear diode desired
    P1OUT |= BIT4;                              // P1.4 (S2) = 1
    P1OUT &= ~(BIT5);                           // P1.5 (S3) = 0
    break;
  case 3:                                       // If green diode desired
    P1OUT |= BIT4 | BIT5;                       // P1.4 (S2) = 1, P1.5 (S3) = 1
  default:                                      // If error in setting
    P2OUT &= ~(BIT5);                           // Turn sensor off
    P1OUT &= ~(BIT3);
    break;
  }
}

void setSensorScaling(int scale)
{
  switch(scale)
  {
  case 0:                                       // If turning sensor off
    P2OUT &= ~(BIT5);                           // P2.5 (S0) = 0
    P1OUT &= ~(BIT3);                           // P1.3 (S1) = 0
    break;
  case 2:                                       // If setting to 2%
    P2OUT &= ~(BIT5);                           // P2.5 (S0) = 0
    P1OUT |= BIT3;                              // P1.3 (S1) = 1
    break;
  case 20:                                      // If setting to 20%
    P2OUT |= BIT5;                              // P2.5 (S0) = 1
    P1OUT &= ~(BIT3);                           // P1.3 (S1) = 0
    break;
  case 100:                                     // If setting to 100%
    P2OUT |= BIT5;                              // P2.5 (S0) = 1
    P1OUT |= BIT3;                              // P1.3 (S1) = 1
    break;
  default:                                      // If invalid setting
    P2OUT &= ~(BIT5);                           // turn sensor off
    P1OUT &= ~(BIT3);
    break;
  }
}

void enableSensorLed()
{
  P5DIR |= BIT0;                              // Set P5.0 to output
  P5OUT |= BIT0;                             // Set P5.0 to low
}

void disableSensorLed()
{
  P5DIR |= (BIT0);                              // Set P5.0 to output
  P5OUT &= ~(BIT0);                             // Set P5.0 to low
}

void setSampleStatus(int status)
{
  sampleComplete = status;
}

int getSampleStatus()
{
  return sampleComplete;
}

void singleSampleDiode(int diode)
{
  enableSensorLed();
  selectDiode(diode);                           // Select relevant diode array
  TA1CTL |= MC_2;                               // Enable timer, continuous mode
  setSensorScaling(20);                          // Enable sensor, 20% scaling
    
  while(!sampleComplete)                        // While no sample captured
  {
    ;
  }
  
  TA1CTL &= ~(MC_0);                               // Disable timer
  TA1R = 0;                                     // Reset timer counter
  setSensorScaling(0);                          // Disable sensor
  disableSensorLed();
}

void multiSampleDiode(int diode, int num_samples)
{
  for(int i=0; i<num_samples; i++)
  {
    singleSampleDiode(diode);
    samples[i] = getPeriod();
    setSampleStatus(0);
  }
}

void setSampleFlag(int flag)
{
  sample_flag = flag;
}

int getSampleFlag()
{
  return sample_flag;
}

int getSamples(int index)
{
  return samples[index];
}

int getPeriod()
{
  return period;
}

int mapToRGB(long sample, long in_min, long in_max, long out_min, long out_max)
{
  long result = 1000000/sample;                 // Calculate frequency of sample
  result = (result - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return result;
}

void initialiseSensorSwitch()
{
  P1DIR &= ~(BIT2);
  P1REN |= BIT2;
  P1IFG &= ~(BIT2);
  P1IE |= BIT2;
}

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

void displaySample(int red, int green, int blue, int clear)
{
  displayNumberCounts(red);
  __delay_cycles(1000000);
  clearLCD();
  displayNumberCounts(green);
  __delay_cycles(1000000);
  clearLCD();
  displayNumberCounts(blue);
  __delay_cycles(1000000);
  clearLCD();
  displayNumberCounts(clear);
  __delay_cycles(1000000);
  clearLCD();
  setSampleFlag(0);
}

void estimateColour(int red, int green, int blue, int clear)
{
  if(clear < 300)
  {
    clear = 350;
  }
  
  unsigned int per_red = (clear * 100L) / red;
  unsigned int per_green = (clear * 100L) / green;
  unsigned int per_blue = (clear * 100L) / blue;
  
  if(per_red > thres_r)
  {
    if(per_green > thres_g)
    {
      if(per_blue > thres_b)
      {
        identified_colour = 5;
      }
      else
      {
        identified_colour = 3;
      }
    }
    else
    {
      identified_colour = 0;
    }
  }
  else if(per_green > thres_g)
  {
    identified_colour = 1;
  }
  else if(per_blue > thres_b)
  {
    identified_colour = 2;
  }
  else
  {
    identified_colour = 4;
  }
}

int getIdentifiedColour()
{
  return identified_colour;
}