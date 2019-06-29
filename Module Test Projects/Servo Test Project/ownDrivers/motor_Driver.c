/**************************************************
 * motor_Driver.c
 * Servo Test Project
 *
 * Last Updated : 17/4/19
 *
 * Authors : James Wilcox
 **************************************************/

#include "motor_Driver.h"

int rate = 0;
int servo_test_pos = 0;
int controlMethod = 0;

#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void)
{
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
  {
    case ADCIV_ADCIFG:                                  // When conversion complete
      rate = (int)(ADCMEM0 * 2.5);                             // Scale ADC value, range = 0 to 2500
      if(controlMethod == 0)
      {
        updatePwmDutyCycle(rate);                       // Set new duty cycle to timer
        displayNumberCounts(rate);                      // Display new duty cycle value
      }
    break;
  }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_ISR0(void)
{
  ADCCTL0 |= ADCENC | ADCSC;                            // Start new ADC sample
}

#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR0(void)
{
  switch(__even_in_range(P2IV, P2IV_P2IFG7))
  {
  case P2IV_P2IFG6:
    if(servo_test_pos < 7)                              // If not at end position
    {
      servo_test_pos++;                                 // Iterate servo position
    }
    else
    {
      servo_test_pos = 0;                               // Reset servo position
    }
    if(controlMethod == 1)
    {
      setServoPosition(servo_test_pos);                 // Update PWM duty cycle
      displayNumberCounts(servo_test_pos);              // Output new position to LCD screen
    }
    P2IFG &= ~(BIT6);                                   // Clear interrupt
    break;
  }
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR0(void)
{
  switch(__even_in_range(P1IV, P1IV_P1IFG7))
  {
  case P1IV_P1IFG2:
    controlMethod ^= 1;                                 // Toggle between manual and semi-auto control
    P1IFG &= ~(BIT2);                                   // Clear interrupt
    break;
  }
}

void initialisePwmTimer(unsigned int period, unsigned int highTime)
{
  TA0CTL |= TACLR;                                      // Clear the timer
  TA0R = 0;                                             // Set initial value
  TA0CCR0 = period;                                     // Set value for timer period
  TA0CCR1 = highTime;                                   // Set value for PWM high time
  TA0CTL |= TASSEL_2 | MC_1;                            // SMCLK (2MHz), up mode
  TA0CCTL1 = OUTMOD_6;                                  // PWM toggle/set
  TA0CCTL0 |= CCIE;                                     // Enable capture-compare interupts
  
  P1DIR |= BIT7;                                        // Set P1.7 to output
  P1SEL0 |= BIT7;                                       // Connect P1.7 to ADC module
}

void updatePwmDutyCycle(unsigned int duty)
{
  TA0CCTL0 &= !(MC_0);                                  // Disable timer
  TA0CCR1 = duty;                                       // Update high time value
  TA0CCTL0 |= MC_1;                                     // Re-enable timer
}
  
void initialiseAdcModule()
{
  P8DIR &= ~(BIT1);                                     // Set P8.1 as input
  P8SEL0 |= BIT1;                                       // Connect P8.1 to ADC module
  
  SYSCFG2 |= ADCPCTL9;                                  // Set pin A9 (8.1) as ADC input
  ADCCTL0 |= ADCSHT_2 | ADCON;                          // ADC Sample Hold Select 2 | ADC On/enable
  ADCCTL1 |= ADCSHP;                                    // ADC Sample/Hold Pulse Mode
  ADCCTL2 |= ADCRES;                                    // ADC Resolution 10-Bit
  ADCMCTL0 |= ADCINCH_9;                                // ADC Input Channel 9
  ADCIFG &= ~(ADCIFG0);                                 // Clear interrupts
  ADCIE |= ADCIE0;                                      // Enable interrupts
  ADCCTL0 |= ADCENC;                                    // Enable sampling
}

void setServoPosition(int position)
{
  switch(position)
  {
  case 0:                                               // Feeder Tube
    updatePwmDutyCycle(500);
    break;
  case 1:                                               // Red Channel
    updatePwmDutyCycle(850);
    break;
  case 2:                                               // Green Channel
    updatePwmDutyCycle(1150);
    break;
  case 3:                                               // Blue Channel
    updatePwmDutyCycle(1450);
    break;
  case 4:                                               // Yellow Channel
    updatePwmDutyCycle(1750);
    break;
  case 5:                                               // Orange Channel
    updatePwmDutyCycle(2050);
    break;
  case 6:                                               // Brown Channel
    updatePwmDutyCycle(2500);
    break;
  default:                                              // Invalid Input
    updatePwmDutyCycle(500);
    break;
  }
}

void initialiseServoSwitches()
{
  P2DIR &= ~(BIT6);                                     // Set P2.6 as input
  P2REN |= BIT6;                                        // Enable pullup resistor on P2.6
  P2IFG &= ~(BIT6);                                     // Clear interrupts on P2.6
  P2IE |= BIT6;                                         // Enable interrupts on P2.6
  
  P1DIR &= ~(BIT2);                                     // Set P1.2 as input
  P1REN |= BIT2;                                        // Enable pullup resistor on P1.2
  P1IFG &= ~(BIT2);                                     // Clear interrupts on P1.2
  P1IE |= BIT2;                                         // Enable interrupts on P1.2
}

void setControlMethod(int method)
{
  controlMethod = method;                               // Set manual or semi-auto control
}