/**************************************************
 * main.c
 * Servo Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "lcdDrivers/hal_LCD.h"
#include "driverlib/MSP430FR2xx_4xx/driverlib.h"
#include "ownDrivers/motor_Driver.h"
#include "ownDrivers/sensor_Driver.h"
#include "ownDrivers/LCD_Driver.h"

int main( void )
{
  initialiseLedIndicator();                     // Setup LED pins and turn off all LEDs
  setRedLed(1);
  setGreenLed(1);
  setBlueLed(1);
  
  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer to prevent time out reset
  PMM_unlockLPM5();                             // Unlock Low power mode 5
  __enable_interrupt();                         // Enable general interrupts in the system register
  
  Init_LCD();                                   // Initialise the LCD screen
  clearLCD();                                   // Ensure the LCD screen is clear

  initialiseServoSwitches();                    // Setup the switches on the MSP430 board
  initialiseAdcModule();                        // Configure and start the ADC module
  initialisePwmTimer(20000, 500);               // Configure and start the PWM module
  
  while(1)
  {
    ;                                           // Infinite loop
  }
}

