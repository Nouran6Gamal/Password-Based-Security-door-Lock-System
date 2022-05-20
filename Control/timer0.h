/*
 * Module : Timer0
 * File Name: timer0.h
 * Description: Header file for timer0 driver
 *      Author: Nouran Gamal
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#define NULL_PTR ((void*)0)


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer0_Clock;

typedef enum
{
	NORMAL,COMPARE
}Timer0_ModeType;

typedef enum
{
	initialValue
}Timer0_InitialValue;

typedef enum
{
	CTCvalue
}Timer0_CTCValue;
typedef struct
{
	Timer0_Clock clock;
	Timer0_ModeType mode;
	Timer0_InitialValue initialValue;
	Timer0_CTCValue CTCvalue;//p.212

}Timer0_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the Timer0 driver
 * 	1. Set the required clock.
 * 	2. Set the required mode.
 * 	3. Set the initial value.
 * 	4. set compare value in CTC mode.
 */
void Timer0_init(const Timer0_ConfigType * Config_Ptr);


/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void));


/*
 * Description: Function to disable the Timer0
 */
void Timer0_DeInit(void);



#endif /* TIMER0_H_ */
