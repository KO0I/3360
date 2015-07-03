#ifndef MENU_H_
#define MENU_H_

extern uint32_t state;

//------------------------------------------------------
//    Print out the menus
//------------------------------------------------------

void print_arm_periph_menu(){
  char* message = "\n\rARM Peripheral Control\n\r  1. Control LED\n\r  2. Control ADC\n\r";
    UARTSend( (uint8_t*)message, strlen(message));
}

void print_led_ctrl_menu(){
  char* message = "\n\rLED Control Menu\n\r  1. Blink ON\n\r  2. Blink OFF\n\r  3. Set Frequency\n\r  4. Set Duty Cycle\n\r  5. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_led_freq_menu(){
  char* message = "\n\rLED Frequency Menu\n\r  1. Slow\n\r  2. Medium\n\r  3. Fast\n\r  4. Very Fast\n\r  5. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_led_duty_menu(){
  char* message = "\n\rLED Duty Cycle Menu\n\r  1. 10%\n\r  2. 25%\n\r  3. 50%\n\r  4. 75%\n\r  5. 90%\n\r  6. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_error(){
  char* errmessage = "\n\r\n\rNot a valid option\n\r\n\r";
  UARTSend((uint8_t*)errmessage, strlen(errmessage));
}

//------------------------------------------------------
//    Menu-Specific Functions
//------------------------------------------------------
// Main Control Menu
void arm_periph_menu(uint8_t input){
  switch(input){
    case '1':
      print_led_ctrl_menu();
      state = 1;
      break;
    case '2':
      // For later
      state = 4;
      break;
    default: 
      print_error();
      state = 0;
//      print_arm_periph_menu();
      break;
  }
}
// LED Control Menu
void led_ctrl_menu(uint8_t input){
  switch(input){
    case '1':
      //start led blink
      print_led_ctrl_menu();
      break;
    case '2':
      //stop led blink
      print_led_ctrl_menu();
      break;
    case '3':
      print_led_freq_menu();
      state = 2;
      break;
    case '4':
      print_led_duty_menu();
      state = 3;
      break;
    case '5':
      state = 0;
      print_arm_periph_menu();
/*    default:
      print_error();
      print_led_duty_menu();
      break;*/
  }
}
// LED Frequency Menu
void led_freq_menu(uint8_t input){
  switch(input){
    case '1':
      // slow blink
      print_led_freq_menu();
      break;
    case '2':
      // med blink
      print_led_freq_menu();
      break;
    case '3':
      print_led_freq_menu();
      break;
    case '4':
      print_led_freq_menu();
      break;
    case '5':
      print_led_ctrl_menu();
      state = 1;
      break;
/*    default:
      print_error();
      print_led_freq_menu();
      break;*/
  }
}
// LED Duty Cycle Menu
void led_duty_menu(uint8_t input){
  switch(input){
    case '1':
      print_led_duty_menu();
      break;
    case '2':
      print_led_duty_menu();
      break;
    case '3':
      print_led_duty_menu();
      break;
    case '4':
      print_led_duty_menu();
      break;
    case '5':
      print_led_ctrl_menu();
      state = 1;
      break;
/*    default:
      print_error();
      print_led_duty_menu();
      break;*/
  }
}

//------------------------------------------------------
//    Main FSM
//------------------------------------------------------
void menuControl(char choice){
  arm_periph_menu(choice);
  switch(state){
    case 0: // Main Control
      arm_periph_menu(choice);
      break;
    case 1: // LED Control
      led_ctrl_menu(choice);
      break;
    case 2: // LED Frequency
      led_freq_menu(choice);
      break;
    case 3: // LED Duty Cycle
      led_duty_menu(choice);
      break;
    case 4: // ADC Control
      break;
    case 5: // ADC Report
      break;
  }
}
#endif
