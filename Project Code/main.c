/**************************************************
 * main.c
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "lcdDrivers/hal_LCD.h"
#include "driverlib/MSP430FR2xx_4xx/driverlib.h"
#include "ownDrivers/motor_Driver.h"
#include "ownDrivers/LCD_Driver.h"
#include "ownDrivers/interface_Driver.h"
#include "ownDrivers/sensor_Driver.h"
#include "ownDrivers/timer_Driver.h"
#include "ownDrivers/ADC_Driver.h"

int main( void )
{
  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer to prevent time out reset
  PMM_unlockLPM5();                             // Unlock Low power mode 5
  __enable_interrupt();                         // Enable general interrupts in the system register
  
  Init_LCD();                                   // Initialise the LCD screen
  clearLCD();                                   // Ensure the LCD screen is clear
  
  initialiseLedIndicator();                     // Initialise indicator LEDs
  setRedLed(0);                                 // Define level of red LED indicator
  setGreenLed(0);                               // Define level of green LED indicator
  setBlueLed(0);                                // Define level of blue LED indicator
  
  initialiseStartSwitch();
  initialiseColourSwitch();
  
  initialiseSensorTimer();
  initialiseSensor();                           // Initialise the sensor timer and pins
  enableSensorLed();                            // Enable LEDs on sensor board
  
  initialiseAdcModule();
  initialisePwmTimer(20000, 500);
  initMotor();
  
  while(1)
  {
    evenDistribution();
    //colourDistribution();
  }
}