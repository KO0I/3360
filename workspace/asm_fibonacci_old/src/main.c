#include "LPC11Uxx.h"
#include "uart.h"
#include "timer32.h"
#include "gpio.h"
#include "stdio.h"


extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[0x40];
//static uint32_t DebugUpdateCounter = 0;

extern int asm_fibonacci(int x);



// Lookup Table:
unsigned char morse(unsigned char n){
  unsigned int lut[16] = {
// symbol: | 3 bits len | 5 bits symbol |
    0b10111111,   // Value is 0
    0b10101111,   // Value is 1
    0b10100111,
    0b10100011,
    0b10100001,
    0b10100000,
    0b10110000,
    0b10111000,
    0b10111100,
    0b10111110,
    0b01010000,   //  .-      A
    0b10010000,   //  _...    B
    0b10010100,   //  -.-.    C
    0b10001000,   //  .-..    D
    0b00110000,   //  .       E
    0b10000100    //  ..-.    F
  };
  if((n >= 0) || (n <= 16)){
    return lut[n];
  }
  else return -1;
}

unsigned int fibonacci(unsigned int n){
  if(n==0) return 0;
  else if(n==1) return 1;
  else if((n>20)||(n<0)) return 1;
  else{
    return (fibonacci(n-1) + fibonacci(n-2));
  }
}

int main(void) {

	int i;
	uint32_t j;
  UARTInit(9600);

  while(1) {
	j = 0;
    UARTBuffer[j++] = 'b';
    UARTBuffer[j++] = '\r';
    UARTBuffer[j++] = '\n';
    UARTSend( (uint8_t *)UARTBuffer, j );
    printf("%s",UARTBuffer);
  } // end of while loop
    for(i=0; i<22; i++){
    //j = asm_fibonacci(i);
      j = fibonacci(i);
    }
}

