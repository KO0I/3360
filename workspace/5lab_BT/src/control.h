#ifndef CONTROL_H_
#define CONTROL_H_

volatile extern uint32_t start_of_period;
volatile extern uint32_t period;
volatile extern uint32_t led_en;
volatile extern uint32_t led_freq;
volatile extern uint32_t led_duty;
volatile extern uint32_t led_count;
volatile extern uint32_t led_period;

//------------------------------------------------------
//    Peripheral Control 
//------------------------------------------------------

void led_on(){
  char* message = "Blink ON!\n\r";
  UARTSend((uint8_t*)message, strlen(message));
  led_en = 1;
  LPC_GPIO->SET[0] = (0x1<<7);
  // defaults
  led_period = 1000;
  led_duty = 50;
}

void led_off(){
  char* message = "Blink OFF!\n\r";
  UARTSend((uint8_t*)message, strlen(message));
  led_en = 0;
  LPC_GPIO->CLR[0] = (0x1<<7);
}

//------------------------------------------------------
//    Timer Initialization
//------------------------------------------------------


void TIMERInit() {
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);

  // Starting with one timer:
  // The timer CT32B0 has four match registers
  //    and two capture registers
  LPC_IOCON->PIO0_18 &= ~0x07;// I/O Config
  LPC_IOCON->PIO0_18 |=  0x02;// Timer0_32 CAP0

  //External Match Register Config

  LPC_CT32B0->EMR &= ~(0xFF<<4);//Clear EMR
  LPC_CT32B0->EMR |= ((0x3<<4)|(0x3<<6)|(0x3<<8)|(0x3<<10));	

  
  LPC_CT32B0->MR0 = SystemCoreClock/1000-1;//ticks every 1 ms
  LPC_CT32B0->TCR = 0x01;// start the timer(s)
  
  LPC_CT32B0->MCR = 0x03;// interrupt and reset on match
  
  NVIC_EnableIRQ(TIMER_32_0_IRQn);
  NVIC_SetPriority(TIMER_32_0_IRQn, 0);

  return;
}

//------------------------------------------------------
//  Timer IRQ Handler
//------------------------------------------------------

void TIMER32_0_IRQHandler(void) {

  //tick++;
  led_count++;
  
  if((led_count == 1) && (led_en)){
    // new cycle, start the LED
    LPC_GPIO->SET[0] = (0x1<<7);
  }
  else if((led_count == ((led_duty * led_period)/100)) && led_en){
    // toggle the LED off
    LPC_GPIO->CLR[0] = (0x1<<7);
  }
  else if(led_count >= led_period && led_en){
	led_count = 0;
  }

  // The Following Code is from the original ADC portion
  /*
  if(tick == TEN_SEC){
	//LED_OFF;
    tick = 0;
    duty_cycle      = (duty_cycle_mode)?75:25;
    duty_cycle_mode = (duty_cycle_mode)?0:1;
  }

  // if the LED is enabled
  if(led_en){
    // keep track of how long is on
    duty_count++;
    if(duty_count >= time_on){
      // turn the LED off after enough time elapses
      LPC_GPIO->CLR[0] = (0x1<<7);
      led_en = 0;
      duty_count = 0;
    }
  }*/
  LPC_CT32B0->IR = (0x1<<0); //reset interrupt flag
  return;
}
#endif
