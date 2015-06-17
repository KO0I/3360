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
#include "LPC11Uxx.h"
#include "timer32.h"

// Global Variables
volatile uint32_t timer32_0_counter[4] = {0,0,0,0};
volatile uint32_t timer32_1_counter[4] = {0,0,0,0};

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
}

/* TIMER32 and TIMER32 Interrupt Initialization */
void TIMERInit() {
}

/* GPIO Interrupt Handler */
void FLEX_INT0_IRQHandler(void) {
	//if((LPC_GPIO->SET[0]>>7) & 0 )
		LPC_GPIO->SET[0] ^= (1<<7);
}

/* TIMER32 Interrupt Handler */
void TIMER32_0_IRQHandler(void) {
	// Clear interrupt registers and increment counter
	// These handle the match events on the timer
	if ( LPC_CT32B0->IR & (0x01<<0) ) {
		LPC_CT32B0->IR = 0x1<<0;
		timer32_0_counter[0]++;
	}
	if ( LPC_CT32B0->IR & (0x01<<1) ) {
		LPC_CT32B0->IR = 0x1<<1;
		timer32_0_counter[1]++;
	}
	if ( LPC_CT32B0->IR & (0x01<<2) ) {
		LPC_CT32B0->IR = 0x1<<2;
		timer32_0_counter[2]++;
	}
	if ( LPC_CT32B0->IR & (0x01<<3) ) {
		LPC_CT32B0->IR = 0x1<<3;
		timer32_0_counter[3]++;
	}

	// Handle capture events

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

