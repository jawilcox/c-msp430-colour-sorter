/**************************************************
 * sensor_Driver.h
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

/*  
    Vcc = 3V3; GND = GND; LED = P5.0; OUT = P8.3
    S0 = P2.5; S1 = P1.3; S2 = P1.4; S3 = P1.5
*/

#include <msp430.h>
#include "LCD_Driver.h"
#include "interface_Driver.h"
#include "ADC_Driver.h"
   
#ifndef SENSOR_DRIVER_H_
#define SENSOR_DRIVER_H_

extern void initialiseSensor();
extern void selectDiode(int);
extern void setSensorScaling(int);
extern void enableSensorLed();
extern void disableSensorLed();
extern void setSampleStatus(int);
extern int getSampleStatus();
extern void singleSampleDiode(int);
extern void multiSampleDiode(int, int);
extern int getSamples(int);
extern void setPeriod(int);
extern int getPeriod();
extern void estimateColourThreshold(int, int, int, int);
extern void estimateColourRange(int, int, int, int);
extern int getIdentifiedColour();

#endif

