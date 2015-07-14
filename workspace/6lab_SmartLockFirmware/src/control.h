#ifndef CONTROL_H_
#define CONTROL_H_

volatile extern uint32_t led_en;
volatile extern uint32_t led_freq;
volatile extern uint32_t led_duty;
volatile extern uint32_t led_count;
volatile extern uint32_t led_period;

//volatile extern uint32_t motor_en;
volatile extern uint32_t motor_count;
volatile extern uint32_t motor_en_count;
volatile extern uint32_t motor_duty;
volatile extern uint32_t motor_period;
volatile extern uint32_t motor_runTime;

//------------------------------------------------------
//    Peripheral Control 
//------------------------------------------------------

void lock(){
  motor_duty = 20;
  //motor_runTime = 1000;
  motor_count = 0;
  motor_en_count = 0;
  // blink the LED to indicate locked state
  led_en = 1;
  LPC_GPIO->SET[0] = (0x1<<7);
  led_period = 5000;
  led_duty = 1;
}

void unlock(){
  motor_duty = 70;
  //motor_runTime = 1000;
  motor_count = 0;
  motor_en_count = 0;
  // if unlocked, don't blink
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
  LPC_CT32B0->MR0 = SystemCoreClock/100000-1;//ticks every 1/100 ms
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
  led_count++;
  motor_count++;
  motor_en_count++;
  /*if(led_en){
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
  }*/
  if(motor_en_count <= motor_runTime){
    if(motor_count == 1){
        // new cycle, start the motor signal
        LPC_GPIO->SET[0] = (0x1<<1);
      }
      else if(motor_count == ((motor_duty * motor_period)/100)){
        // toggle the motor signal off
        LPC_GPIO->CLR[0] = (0x1<<1);
      }
      else if(motor_count >= motor_period){
      motor_count = 0;
    }
  }
  else LPC_GPIO->CLR[0] = (0x1<<1);
  LPC_CT32B0->IR = (0x1<<0); //reset interrupt flag
  return;
}
#endif
