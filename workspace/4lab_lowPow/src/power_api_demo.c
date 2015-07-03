/*****************************************************************************
 *   blinky.c:  LED blinky C file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.12.07  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/

#include "driver_config.h"
#include "target_config.h"
#include "rom_drivers.h"
#include "pmu.h"
#include "gpio.h"
//#include "LPC11Uxx.h"

unsigned int command[5], result[5];             //command and result arrays
const ROM ** rom = (const ROM **) 0x1FFF1FF8;

volatile unsigned long int i;                   //counter variable
volatile unsigned long int j, k;				//counters vars for blinking loop
volatile unsigned long int wake_cycles = 0;

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
    msTicks++;
}

void delay_ms(uint32_t ms) {
    uint32_t now = msTicks;
    while ((msTicks-now) < ms);
}

int fib(int n)
{
    int c;

    if (n == 0)
        return 0;
    if (n == 1)
	return 1;

    c = fib(n-2) + fib(n-1);

    return c;
}

int main (void)
{
	GPIOInit();
	SysTick_Config(SystemCoreClock/1000);// from CMSIS template
	GPIOSetDir( 0, 7, 1 );
    GPIOSetBitValue( 0, 7, 1 );
    for (i = 0; i != 10; i++);
    GPIOSetBitValue( 0, 7, 0 );
    if((*rom)->pPWRD == (void *)0xFFFFFFFF)
    {
    	// This LPC does not have the power API
    	while(1);
    }

    LPC_SYSCON->SYSAHBCLKCTRL = (0xFFFFFFFF & (~(1<<15))); //enable all clocks except the WDT

    /* user must select correct PLL input source before calling power/pll routines */
    LPC_SYSCON->PDRUNCFG &= ~(1<<5);            //power-up the system oscillator
    for (i = 0; i != 24000; i++);               //wait for it to stabilize
    LPC_SYSCON->SYSPLLCLKSEL = 0x01;            //system PLL source is the system oscillator
    LPC_SYSCON->SYSPLLCLKUEN = 0x00;            //update the system PLL source...
    LPC_SYSCON->SYSPLLCLKUEN = 0x01;            //...
    LPC_SYSCON->MAINCLKSEL = 0x01;              //main clock source is the PLL input
    LPC_SYSCON->MAINCLKUEN = 0x00;              //update the main clock source...
    LPC_SYSCON->MAINCLKUEN = 0x01;              //...

    LPC_SYSCON->CLKOUTCLKSEL = 0x03;            //CLKOUT = main clock
    LPC_SYSCON->CLKOUTUEN = 0x01;               //update CLKOUT selection...
    LPC_SYSCON->CLKOUTUEN = 0x00;               //...
    LPC_SYSCON->CLKOUTUEN = 0x01;               //...
    LPC_SYSCON->CLKOUTDIV = 10;                 //generate ouptut @ 1/10 rate

    LPC_IOCON->PIO0_1 &= ~0x07;                 //select CLKOUT @ PIO0_1...
    LPC_IOCON->PIO0_1 |= 1;                     //...

	//configure CT16B1_MAT0 as a system/10 clock out (P0_21)
//	LPC_IOCON->PIO0_21 = (LPC_IOCON->PIO0_21 & ~0x7) | 1;	//select CT16B1_MAT0 @ P0_21
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);           	//enable CT16B1 clock
	LPC_TMR16B1->TCR	= 0x00;						//stop the timer
	LPC_TMR16B1->TCR	= 0x02;						//reset the timer
	LPC_TMR16B1->TCR	= 0x00;						//release the reset
	LPC_TMR16B1->CTCR	= 0x00;						//count on peripheral clock rising edges only
  	LPC_TMR16B1->PR		= 0;						//max rate (no prescaler)
	LPC_TMR16B1->MR0 	= 10/2-1;					//match output = 1/10 timer's clock
  	LPC_TMR16B1->MCR	= 1<<1;						//reset on MR0
  	LPC_TMR16B1->EMR	= 3<<4;						//toggle MAT0
	LPC_TMR16B1->TCR	= 0x01;						//let the timer run

    /* user must select the correct operating frequency before setting up the PLL   */
    /* or the voltage regulator and the flash interface setup might not be able     */
    /* to support application running at higher frequencies                         */
    command[0] = 48;                            //system freq 48 MHz
