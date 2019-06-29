/**************************************************
 * motor_Driver.h
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD_Driver.h"
#include "timer_Driver.h"
#include "ADC_Driver.h"
#include "sensor_Driver.h"

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

extern void initMotor();
extern void setServoPosition(int);
extern void evenDistribution();
extern void colourDistribution();
extern void stepClockwise();
extern void stepAntiClockwise();

#endif

