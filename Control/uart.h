 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Nouran Gamal
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#define NULL_PTR ((void*)0)


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	fiveBit,sixBit,sevenBit,eightBit

}UART_BitData;//UCSZ0,1 in UCSRC reg 5bit=00 ,6bit=01,7bit=10,8bit=11


typedef enum
{
	otherMode,nineBitMode //UCSZ2 in UCSRB reg =1(9bit)/=0(5,6,7,8bit)
}UART_BitDataMode;

typedef enum
{
	disabled,reserved,even,odd //UPM0,1
}UART_Parity;
typedef enum
{
	oneBit,twoBit //USBS in UCSRC =0 (1bit stop)/=1(2bit stop)
}UART_Stop;
typedef enum
{
	NTSH=9600,FTEH=4800,FTFH=14400
	//NTSH=nine thousand six hundred
}UART_Baudrate;

typedef struct{
	//data bit
	UART_BitData numBitData;//UCSZ0,1 in UCSRC reg
	UART_BitDataMode bitDataMode;//UCSZ2 in UCSRB reg
	//parity
	UART_Parity parity; // disable or enable parity bit (even/odd)
	UART_Stop stop; //USBS in UCSRC =0 (1bit stop)/=1(2bit stop)
	UART_Baudrate baudrate;

}UART_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE Config_Ptr->baudrate

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_init(const UART_ConfigType * Config_Ptr);
/*
 * Description: Function to set the Call Back function address.
 */
void UART_setCallBack(void(*a_ptr)(void));

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
