/****************************************************************************
 *   $Id:: adctest.c 4357 2010-08-20 00:04:26Z usb00423                     $
 *   Project: NXP LPC11Uxx ADC example
 *
 *   Description:
 *     This file contains ADC test modules, main entry, to test ADC APIs.
 *
*
****************************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.

* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.

****************************************************************************/

// Forced ADC to sample a single input, and then attempted to add an averaging
// component to the UpdateValues() function
// gpio, stdio, and timer32 are included in this to toggle lights,
// print and run a timer

// Current problems: ADCMax, ADCMin and ADCMean are not producing values that
// make sense.

#include "LPC11Uxx.h"                        /* LPC11xx definitions */
#include "adc.h"
#if ADC_DEBUG
#include "uart.h"
#include "timer32.h"
#include "gpio.h"
#include "stdio.h"
#define ADC_NUM 0 		// forcing the ADC to only sample one input
#endif

extern volatile uint32_t ADCValue[ADC_NUM];
extern volatile uint32_t ADCIntDone;
extern volatile uint32_t OverRunCounter;
extern volatile uint32_t timer32_1_counter[4];

volatile uint32_t ADCMinValue[ADC_NUM];
volatile uint32_t ADCMaxValue[ADC_NUM];
volatile uint32_t ADCMeanValue;
volatile uint32_t period1 = 0;
volatile uint32_t period2 = 0;
volatile uint32_t tick = 1;
float frequency;
//ADCMaxValue[0] = 1023;
//ADCMinValue[0] = 0;
volatile uint32_t ADCConversionCounter = 0;
volatile uint32_t ADCConversionBurstCounter = 0;

#if ADC_DEBUG
extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];
static int32_t ClearCounter = ADC_DEBUG_CLEAR_CNT;
static uint32_t DebugUpdateCounter = 0;


static uint8_t ConvertDigital ( uint8_t digit )
{
  static uint8_t hex[] = "0123456789ABCDEF";
  return hex[digit & 0xf];
}

/*****************************************************************************
** Function name:   PrintoutADCValue
**
** Descriptions:    Dump ADC reading to the UART
**
** parameters:      None
** Returned value:    None
**
*****************************************************************************/
static void PrintoutADCValue( void )
{
 uint32_t i, j = 0;

  /* Bring cursor to home on terminal, write headers */
  UARTBuffer[j++] = 'C';
  UARTBuffer[j++] = 'h';
  UARTBuffer[j++] = ' ';
  UARTBuffer[j++] = 'C';
  UARTBuffer[j++] = 'U';
  UARTBuffer[j++] = 'R';
  UARTBuffer[j++] = ' ';
  UARTBuffer[j++] = 'M';
  UARTBuffer[j++] = 'I';
  UARTBuffer[j++] = 'N';
  UARTBuffer[j++] = ' ';
  UARTBuffer[j++] = 'M';
  UARTBuffer[j++] = 'A';
  UARTBuffer[j++] = 'X';
  UARTBuffer[j++] = '\r';
  UARTBuffer[j++] = '\n';
  UARTSend( (uint8_t *)UARTBuffer, j );
  //printf("%s", UARTBuffer);
  /* Update current, min, and max values on terminal */
  for ( i = 0; i < 1; i++ )
  {
    j = 0;
  UARTBuffer[j++] = ConvertDigital(i);
  UARTBuffer[j++] = ' ';
    UARTBuffer[j++] = ConvertDigital( (uint8_t)((ADCValue[i]>>8)&0xF));
    UARTBuffer[j++] = ConvertDigital( (uint8_t)((ADCValue[i]>>4)&0xF));
    UARTBuffer[j++] = ConvertDigital( (uint8_t)(ADCValue[i]&0xF));
    UARTBuffer[j++] = ' ';
    UARTBuffer[j++] = ConvertDigital( (uint8_t)((ADCMinValue[i]>>8)&0xF));
    UARTBuffer[j++] = ConvertDigital( (uint8_t)((ADCMinValue[i]>>4)&0xF));
    UARTBuffer[j++] = ConvertDigital( (uint8_t)(ADCMinValue[i]&0xF));
    UARTBuffer[j++] = ' ';
    UARTBuffer[j++] = ConvertDigital( (uint8_t)((ADCMaxValue[i]>>8)&0xF));
    UARTBuffer[j++] = ConvertDigital( (uint8_t)((ADCMaxValue[i]>>4)&0xF));
    UARTBuffer[j++] = ConvertDigital( (uint8_t)(ADCMaxValue[i]&0xF));
    UARTBuffer[j++] = '\r';
    UARTBuffer[j++] = '\n';
    UARTSend( (uint8_t *)UARTBuffer, j );
    // THIS PRINTF WORKS
    //printf("%s", UARTBuffer);
  }

  /* Show number of samples until next clear */
  j=0;
  UARTBuffer[j++] = 'N';
  UARTBuffer[j++] = 'o';
  UARTBuffer[j++] = ' ';
  UARTBuffer[j++] = 'o';
  UARTBuffer[j++] = 'f';
  UARTBuffer[j++] = ' ';
  UARTBuffer[j++] = 'S';
  UARTBuffer[j++] = 'a';
  UARTBuffer[j++] = 'm';
  UARTBuffer[j++] = 'p';
  UARTBuffer[j++] = 'l';
  UARTBuffer[j++] = 'e';
  UARTBuffer[j++] = 's';
  UARTBuffer[j++] = ':';
  UARTBuffer[j++] = ' ';
  UARTBuffer[j++] = ConvertDigital( (uint8_t)((ClearCounter>>8)&0xF));
  UARTBuffer[j++] = ConvertDigital( (uint8_t)((ClearCounter>>4)&0xF));
  UARTBuffer[j++] = ConvertDigital( (uint8_t)(ClearCounter&0xF));
  UARTBuffer[j++] = '\r';
  UARTBuffer[j++] = '\n';
  UARTBuffer[j++] = '\n';
  UARTSend( (uint8_t *)UARTBuffer, j );
 //printf("%s", UARTBuffer);
  return;
}
#endif

