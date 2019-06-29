/**************************************************
 * LCD_Driver.h
 * Sensor Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include <msp430.h>
#include "../lcdDrivers/hal_LCD.h"
   
#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

extern void initialiseSwitch(unsigned char port, unsigned char pin);
extern void displayValue();
extern void cycleColours();
extern void iterateColour(int numColour);
extern void displayNumberCounts(int counts);
extern void displayColour(int colour);

#endif

