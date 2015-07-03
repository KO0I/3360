#include "LPC11Uxx.h"
#include "uart.h"
#include "gpio.h"
#include "timer32.h"

#include <string.h>
#include <stdio.h>

#include "control.h"
#include "menu.h"

extern volatile uint32_t timer32_0_counter;
extern volatile uint32_t timer32_0_capture;

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

uint32_t state = 0;

uint32_t led_en = 0;
uint32_t led_freq = 10;
uint32_t led_duty = 50;
uint32_t led_count= 0;

int main (void) {
  SystemCoreClockUpdate();
  // LED
  GPIOInit();
  GPIOSetDir(0, 7, 1);
  // Timer

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
