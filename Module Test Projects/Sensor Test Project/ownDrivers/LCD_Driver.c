/**************************************************
 * LCD_Driver.c
 * Sensor Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "LCD_Driver.h"

int colour = 0;
int value = 0;
int count_red = 0;
int count_green = 0;
int count_blue = 0;
int count_yellow = 0;
int count_brown = 0;
int count_orange = 0;

void initialiseSwitch(unsigned char port, unsigned char pin)
{
  GPIO_selectInterruptEdge(port, pin, GPIO_HIGH_TO_LOW_TRANSITION);
  GPIO_setAsInputPinWithPullUpResistor(port, pin);
  GPIO_clearInterrupt(port, pin);
  GPIO_enableInterrupt(port, pin);
}

void displayValue()
{
  switch(colour)
  {
  case 0:
    showChar('R', pos1);
    showChar('E', pos2);
    value = count_red;
    break;
  case 1:
    showChar('G', pos1);
    showChar('R', pos2);
    value = count_green;
    break;
  case 2:
    showChar('B', pos1);
    showChar('L', pos2);
    value = count_blue;
    break;
  case 3:
    showChar('Y', pos1);
    showChar('E', pos2);
    value = count_yellow;
    break; 
  case 4:
    showChar('B', pos1);
    showChar('R', pos2);
    value = count_brown;
    break; 
  case 5:
    showChar('O', pos1);
    showChar('R', pos2);
    value = count_orange;
    break; 
  default:
    showChar('E', pos1);
    showChar('R', pos2);
    value = 0;
    break;
  }
  
  char num[3] = {0,0,0}; 
  
  num[0] = (value % 10) + 48;             // Extract units value from integer
  num[1] = ((value/10) % 10) + 48;        // Extract tens value
  num[2] = ((value/100) % 10) + 48;       // Extract hundreds value
  
  showChar(num[2], pos4);
  showChar(num[1], pos5);
  showChar(num[0], pos6);
}

void cycleColours()
{
  if(colour < 5)
  {
    colour ++;
  }
  else
    colour = 0;
}

void iterateColour(int numColour)
{
  switch(numColour)
  {
  case 0:
    count_red ++;
    break;
  case 1:
    count_green ++;
    break;
  case 2:
    count_blue ++;
    break;
  case 3:
    count_yellow ++;
    break;
  case 4:
    count_brown ++;
    break;
  case 5:
    count_orange ++;
    break;
  }
}

void displayNumberCounts(int counts)
{
  char num[4] = {0,0,0,0}; 
  
  num[0] = (counts % 10) + 48;             // Extract units value from integer
  num[1] = ((counts/10) % 10) + 48;        // Extract tens value
  num[2] = ((counts/100) % 10) + 48;       // Extract hundreds value
  num[3] = ((counts/1000) % 10) + 48;
  
  showChar(num[3], pos1);
  showChar(num[2], pos2);
  showChar(num[1], pos3);
  showChar(num[0], pos4);
}

void displayColour(int colour)
{
  switch(colour)
  {
  case 0:
    showChar('R', pos1);
    showChar('E', pos2);
    showChar('D', pos3);
    break;
  case 1:
    showChar('G', pos1);
    showChar('R', pos2);
    showChar('E', pos3);
    break;
  case 2:
    showChar('B', pos1);
    showChar('L', pos2);
    showChar('U', pos3);
    break;
  case 3:
    showChar('Y', pos1);
    showChar('E', pos2);
    showChar('L', pos3);
    break;
  case 4:
    showChar('B', pos1);
    showChar('R', pos2);
    showChar('O', pos3);
    break;
  case 5:
    showChar('O', pos1);
    showChar('R', pos2);
    showChar('A', pos3);
    break;
  }
  __delay_cycles(1000000);
  clearLCD();
}