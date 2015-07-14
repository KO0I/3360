#ifndef MENU_H_
#define MENU_H_

extern uint32_t state;

//------------------------------------------------------
//    Print out the menus
//		Later: this may serve as the means by
//		which data is fed back to Android app
//------------------------------------------------------

void print_locked_menu(){
  char* message;
  if(state == 0){
	  message = "\n\rLocked\n\r";
  }
  else if(state == 1){
	  message = "\n\rAlready Locked\n\r";
  }
  UARTSend( (uint8_t*)message, strlen(message));
}

void print_unlocked_menu(){
	char* message;
	if(state == 1) message = "\n\rUnlocked\n\r";
	else if(state == 0) message = "\n\rAlready Unlocked\n\r";
  UARTSend( (uint8_t*)message, strlen(message));
}

void print_error(){
  char* errmessage = "\n\r\n\rNot a valid option\n\r\n\r";
  UARTSend((uint8_t*)errmessage, strlen(errmessage));
}

//------------------------------------------------------
//    Menu-Specific Functions
//------------------------------------------------------

void locked_menu(uint8_t input){
  switch(input){
   case '1':
	 // Already Locked
     print_locked_menu();
     state = 1;
     break;
   case '0':
	 unlock();
	 print_unlocked_menu();
	 state = 0;
	 break;
   default:
	 print_error();
	 break;
  }
}

void unlocked_menu(uint8_t input){
  switch(input){
   case '1':
	 lock();
     print_locked_menu();
     state = 1;
     break;
   case '0':
	 // Already Unlocked
	 print_unlocked_menu();
	 state = 0;
	 break;
   default:
	 print_error();
	 break;
  }
}

//------------------------------------------------------
//    Main FSM
//------------------------------------------------------
void menuControl(char choice){
  //arm_periph_menu(choice);
  switch(state){
    case 0: // Unlocked
      unlocked_menu(choice);
      break;
    case 1: // Locked
      locked_menu(choice);
      break;
  }
}
#endif
