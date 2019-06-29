/**************************************************
 * LCD_Driver.h
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include <msp430.h>
#include "../lcdDrivers/hal_LCD.h"
   
#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

extern void displayValue();
extern void cycleColours();
extern void iterateColour(int);
extern void displayNumberCounts(int);

#endif

