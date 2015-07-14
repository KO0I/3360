#include "LPC11Uxx.h"
#include "uart.h"
//#include "adc.h"
#include "gpio.h"
#include "timer32.h"

#include <string.h>
#include <stdio.h>

#include "control.h"
#include "menu.h"

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

uint32_t state = 0;

volatile uint32_t led_en = 0;
volatile uint32_t led_freq = 10;
volatile uint32_t led_duty = 50;
volatile uint32_t led_count= 0;
volatile uint32_t led_period = 1000;

volatile uint32_t time_on;
volatile uint32_t duty_cycle = 25;
volatile uint32_t duty_count;

volatile uint32_t motor_en;
volatile uint32_t motor_count = 0;
volatile uint32_t motor_en_count = 0;
volatile uint32_t motor_duty = 51;
volatile uint32_t motor_runTime = 200000;	// Runtime is two seconds
volatile uint32_t motor_period = 300;		// Signal Period is 3ms (333Hz)

int main (void) {
  SystemCoreClockUpdate();
  // LED and ADC input
  GPIOInit();
  GPIOSetDir(0, 7, 1);
  // Port 0 Pin 1 is PWM output to motor
  GPIOSetDir(0, 1, 1);
  TIMERInit();

  // UART
  UARTInit(9600);

  // Welcome with the Unlocked Menu
  //print_arm_periph_menu();
  print_unlocked_menu();

  while (1) 
  {				/* Loop forever */
    if ( UARTCount != 0 )
    {
      LPC_USART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
      UARTSend( (uint8_t *)UARTBuffer, UARTCount );
      // take first character
      menuControl(UARTBuffer[0]);
      UARTCount = 0;
      LPC_USART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
    }
  }
}