/*****************************************************************************
** Function name:   ClearStats
**
** Descriptions:    Clear ADC statistics
**
** parameters:      None
** Returned value:    None
**
*****************************************************************************/
static void ClearStats(void)
{
  int i;
  for ( i = 0; i < ADC_NUM; i++ )
  {
    ADCMinValue[i] = 0x3ff;
    ADCMaxValue[i] = 0;
  }
}

/*****************************************************************************
** Function name:   UpdateStats
**
** Descriptions:    Update ADC statistics
**
** parameters:      None
** Returned value:    None
**
*****************************************************************************/
static void UpdateStats(void)
{
  int i;
  for ( i = 0; i < ADC_NUM; i++ )
  {
    if ( ADCValue[i] < ADCMinValue[i] ){
     ADCMinValue[i] = ADCValue[i];
    }
   if ( ADCValue[i] > ADCMaxValue[i] ){
     ADCMaxValue[i] = ADCValue[i];
   }
  }
  ADCMeanValue = (ADCMaxValue[i]-ADCMinValue[i])>>1;
  //ADCMeanValue = 321;
  //printf("ADC Mean Value: %d\n", ADCMeanValue);

}

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{

  init_timer32(0, TIME_INTERVAL); // there are two 32-bit timers: 0 and 1
  enable_timer32(0);



  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); // enable AHB clock to GPIO

  GPIOSetDir( 0, 7, 1 );		// set direction for port 7
  ADCMaxValue[0] = 1;			// set max value to a tiny number
  ADCMinValue[0] = 1023;		// set min value to a huge number
  ADCMeanValue = 321;			// set mean value to a reasonable number
#if !BURST_MODE
  uint32_t i;
#endif
  SystemCoreClockUpdate();

#if ADC_DEBUG
  /* NVIC is installed inside UARTInit file. */
  UARTInit(9600);
#endif
  ClearStats();

  /* Initialize ADC  */
  ADCInit( ADC_CLK );

  while ( 1 )
  {
#if BURST_MODE        /* Interrupt driven only */
    /* Burst mode */
    ADCBurstRead();
    while ( !ADCIntDone );
    ADCIntDone = 0;
    if ( OverRunCounter != 0 )
    {
     while ( 1 );
    }
    ADCConversionBurstCounter++;
    UpdateStats();
#else
    /* Non burst mode, get ADC from all channels. */
    for ( i = 0; i < 1; i++ )
    {
#if ADC_INTERRUPT_FLAG        /* Interrupt driven */
     ADCRead( i );
     while ( !ADCIntDone );
     ADCIntDone = 0;
     if ( OverRunCounter != 0 )
      while ( 1 );

#else
     ADCValue[i] = ADCRead( i );  /* Polling */
     //ADCMeanValue = (ADCMaxValue[0]-ADCMinValue[0])>>1;
     if (ADCValue[0] >= ADCMeanValue){
      GPIOSetBitValue( 0, 7, 1 );
      if(tick){//start of period
    	  period1 = timer32_1_counter[0]; // get current time
    	  tick = ~tick;
      }
      else if(!tick){//start of next period
    	  period2 = timer32_1_counter[0]; // get time on the next period
    	  tick = ~tick;
    	  frequency = 1/(period2-period1);
    	  //printf("Frequency: %d",frequency);
      }
     }
     else  {
      if(ADCValue[0] < ADCMeanValue){
        GPIOSetBitValue( 0, 7, 0 );
      }
     }

#endif
     ADCConversionCounter++;
   }
    UpdateStats();
#endif

#if ADC_DEBUG
    if (DebugUpdateCounter++ >= ADC_DEBUG_UPDATE_CNT)
    {
      if (ClearCounter-- < 0)
      {
        ClearStats();
        ClearCounter = ADC_DEBUG_CLEAR_CNT;
      }
      PrintoutADCValue();
    }
#endif
  int j = 0;
  UARTBuffer[j++] = 'a';
  UARTBuffer[j++] = '\r';
  UARTBuffer[j++] = '\n';
  UARTSend( (uint8_t *)UARTBuffer, j );
  printf("%s",UARTBuffer);
  DebugUpdateCounter = 0;
  }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
