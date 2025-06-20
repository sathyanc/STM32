/*
 * USART_Driver.h
 *
 *  Created on: May 18, 2025
 *      Author: sathyan
 */

#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include "stdint.h"
#include "stm32f411xe.h"

/* USART Peripheral Clock Frequency*/
#define USART_PeripheralClockFreq	8000000U

typedef enum
{
	USART1_ID,
	USART2_ID,
	USART6_ID
}USART_EN_ID_T;

typedef enum
{
	USART_WORDLENGTH_8B,
	USART_WORDLENGTH_9B
}USART_EN_WORDLENGTH_T;

typedef enum
{
	USART_PARITY_NONE,
	USART_PARITY_EVEN,
	USART_PARITY_ODD
}USART_EN_PARITY_T;

typedef enum
{
	USART_STOPBITS_0_5,
	USART_STOPBITS_1,
	USART_STOPBITS_1_5,
	USART_STOPBITS_2

}USART_EN_STOPBIT_T;

typedef struct
{
	USART_EN_ID_T usartID;
	uint32_t	  baudrate;
	USART_EN_WORDLENGTH_T	wordLength;
	USART_EN_PARITY_T	parity;
	USART_EN_STOPBIT_T stopBits;
	uint8_t oversampling;
}USART_Struct_T;

/*USART Function Declarations */
void USART_Init(USART_Struct_T *usartConfig);
void USART_DeInit(USART_EN_ID_T usartId);
void USART_Transmit(USART_EN_ID_T usartId, uint8_t *data, uint8_t length);
void USART_Receive(USART_EN_ID_T usartId, uint8_t *data, uint8_t length);
/*Support functions*/
void USART_Enable(USART_EN_ID_T usartId);
void USART_Disable(USART_EN_ID_T usartId);
void USART_ConfigureGPIO(USART_EN_ID_T usartId);



#endif
