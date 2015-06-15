#include "LPC11Uxx.h"
#include "uart.h"
#include "timer32.h"
#include "gpio.h"
#include "stdio.h"

#define DIT 100
#define DAH 4*DIT
uint8_t wasDit = 0; // helps make the Morse look more natural

// UART for debugging -------------------------------------------------
extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[0x40];
//static uint32_t DebugUpdateCounter = 0;

// TIMER SETUP --------------------------------------------------------
#define TEST_TIMER_NUM		0		/* 0 or 1 for 32-bit timers only */

extern volatile uint32_t timer32_0_counter[4];
extern volatile uint32_t timer32_1_counter[4];

// FROM CMSIS TEMPLATE
volatile uint32_t msTicks = 0;

// Lookup Table that maps numbers to a Morse code symbol
static uint8_t mlut[16] = { // Morse Code Lookup Table
  // the format of the symbol is as follows:
  // first three bits indicate the length (len) of the symbol.
  // The (len) most significant bits compose the morse symbol.
  // The unused bits are zeros. Ones represent a long pulse (dah)
  // and zeros represent a short pulse (dit). The following example
  // shows the encoding for the decimal number 3:
  //
  //      |  len  |    sym    |
  //  Bin | 1 0 1 | 0 0 0 1 1 |
  //  Dec |  (5)  |    (3)    |
  //  Mor |  N/A  | . . . - - |
  //  
  //
    0b10111111,   //  -----   0 
    0b10101111,   //  .----   1
    0b10100111,	  //  ..---   2
    0b10100011,	  //  ...--   3
    0b10100001,	  //  ....-   4
    0b10100000,	  //  .....   5
    0b10110000,	  //  -....   6
    0b10111000,	  //  --...   7
    0b10111100,	  //  ---..   8
    0b10111110,	  //  ----.   9
    0b01001000,   //  .-      A
    0b10010000,   //  _...    B
    0b10010100,   //  -.-.    C
    0b01110000,   //  -..     D
    0b00100000,   //  .       E
    0b10000100    //  ..-.    F
};

// The two following functions are part of a
// CMSIS-based delay.
// STRETCH GOAL: replace with interrupts.

void SysTick_Handler(void) {
    msTicks++;
}

void delay_ms(uint32_t ms) {
    uint32_t now = msTicks;
    while ((msTicks-now) < ms);
}

// Recursive Fibonacci code written in assembly
//extern int asm_fibonacci_marisa(int x);

extern int asm_fib(int x);

extern int asm_fibonacci(int x);

// From ADC Example
static uint8_t ConvertDigital ( uint8_t digit )
{
  static uint8_t hex[] = "0123456789ABCDEF";
  return hex[digit & 0xf];
}

// Let m be the result of a known working function
// Let n be the result of the function being tested
// Note that this uses up the UART buffer!
uint32_t print32bitCompare(uint32_t m, uint32_t n, uint32_t buffer){
  // pass this function a 32-bit number, and this will product a
  // useable value on the UART buffer
  UARTBuffer[buffer++] = 'i';
  UARTBuffer[buffer++] = 'd';
  UARTBuffer[buffer++] = 'e';
  UARTBuffer[buffer++] = 'a';
  UARTBuffer[buffer++] = 'l';
  UARTBuffer[buffer++] = ':';
  UARTBuffer[buffer++] = ConvertDigital((uint8_t)((m>>12)&0xF));
  UARTBuffer[buffer++] = ConvertDigital( (uint8_t)((m>>8)&0xF));
  UARTBuffer[buffer++] = ConvertDigital( (uint8_t)((m>>4)&0xF));
  UARTBuffer[buffer++] = ConvertDigital((uint8_t)(m&0xF));
  UARTBuffer[buffer++] = ',';
  UARTBuffer[buffer++] = ' ';
  UARTBuffer[buffer++] = 'r';
  UARTBuffer[buffer++] = 'e';
  UARTBuffer[buffer++] = 'a';
  UARTBuffer[buffer++] = 'l';
  UARTBuffer[buffer++] = ':';
  UARTBuffer[buffer++] = ConvertDigital((uint8_t)((n>>12)&0xF));
  UARTBuffer[buffer++] = ConvertDigital( (uint8_t)((n>>8)&0xF));
  UARTBuffer[buffer++] = ConvertDigital( (uint8_t)((n>>4)&0xF));
  UARTBuffer[buffer++] = ConvertDigital((uint8_t)(n&0xF));
  UARTBuffer[buffer++] = '\r';
  UARTBuffer[buffer++] = '\n';
  UARTSend( (uint8_t *)UARTBuffer, buffer );
  printf("%s",UARTBuffer);
  return buffer;
}

// note: write a printUint32 function for later, could come in handy

