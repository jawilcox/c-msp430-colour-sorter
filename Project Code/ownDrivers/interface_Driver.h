/**************************************************
 * LED_Driver.h
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/
 
#include <msp430.h>
#include "LCD_Driver.h"
   
#ifndef INTERFACE_DRIVER_H_
#define INTERFACE_DRIVER_H_

extern void initialiseLedIndicator();
extern void setRedLed(int);
extern void setGreenLed(int);
extern void setBlueLed(int);
extern void displayColour(int);
extern void initialiseStartSwitch();
extern void initialiseColourSwitch();

#endif