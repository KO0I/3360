#include "LPC11Uxx.h"
#include "uart.h"
#include "gpio.h"
#include "timer32.h"

#include <string.h>
#include <stdio.h>



//extern volatile uint32_t timer32_0_counter;
//extern volatile uint32_t timer32_0_capture;

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

uint32_t state = 0;

volatile uint32_t led_en = 0;
volatile uint32_t led_freq = 10;
volatile uint32_t led_duty = 50;
volatile uint32_t led_count= 0;
volatile uint32_t led_period = 1000;

volatile uint32_t start_of_period = 0;
volatile uint32_t period;
volatile uint32_t time_on;
volatile uint32_t duty_cycle = 25;
volatile uint32_t duty_count;

#include "control.h"
#include "menu.h"

int main (void) {
  SystemCoreClockUpdate();
  // LED
  GPIOInit();
  GPIOSetDir(0, 7, 1);
  TIMERInit();

  // UART
  UARTInit(9600);

  // Willkommen mit Peripheral Menü
  print_arm_periph_menu();

  while (1) 
  {				/* Loop forever */
    if ( UARTCount != 0 )
    {
      LPC_USART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
      UARTSend( (uint8_t *)UARTBuffer, UARTCount );
      menuControl(UARTBuffer[0]);
      UARTCount = 0;
      LPC_USART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
    }
  }
}
