/**************************************************
 * sensor_Driver.h
 * Servo Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

/*  
    Vcc = 3V3
    GND = GND
    LED = P5.0
    OUT = P8.3
    S0 = P2.5
    S1 = P1.3
    S2 = P1.4
    S3 = P1.5
*/

#include <msp430.h>
#include "LCD_Driver.h"
   
#ifndef SENSOR_DRIVER_H_
#define SENSOR_DRIVER_H_

extern void initialiseLedIndicator();
extern void setRedLed(int state);
extern void setGreenLed(int state);
extern void setBlueLed(int state);

#endif

