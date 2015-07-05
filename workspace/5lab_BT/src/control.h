#ifndef CONTROL_H_
#define CONTROL_H_

volatile extern uint32_t led_en;
volatile extern uint32_t led_freq;
volatile extern uint32_t led_duty;
volatile extern uint32_t led_count;
volatile extern uint32_t led_period;

volatile extern uint32_t adc_en;
volatile extern uint32_t adc_count;
volatile extern uint32_t adc_period;

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
  adc_count++;
  if(led_en){ 
    if(led_count == 1){
      // new cycle, start the LED
      LPC_GPIO->SET[0] = (0x1<<7);
    }
    else if(led_count == ((led_duty * led_period)/100)){
      // toggle the LED off
      LPC_GPIO->CLR[0] = (0x1<<7);
    }
    else if(led_count >= led_period){
    led_count = 0;
    }
  }
/*
  if(adc_en){
    if(adc_count >= adc_period){
      // from adc.h
      //ADCRead(0);
      //float adc_meas = (3.3*ADCRead(0))/2047;
    	float adc_meas = 0;
      char  adc_ascii[10];
      sprintf(adc_ascii, "%.5f", adc_meas);
      char* adc_report = "ADC reports: ";
      UARTSend((uint8_t*)adc_report, strlen(adc_report));

      UARTSend((uint8_t*)adc_ascii, strlen(adc_ascii));

      char* adc_unit   = "[V]\n\r";
      UARTSend((uint8_t*)adc_unit, strlen(adc_unit));
    }
  }*/

  LPC_CT32B0->IR = (0x1<<0); //reset interrupt flag
  return;
}
#endif