//    command[1] = PARAM_DEFAULT;                 //specify system power to default
//    command[1] = PARAM_CPU_EXEC;                //specify system power for cpu performance run
//    command[1] = PARAM_EFFICIENCY;              //specify system power for efficiency
    command[1] = PARAM_LOW_CURRENT;             //specify system power for low active current
    (*rom)->pPWRD->set_power(command,result);   //set system power
    if (result[0] != PARAM_CMD_CUCCESS){        //if a failure is reported...
        while(1);                               //... stay in the loop
    }

    /* the pll setup routine is searching for a setup based on the specified input  */
    /* and output frequency and after setting up the main PLL switches main clock   */
    /* source from PLL in to PLL out                                                */
    command[0] = 12000;                         //PLL's input freq 12000
    command[1] = 48000;                         //CPU's freq 48000
    command[2] = CPU_FREQ_EQU;                  //specify exact frequency
    command[3] = 0;                             //infinitely wait for the PLL to lock
    (*rom)->pPWRD->set_pll(command,result);     //set the PLL
    if ((result[0] != PLL_CMD_CUCCESS)){        //if a failure is reported...
        while(1);                               //... stay in the loop
    }

    /* before changing the PLL setup main clock source must be switched from        */
    /* PLL in to PLL out!!!                                                         */
    while(1){
        //48 MHz setup begin
        LPC_SYSCON->MAINCLKSEL = 0x01;              //main clock source is the PLL input
        LPC_SYSCON->MAINCLKUEN = 0x00;              //update the main clock source...
        LPC_SYSCON->MAINCLKUEN = 0x01;              //...
        for (i = 0; i != 10000; i++);               //wait for a while
        command[0] = 48;                            //system freq 48 MHz
        command[1] = PARAM_LOW_CURRENT;             //specify system power for low active current
        (*rom)->pPWRD->set_power(command,result);   //set system power
        if (result[0] != PARAM_CMD_CUCCESS){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        command[0] = 12000;                         //PLL's input freq 12000
        command[1] = 48000;                         //CPU's freq 48000
        command[2] = CPU_FREQ_EQU;                  //specify exact frequency
        command[3] = 0;                             //infinitely wait for the PLL to lock
        (*rom)->pPWRD->set_pll(command,result);     //set the PLL
        if ((result[0] != PLL_CMD_CUCCESS)){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        //for (i = 0; i != 5000000; i++);
        fib(30);
        GPIOSetBitValue( 0, 7, 1 );
        //for (i = 0; i != 5000000; i++)
        delay_ms(1000);
        GPIOSetBitValue( 0, 7, 0 );
        //48 MHz setup end

        //24 MHz setup begin
        LPC_SYSCON->MAINCLKSEL = 0x01;              //main clock source is the PLL input
        LPC_SYSCON->MAINCLKUEN = 0x00;              //update the main clock source...
        LPC_SYSCON->MAINCLKUEN = 0x01;              //...
        for (i = 0; i != 10000; i++);               //wait for a while
        command[0] = 24;                            //system freq 24 MHz
        command[1] = PARAM_LOW_CURRENT;             //specify system power for low active current
        (*rom)->pPWRD->set_power(command,result);   //set system power
        if (result[0] != PARAM_CMD_CUCCESS){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        command[0] = 12000;                         //PLL's input freq 12000
        command[1] = 24000;                         //CPU's freq 24000
        command[2] = CPU_FREQ_EQU;                  //specify exact frequency
        command[3] = 0;                             //infinitely wait for the PLL to lock
        (*rom)->pPWRD->set_pll(command,result);     //set the PLL
        if ((result[0] != PLL_CMD_CUCCESS)){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        //for (i = 0; i != 2500000; i++);
        fib(30);
        GPIOSetBitValue( 0, 7, 1 );
        //for (i = 0; i != 2500000; i++);
        delay_ms(1000/2);
        GPIOSetBitValue( 0, 7, 0 );
        //24 MHz setup end

        //18 MHz setup begin
        LPC_SYSCON->MAINCLKSEL = 0x01;              //main clock source is the PLL input
        LPC_SYSCON->MAINCLKUEN = 0x00;              //update the main clock source...
        LPC_SYSCON->MAINCLKUEN = 0x01;              //...
        for (i = 0; i != 10000; i++);               //wait for a while
        command[0] = 18;                            //system freq 18 MHz
        command[1] = PARAM_LOW_CURRENT;             //specify system power for low active current
        (*rom)->pPWRD->set_power(command,result);   //set system power
        if (result[0] != PARAM_CMD_CUCCESS){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        command[0] = 12000;                         //PLL's input freq 12000
        command[1] = 18000;                         //CPU's freq 18000
        command[2] = CPU_FREQ_EQU;                  //specify exact frequency
        command[3] = 0;                             //infinitely wait for the PLL to lock
        (*rom)->pPWRD->set_pll(command,result);     //set the PLL
        if ((result[0] != PLL_CMD_CUCCESS)){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        //for (i = 0; i != 1875000; i++);
        fib(30);
        GPIOSetBitValue( 0, 7, 1 );
        //for (i = 0; i != 1875000; i++);
        delay_ms(1000/4);
        GPIOSetBitValue( 0, 7, 0 );
        //18 MHz setup end


        //3 MHz setup begin
        LPC_SYSCON->MAINCLKSEL = 0x01;              //main clock source is the PLL input
        LPC_SYSCON->MAINCLKUEN = 0x00;              //update the main clock source...
        LPC_SYSCON->MAINCLKUEN = 0x01;              //...
        for (i = 0; i != 10000; i++);               //wait for a while
        command[0] = 3;                             //system freq 3 MHz
        command[1] = PARAM_LOW_CURRENT;             //specify system power for low active current
        (*rom)->pPWRD->set_power(command,result);   //set system power
        if (result[0] != PARAM_CMD_CUCCESS){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        command[0] = 12000;                         //PLL's input freq 12000
        command[1] = 3000;                          //CPU's freq 3000
        command[2] = CPU_FREQ_EQU;                  //specify exact frequency
        command[3] = 0;                             //infinitely wait for the PLL to lock
        (*rom)->pPWRD->set_pll(command,result);     //set the PLL
        if ((result[0] != PLL_CMD_CUCCESS)){        //if a failure is reported...
            while(1);                               //... stay in the loop
        }
        //for (i = 0; i != 312500; i++);
        fib(30);
        GPIOSetBitValue( 0, 7, 1 );
        //for (i = 0; i != 312500; i++);
        delay_ms(1000/16);
        GPIOSetBitValue( 0, 7, 0 );
        //3 MHz setup end

        PMU_Sleep(2,0);

        wake_cycles++;

        for(j=0; j<=wake_cycles; j++){
        	GPIOSetBitValue( 0, 7, 1 );
        	//LPC_GPIO->SET[0] = (1<<7);
        	//for (k = 0; k != 312500; k++);
        	delay_ms(1000/16);
        	GPIOSetBitValue( 0, 7, 0 );
        	delay_ms(500/16);
        	//LPC_GPIO->CLR[0] = (1<<7);
        }

        // wake
        PMU_Init();
    }
}

