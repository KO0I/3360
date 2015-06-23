/*
   ===============================================================================
Name        : main.c

Authors     : Patrick Harrington and Marisa Martinez
Version     : 0.1
Copyright   : Copyright (C) 
Description : Lab 3 for ECEN 3000/3360
              Objective is to create a simple digital
              oscilloscope, driven exclusively by interrupts.
===============================================================================
*/
/* GPIO and GPIO Interrupt Initialization */
#ifdef __USE_CMSIS
#include "LPC11Uxx.h"
#endif
#include "timer32.h"
#include <cr_section_macros.h>

#define TEN_SEC 20000

// Global Variables
volatile uint32_t timer32_0_counter[4] = {0,0,0,0};
//volatile uint32_t timer32_1_counter[4] = {0,0,0,0};
volatile uint32_t Ttotal;	// total period of signal
static uint32_t duty_cycle_mode = 1; //0===25%, 1===75% Duty Cycle

uint32_t tick = 0; 
uint32_t tock = 0;
uint32_t period;
uint32_t duty;
uint32_t duty_cycle;
uint32_t duty_count;
uint32_t led_en = 0;


void GPIOInit() {
  // Set port 0 pin 7 to output
  LPC_GPIO->DIR[0] |= (1<<7);
  //LPC_GPIO->SET[0] |= (1<<7);
  
  // Set port 0 pin 0 to input
  LPC_GPIO->DIR[0] &= (0xFE);

  // Enable AHB clock to the GPIO domain.
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

  // Enable AHB clock to the FlexInt, GroupedInt domain.
  LPC_SYSCON->SYSAHBCLKCTRL |= ((1<<19) | (1<<23) | (1<<24));

  // Prepare and enable GPIO interrupts
  LPC_SYSCON->PINTSEL[0] = 0;
  NVIC->ISER[0] = (1<<((uint32_t)(FLEX_INT0_IRQn)& 0x1F)); 	// enable IRQ
  LPC_GPIO_PIN_INT->IENR |= (0x1<<0);						// Rising Edge of P0_0
  LPC_GPIO_PIN_INT->SIENR |= (0x1<<0);						// Rising Edge of P0_0
  LPC_GPIO->SET[0] = (0<<7);//keep the LED off on start
}

/* TIMER32 and TIMER32 Interrupt Initialization */
void TIMERInit() {
  // Enable AHB clock to the CT32B0 domain.
  // See page 31 of LPC User Manual
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);

  // Starting with one timer:
  // The timer CT32B0 has four match registers
  //    and two capture registers
  LPC_IOCON->PIO0_18 &= ~0x07;// I/O Config
  LPC_IOCON->PIO0_18 |=  0x02;// Timer0_32 CAP0

  //External Match Register Config

	LPC_CT32B0->EMR &= ~(0xFF<<4);//Clear EMR
  LPC_CT32B0->EMR |= ((0x3<<4)|(0x3<<6)|(0x3<<8)|(0x3<<10));	

  
  // when TC = 1/2ms, clear TC

  LPC_CT32B0->TCR = 0x02;// Reset the Timer
  LPC_CT32B0->PR  = 0x00;// Pre-scale
  LPC_CT32B0->MR0 = SystemCoreClock/2000;//ticks every half ms
  LPC_CT32B0->IR  = 0x11;// Clears the interrupt req.
  LPC_CT32B0->MCR = 0x03;// interrupt and reset on match
  LPC_CT32B0->TCR = 0x01;// start the timer(s)
  
  // replace with lower-level stuff later?
  NVIC_EnableIRQ(TIMER_32_0_IRQn);
  NVIC_SetPriority(TIMER_32_0_IRQn, 0);

  //LPC_GPIO2->IE |= (0x1<<1);//unmask the interrupt
}

/* GPIO Interrupt Handler */
void FLEX_INT0_IRQHandler(void) {
  LPC_GPIO->SET[0] = (0<<7);//keep the LED off on start
  // Right now, configured to trigger on rising edge of P0_0
	//if((LPC_GPIO->SET[0]>>7) & 0 )
	//LPC_GPIO->SET[0] ^= (1<<7);//toggle the LED
  period = tick - tock;
  tock = tick;
  duty = (period * duty_cycle)/100;
  // always enable the LED on rising edge
  LPC_GPIO->SET[0] = (1<<7);
  led_en = 1;
  duty_count = 0;
}

/* TIMER32 Interrupt Handler */
void TIMER32_0_IRQHandler(void) {
	// Clear interrupt registers and increment counter
	// These handle the match events on the timer
  
  LPC_CT32B0->IR = 0x11; //reset interrupt flag
  tick++;
  if(tick == TEN_SEC){
    tick = 0;
    if(duty_cycle_mode) duty_cycle = 75;
    else duty_cycle = 25;
    // toggle duty cycle mode
    duty_cycle_mode ^= duty_cycle_mode;
  }

  // if the LED is enabled
  if(led_en){
    //duty_count++;
    if(duty_count >= duty){
      LPC_GPIO->SET[0] = (0<<7);
    }
  }
	return;
}

int main(void) {

/* Initialization code */
  // Initialize GPIO ports for both Interrupts and LED control
  GPIOInit();                   
  // Initialize Timer and Generate a 1ms interrupt
  TIMERInit();                

  /* Infinite looping */
  while(1);      


  return 0;
}

