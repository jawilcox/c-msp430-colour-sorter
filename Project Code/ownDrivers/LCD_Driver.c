/**************************************************
 * LCD_Driver.c
 * M&M Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "LCD_Driver.h"
#include <time.h>

int colour = 0;
int value = 0;
int count_red = 0;
int count_green = 0;
int count_blue = 0;
int count_yellow = 0;
int count_brown = 0;
int count_orange = 0;

void displayValue()
{
  switch(colour)
  {
  case 0:                                       // Red
    showChar('R', pos1);
    showChar('E', pos2);
    value = count_red;
    break;
  case 1:                                       // Green
    showChar('G', pos1);
    showChar('R', pos2);
    value = count_green;
    break;
  case 2:                                       // Blue
    showChar('B', pos1);
    showChar('L', pos2);
    value = count_blue;
    break;
  case 3:                                       // Yellow
    showChar('Y', pos1);
    showChar('E', pos2);
    value = count_yellow;
    break; 
  case 4:                                       // Brown
    showChar('B', pos1);
    showChar('R', pos2);
    value = count_brown;
    break; 
  case 5:                                       // Orange
    showChar('O', pos1);
    showChar('R', pos2);
    value = count_orange;
    break; 
  default:                                      // Error
    showChar('E', pos1);
    showChar('R', pos2);
    showChar('R', pos3);
    value = 0;
    break;
  }
  
  char num[3] = {0,0,0}; 
  
  num[0] = (value % 10) + 48;                   // Extract units value from integer
  num[1] = ((value/10) % 10) + 48;              // Extract tens value
  num[2] = ((value/100) % 10) + 48;             // Extract hundreds value
  
  showChar(num[2], pos4);                       // Display hundreds
  showChar(num[1], pos5);                       // Display tens
  showChar(num[0], pos6);                       // Display units
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
  switch(numColour)                             // Select correct colour to iterate
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
  
  num[0] = (counts % 10) + 48;                  // Extract units value from integer
  num[1] = ((counts/10) % 10) + 48;             // Extract tens value
  num[2] = ((counts/100) % 10) + 48;            // Extract hundreds value
  num[3] = ((counts/1000) % 10) + 48;           // Extract thousands value
  
  showChar(num[3], pos1);                       // Display thousands
  showChar(num[2], pos2);                       // Display hundreds
  showChar(num[1], pos3);                       // Display tens
  showChar(num[0], pos4);                       // Display units
}

