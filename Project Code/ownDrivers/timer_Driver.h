/**************************************************
 * timer_Driver.h
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include <msp430.h>
#include "sensor_Driver.h"
   
#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

extern void initialisePwmTimer(unsigned int, unsigned int);
extern void updatePwmDutyCycle(unsigned int);
extern void initialiseSensorTimer();

#endif