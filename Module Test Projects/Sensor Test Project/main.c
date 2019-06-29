/**************************************************
 * main.c
 * Sensor Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "lcdDrivers/hal_LCD.h"
#include "driverlib/MSP430FR2xx_4xx/driverlib.h"
#include "ownDrivers/motor_Driver.h"
#include "ownDrivers/LCD_Driver.h"
#include "ownDrivers/sensor_Driver.h"

int R_Val = 0;
int G_Val = 0;
int B_Val = 0;
int C_Val = 0;

int main( void )
{
  initialiseLedIndicator();                     // Initialise indicator LEDs
  
  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer to prevent time out reset
  PMM_unlockLPM5();                             // Unlock Low power mode 5
  __enable_interrupt();                         // Enable general interrupts in the system register
  
  Init_LCD();                                   // Initialise the LCD screen
  clearLCD();                                   // Ensure the LCD screen is clear
  
  initialiseSensor();                           // Initialise the sensor timer and pins
  initialiseSensorSwitch();
  
  while(1)
  {
    if(getSampleFlag())
    {
      multiSampleDiode(0, 5);                   // Take 5 samples of the red diodes
      R_Val = getSamples(2);
      multiSampleDiode(1, 5);                   // Take 5 samples of blue diodes
      B_Val = getSamples(2);
      multiSampleDiode(2, 5);                   // Take 5 samples of clear diodes
      C_Val = getSamples(2);
      multiSampleDiode(3, 5);                   // Take 5 samples of green diodes
      G_Val = getSamples(2);
      
      estimateColour(R_Val, G_Val, B_Val, C_Val);
      displayColour(getIdentifiedColour());
      setSampleFlag(0);                         // Set that the sample is complete
    }
  }
}

