/**************************************************
 * sensor_Driver.c
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "sensor_Driver.h"

unsigned int numSamples = 10;
int sampleAverage[4] = {0,0,0,0};
int sampleComplete = 0;
int period = 0;
int samples[4] = {0,0,0,0};

int identified_colour = 0;
int thres_r = 43;
int thres_g = 46;
int thres_b = 58;

void initialiseSensor()
{
  P8DIR &= ~(BIT3);                             // Set P8.3 as input
  P8SEL0 |= BIT3;                               // Connect P8.3 to timer
  
  P1DIR |= BIT3 | BIT4 | BIT5;                  // Set P1.3-5 as output (select lines)
  P2DIR |= BIT5;                                // Set P2.5 as output (select lines)

  setSensorScaling(0);                          // Turn off sensor output
  disableSensorLed();                           // Torn off sensor LED
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
  P5DIR |= BIT0;                                // Set P5.0 to output
  P5OUT |= BIT0;                                // Set P5.0 to low
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
  setSensorScaling(20);                         // Enable sensor, 20% scaling
    
  while(!sampleComplete)                        // While no sample captured
  {
    ;
  }
  
  TA1CTL &= ~(MC_0);                            // Disable timer
  TA1R = 0;                                     // Reset timer counter
  setSensorScaling(0);                          // Disable sensor
  disableSensorLed();                           // Disable sensor LED
}

void multiSampleDiode(int diode, int num_samples)
{
  for(int i=0; i<num_samples; i++)
  {
    singleSampleDiode(diode);                   // Take repeated single samples
    samples[i] = getPeriod();                   // Store sample period
    setSampleStatus(0);                         // Ready for next sample
  }
}

int getSamples(int index)
{
  return samples[index];
}

void setPeriod(int T)
{
  period = T;
}

int getPeriod()
{
  return period;
}

void estimateColourThreshold(int red, int green, int blue, int clear)
{
  if(clear < 300)                                       // If error in clear measurement, normally '19'
  {
    clear = 315;
  }
  
  unsigned int per_red = (clear * 100L) / red;          // Calculate percentage contributions of R, G, and B
  unsigned int per_green = (clear * 100L) / green;
  unsigned int per_blue = (clear * 100L) / blue;
  
  if(per_red > thres_r)
  {
    if(per_green > thres_g)
    {
      if(per_blue > thres_b)
      {
        identified_colour = 0;                          // Orange
      }
      else
      {
        identified_colour = 3;                          // Yellow
      }
    }
    else
    {
      identified_colour = 0;                            // Red
    }
  }
  else if(per_green > thres_g)
  {
    identified_colour = 1;                              // Green
  }
  else if(per_blue > thres_b)
  {
    identified_colour = 2;                              // Blue
  }
  else
  {
    identified_colour = 4;                              // Brown
  }
}

void estimateColourRange(int red, int green, int blue, int clear)
{
  if(red < 300)                                       // If error in clear measurement, normally '19'
  {
    red = 315;
  }
  
  if(green < 300)                                       // If error in clear measurement, normally '19'
  {
    green = 315;
  }
  
  if(blue < 300)                                       // If error in clear measurement, normally '19'
  {
    blue = 315;
  }
  
  unsigned int per_red = (red * 100L) / (red+green+blue);          // Calculate percentage contributions of R, G, and B
  unsigned int per_green = (green * 100L) / (red+green+blue);
  unsigned int per_blue = (blue * 100L) / (red+green+blue);
  
  if(per_red>29 && per_red<32 && per_green>36 && per_green<38 && per_blue>30 && per_blue<32)
  {
    identified_colour = 0;                              // Red
  }
  else if(per_red>33 && per_red<35 && per_green>32 && per_green<35 && per_blue>30 && per_blue<32)
  {
    identified_colour = 1;                              // Green
  }
  else if(per_red>34 && per_red<37 && per_green>34 && per_green<36 && per_blue>27 && per_blue<29)
  {
    identified_colour = 2;                              // Blue
  }
  else if(per_red>30 && per_red<34 && per_green>33 && per_green<35 && per_blue>31 && per_blue<35)
  {
    identified_colour = 3;                              // Yellow
  }
  else if(per_red>31 && per_red<34 && per_green>34 && per_green<36 && per_blue>29 && per_blue<32)
  {
    identified_colour = 4;                              // Brown
  }
  else if(per_red>27 && per_red<31 && per_green>35 && per_green<41 && per_blue>30 && per_blue<33)
  {
    identified_colour = 0;                              // Orange
  }
  else
  {
    estimateColourThreshold(red, green, blue, clear);   // If not within colour ranges, use threshold method
  }
}

int getIdentifiedColour()
{
  return identified_colour;
}