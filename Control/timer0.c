/*
 * Module : Timer0
 * File Name: timer0.c
 * Description: Source file for timer0 driver
 *      Author: Nouran Gamal
 */
#include "timer0.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)//normal mode interrupt service routine
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the Timer0 driver
 * 	1. Set the required clock.
 * 	2. Set the required mode.
 * 	3. Set the initial value.
 * 	4. set compare value in CTC mode.
 */
void Timer0_init(const Timer0_ConfigType * Config_Ptr )
{
	if(Config_Ptr->mode == NORMAL){
		/* Initial Value for Timer0 */
		TCNT0 = Config_Ptr->initialValue;
		/*
		 * insert the required clock value in the first three bits (CS00, CS01 and CS02)
		 * of TCCR0 Register
		 */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);
		TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
		/* Configure the timer control register
		 * 1. Non PWM mode FOC0=1
		 * 2. Normal Mode WGM01=0 & WGM00=0
		 * 3. Normal Mode COM00=0 & COM01=0
		 */
		TCCR0 = (1<<FOC0) ;
	}


	if(Config_Ptr->mode == COMPARE){
		/* Initial Value for Timer0 */
		TCNT0 = Config_Ptr->initialValue;

		/* compare Value for Timer0 */
		OCR0 = Config_Ptr->CTCvalue;
		/*
		 * insert the required clock value in the first three bits (CS00, CS01 and CS02)
		 * of TCCR0 Register
		 */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);

		TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
		/* Configure timer0 control register
		 * 1. Non PWM mode FOC0=1
		 * 2. CTC Mode WGM01=1 & WGM00=0
		 * 3. No need for OC0 in this example so COM00=0 & COM01=0
		 */
		TCCR0 = (1<<FOC0) | (1<<WGM01) ;
	}
}

	/*
	 * Description: Function to set the Call Back function address.
	 */
	void Timer0_setCallBack(void(*a_ptr)(void))
	{
		/* Save the address of the Call back function in a global variable */
		g_callBackPtr = a_ptr;
	}


	/*
	 * Description: Function to disable the Timer0
	 */
	void Timer0_DeInit(void)
	{
		/* Clear All Timer0 Registers */
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;

		/* Disable the Timer overflow interrupt & output compare match interrupt*/
		TIMSK &= ~(1<<TOIE0);
		TIMSK &= ~(1<<OCIE0);

	}
