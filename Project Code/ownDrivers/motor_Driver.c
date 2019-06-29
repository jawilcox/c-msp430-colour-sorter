/**************************************************
 * motor_Driver.c
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "motor_Driver.h"

int R_Val = 0;
int G_Val = 0;
int B_Val = 0;
int C_Val = 0;
int currentServoPos = 500;
int newServoPos = 0;
int numSteps = 10;
int stepSize = 0;

void initMotor()
{
  updatePwmDutyCycle(500);
  __delay_cycles(1000000);
  currentServoPos = 500;
}

void setServoPosition(int position)
{
  switch(position)
  {
  case 0:                                               // Feeder Tube
    newServoPos = 500;
    numSteps = 20;
    stepClockwise();
    currentServoPos = newServoPos;
    __delay_cycles(100000);
    break;
  case 1:                                               // Sensor
    newServoPos = 750;
    numSteps = 4;
    stepAntiClockwise();
    currentServoPos = newServoPos;
    __delay_cycles(100000);
    break;
  case 2:                                               // Red/Orange
    newServoPos = 1250;
    numSteps = 6;
    stepAntiClockwise();
    currentServoPos = newServoPos;
    break;
  case 3:                                               // Green
    newServoPos = 1500;
    numSteps = 8;
    stepAntiClockwise();
    currentServoPos = newServoPos;
    break;
  case 4:                                               // Blue
    newServoPos = 1850;
    numSteps = 12;
    stepAntiClockwise();
    currentServoPos = newServoPos;
    break;
  case 5:                                               // Yellow
    newServoPos = 2250;
    numSteps = 16;
    stepAntiClockwise();
    currentServoPos = newServoPos;
    break;
  case 6:                                               // Brown
    newServoPos = 2500;
    numSteps = 20;
    stepAntiClockwise();
    currentServoPos = newServoPos;
    break;
  default:                                              // Invalid Input
    newServoPos = 500;
    numSteps = 20;
    stepClockwise();
    currentServoPos = newServoPos;
    break;
  }
}

void evenDistribution()
{
  setServoPosition(0);                                  // Return to feeder tube
  
  for(int i=1; i<6; i++)                                // For each container
  {
    setServoPosition(2);                                // Move to sensing position
    displayColour(i-1);                                 // Indicate container colour with LEDs
    setServoPosition(i+1);                                // Move to next container
    iterateColour(i-1);                                 // update counts
    displayValue();                                     // Display current count on LCD
    setServoPosition(0);                                // Return to feeder tube
  }
}

void colourDistribution()
{
  setServoPosition(0);
  setServoPosition(2);
  __delay_cycles(1000000);
  
  multiSampleDiode(0, 5);                               // Take 5 samples of the red diodes
  R_Val = getSamples(2);
  multiSampleDiode(1, 5);                               // Take 5 samples of blue diodes
  B_Val = getSamples(2);
  multiSampleDiode(2, 5);                               // Take 5 samples of clear diodes
  C_Val = getSamples(2);
  multiSampleDiode(3, 5);                               // Take 5 samples of green diodes
  G_Val = getSamples(2);
      
  estimateColourRange(R_Val, G_Val, B_Val, C_Val);      // Identify sensed colour
  iterateColour(getIdentifiedColour());                 // update counts
  displayColour(getIdentifiedColour());                 // Indicate sensed colour with LEDs
  setServoPosition(getIdentifiedColour()+2);            // Moved to sensed colour position
  displayValue();                                       // Display current count on LCD
  setSampleStatus(0);                                   // Ready for next sample
  
  setServoPosition(0);                                  // return to feeder tube
}

void stepClockwise()
{
  stepSize = abs((newServoPos - currentServoPos) / numSteps);
  
  for(int i=1; i<numSteps+1; i++)
  {
    updatePwmDutyCycle(currentServoPos - stepSize);
    __delay_cycles(100000);
    currentServoPos -= stepSize;
  }
}

void stepAntiClockwise()
{
  stepSize = abs((newServoPos - currentServoPos) / numSteps);
  
  for(int i=1; i<numSteps+1; i++)
  {
    updatePwmDutyCycle(currentServoPos + stepSize);
    __delay_cycles(100000);
    currentServoPos += stepSize;
  }
}