void printchar(uint8_t c){
  // prints a character
  uint8_t j = 0;
  UARTBuffer[j++] = 'c';
  UARTBuffer[j++] = ':';
  UARTBuffer[j++] = ' ';
  UARTBuffer[j++] = ConvertDigital(c);
  UARTBuffer[j++] = '\r';
  UARTBuffer[j++] = '\n';
  UARTSend( (uint8_t *)UARTBuffer, j );
  printf("%s",UARTBuffer);
}

void dit(void){
  // short pulse (1 or '.')
  GPIOSetBitValue( 0, 7, 1 );
  delay_ms(DIT);
  GPIOSetBitValue( 0, 7, 0 );
  // By manipulating the delay based on what was in use,
  // it might be possible to emulate different keyers
  // (straight key, iambic, vibroflex bug, etc)
  delay_ms(DIT /*/ ((wasDit)?2:1)*/);
  wasDit = 1;
}
void dah(void){
  // long pulse (0 or '-')
  GPIOSetBitValue( 0, 7, 1 );
  delay_ms(DAH);
  GPIOSetBitValue( 0, 7, 0 );
  delay_ms(DIT); // the space b/n letters is always DIT
  wasDit = 0;
}
void rest(void){
  // A space between letters in a word
  GPIOSetBitValue( 0, 7, 0 );
  delay_ms(DAH);
  wasDit = 0;
}

void endWord(void){
	// separate words by seven dits
  // also a handy "long pause"
	GPIOSetBitValue( 0, 7, 0);
	delay_ms(DAH);
	wasDit = 0;
}

void cwblink8(uint8_t n){	// blinks out the Morse code for a single character
  uint8_t len;
  uint8_t i;
  if((n < 128) && (n >= 64)){ // only indicates 01x
    len = ((n>>5)&1) ? 3:2;           // DOUBLE CHECK BIT-SELECT
  }
  else if((n < 64) && (n <= 32)){
    len = 1;
  }
  else len = n >> 5; 	// upper three bits is length
 
  for(i=0; i<len; i++){
	  ((n >> (4-i)) & 1) ? dah():dit();
  }
  rest();
  // Extra delay between words
  //int WAITFACTR = 3;
  //int j;
  //for(j=WAITFACTR;j>=0;j--){
      endWord();
  //} //end of extra delay loop
}

void cwblink32 ( uint32_t n){
  // n is split into four bytes that are then passed
  // to cwblink88, which blinks out a sequence corresponding
  // to Morse characters
  // leading zeros are ignored
  if(n<=0xF){
    cwblink8(mlut[(uint8_t)n]);
  }
  else if((n>0xF) && (n<=0xFF)){
    if((n>>4)&0xF)  cwblink8(mlut[(uint8_t)((n>>4)&0xF)]);
    cwblink8(mlut[(uint8_t)n&0xF]);
  }
  else if((n>0xFF) && (n<0xFFF)){
    if((n>>8)&0xF)  cwblink8(mlut[(uint8_t)((n>>8)&0xF)]);
    if((n>>4)&0xF)  cwblink8(mlut[(uint8_t)((n>>4)&0xF)]);
  }
  else if((n>0xFFF) && (n<0xFFFF)){
    if((n>>12)&0xF) cwblink8(mlut[(uint8_t)((n>>12)&0xF)]);
    if((n>>8)&0xF)  cwblink8(mlut[(uint8_t)((n>>8)&0xF)]);
    if((n>>4)&0xF)  cwblink8(mlut[(uint8_t)((n>>4)&0xF)]);
    cwblink8(mlut[(uint8_t)n&0xF]);
  }
}

// Simple Fibonacci Code to use until assembly is debugged
uint32_t fibonacci(uint32_t n){
  if(n==0) return 0;
  else if(n==1) return 1;
  else if((n>20)||(n<0)) return 1;
  else{
    return (fibonacci(n-1) + fibonacci(n-2));
  }
}

int main(void) {

  SystemInit(); // from CMSIS template
  SystemCoreClockUpdate(); // from timer code
  SysTick_Config(SystemCoreClock/1000);// from CMSIS template

  uint32_t i,j,m,n;
  UARTInit(9600);

  /* TEST_TIMER_NUM is either 0 or 1 for 32-bit timer 0 or 1. */
  init_timer32(TEST_TIMER_NUM, TIME_INTERVAL);
  enable_timer32(TEST_TIMER_NUM);

  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

  /* Set port 0_7 to output */
  GPIOSetDir( 0, 7, 1 );


  for(i=0; i<21; i++){
    j = 0;
    //n = asm_fibonacci(i);
    m = fibonacci(i);
    n = fib(i);
    //n = asm_fibonacci(i);
    print32bitCompare(m,n,j);
    // the encoding is Morse
    // the output signal is CW
    //cwblink32(n);
  }
return 0;
}

