/**************************************************
 * motor_Driver.h
 * Sensor Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include <msp430.h>
#include "LCD_Driver.h"

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

extern void initialisePwmTimer(unsigned int period, unsigned int highTime);
extern void updatePwmDutyCycle(unsigned int duty);
extern void initialiseAdcModule();
extern void setServoPosition(int position);
extern void initialiseServoSwitches();
extern void setControlMethod(int method);

#endif

