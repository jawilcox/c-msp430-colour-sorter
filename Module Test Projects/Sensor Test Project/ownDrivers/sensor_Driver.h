/**************************************************
 * sensor_Driver.h
 * Sensor Test Project
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

extern void initialiseSensor();
extern void selectDiode(int mode);
extern void setSensorScaling(int scale);
extern void enableSensorLed();
extern void disableSensorLed();
extern void setSampleStatus(int status);
extern int getSampleStatus();
extern void singleSampleDiode(int diode);
extern void multiSampleDiode(int diode, int num_samples);
extern void setSampleFlag(int flag);
extern int getSampleFlag();
extern int getSamples(int index);
extern int getPeriod();
extern void initialiseSensorSwitch();
extern void initialiseLedIndicator();
extern void setRedLed(int state);
extern void setGreenLed(int state);
extern void setBlueLed(int state);
extern void estimateColour(int red, int green, int blue, int clear);
extern int getIdentifiedColour();

#endif

