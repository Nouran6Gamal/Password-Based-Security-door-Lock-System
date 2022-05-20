 /******************************************************************************
 *
 * Module: I2C(TWI)
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C(TWI) AVR driver
 *
 * Author: Nouran Gamal
 *
 *******************************************************************************/ 


#ifndef I2C_H_
#define I2C_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#define NULL_PTR ((void*)0)


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	slave_add
}I2C_SlaveAddress;
typedef enum{
	two=0x02,three=0x03
}I2C_DivFactor; //division factor
typedef enum{
	one=0x00,four=0x01,sixteen=0x02,fourtysix=0x03 // prescaler value
}I2C_PreScaler;

typedef struct{
	I2C_DivFactor TWBR_i2c;
	I2C_PreScaler TWPS;
	I2C_SlaveAddress slave_add;
}I2C_ConfigType;


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start 
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(const I2C_ConfigType * Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void); //read with send Ack
uint8 TWI_readWithNACK(void); //read without send Ack
uint8 TWI_getStatus(void);
/*
 * Description: Function to set the Call Back function address.
 */
void I2C_setCallBack(void(*a_ptr)(void));


#endif /* I2C_H_ */
