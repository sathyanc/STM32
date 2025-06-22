/*
 * USART_Driver.c
 *
 *  Created on: May 25, 2025
 *      Author: sathyan
 */

#include "USART_Driver.h"
#include "GPIO_Driver.h"
#include "RCC_Driver.h"

/*This function initializes the USART Peripheral based on the USARTID passed through the Config Struct*/
void USART_Init(USART_Struct_T *usartConfig)
{
	uint8_t Over8Val;
	float UsartDiv,fraction;
	uint32_t Mantissa;
	USART_RegDef_T *pUsart;

	pUsart = usartConfig->USARTInstance;

	/*Configure the GPIO Peripheral for the given USART peripheral*/
	USART_ConfigureGPIO(usartConfig->usartID);

	/*Select the USART Peripheral and Init the Clock for it*/
	switch(usartConfig->usartID)
	{
		case USART1_ID:
			/*Enable the Peripheral Clock*/
			RCC->APB2ENR |= ( 1 << 4);
			break;
		case USART2_ID:
			/*Enable the Peripheral Clock*/
			RCC->APB1ENR |= ( 1 << 17);
			break;
		case USART6_ID:
			/*Enable the Peripheral Clock*/
			RCC->APB2ENR |= ( 1 << 5);
			break;
		default:
			return;
	}

	/*Set the Word Length*/
	if(usartConfig->wordLength == USART_WORDLENGTH_8B)
	{
		pUsart->CR1 &= ~(1 << 12);
	}
	else
	{
		pUsart->CR1 |= (1<<12); //9bits word length
	}
	/*Set the Stop bits*/
	pUsart->CR2 &= ~(0b11 << 12);
	if(usartConfig->stopBits == USART_STOPBITS_0_5)
		pUsart->CR2 |=  USARTx_CR2_STOPBIT0_5;
	else if(usartConfig->stopBits == USART_STOPBITS_1)
		pUsart->CR2 |=  USARTx_CR2_STOPBIT1;
	else if(usartConfig->stopBits == USART_STOPBITS_1_5)
		pUsart->CR2 |=  USARTx_CR2_STOPBIT1_5;
	else if(usartConfig->stopBits == USART_STOPBITS_2)
		pUsart->CR2 |=  USARTx_CR2_STOPBIT2;


	/*Enable or Disable Parity*/
	if(usartConfig->parity != USART_PARITY_NONE)
	{
		/*Enable Parity*/
		pUsart->CR1 |= (1 << 10);

		/*Set the Parity*/
		pUsart->CR1 &= ~(1 << 9);
		if(usartConfig->parity == USART_PARITY_EVEN)
		{
			pUsart->CR1 &= ~(1 << 9);
		}
		else if(usartConfig->parity == USART_PARITY_ODD)/*ODD*/
		{
			pUsart->CR1 |= (1 << 9);
		}
	}

	/*Set Oversampling Flag OVER8*/
	if(usartConfig->oversampling == 8)
	{
		pUsart->CR1 |= USARTx_CR1_OVER8;
		Over8Val =1;
	}
	else if(usartConfig->oversampling == 16)
	{
		pUsart->CR1 &= ~USARTx_CR1_OVER8;
		Over8Val =0;
	}

	/*Set the Baud rate*/
	//USARTDIV = FClk / ( 8 x ( 2 - OVER8) x BaudRate)
	UsartDiv = (USART_PeripheralClockFreq / (8 * (2 - Over8Val) * usartConfig->baudrate));
	Mantissa = (uint32_t)UsartDiv;
	fraction = UsartDiv - Mantissa;

	if(Over8Val == 1)
	{
		pUsart->BRR = (Mantissa << 4) | (uint8_t)(fraction * 8 + 0.5f);
	}
	else /*Oversampling by 16*/
	{
		pUsart->BRR = (Mantissa << 4) | (uint8_t)(fraction * 16 + 0.5f);
	}

	/*Enable Transmitter/Receiver*/
	/*Enable USART*/
	pUsart->CR1 |= (USARTx_CR1_TE) | (USARTx_CR1_RE) | (USARTx_CR1_UE);
}

/*This function DeInitializes the USART peripheral based on the USART ID passed as a param*/
void USART_DeInit(USART_Struct_T *usartConfig)
{
	if(usartConfig->usartID == USART1_ID)
	{
		/*Disable USART1 Peripheral Clock through APB RCC Register */
		RCC->APB2ENR &= ~( 1 << 4);
	}
	else if(usartConfig->usartID == USART2_ID)
	{
		/*Disable USART1 Peripheral Clock through APB RCC Register */
		RCC->APB1ENR &= ~( 1 << 17);
	}
	else if(usartConfig->usartID == USART6_ID)
	{
		/*Disable USART1 Peripheral Clock through APB RCC Register */
		RCC->APB2ENR &= ~( 1 << 5);
	}
	/*Disable USART1 through CR1 Register*/
	usartConfig->USARTInstance->CR1 &= ~(USARTx_CR1_UE);
}

/*This function transmits the data of length passed as param*/
void USART_Transmit(USART_Struct_T *usartConfig, uint8_t *data, uint8_t length)
{
	USART_RegDef_T *pUsart;
	pUsart = usartConfig->USARTInstance;

	if(!usartConfig || !pUsart || !data || !length)
		return;

	for (uint32_t i=0; i<length; i++ )
	{
		while (!(pUsart->SR & USARTx_SR_TXE));

		//Transmit the data
		pUsart->DR = data[i] & 0xff;
	}
	//Check the TC Flag
	while (!(pUsart->SR & USARTx_SR_TC));
}


/*This function prepares the global buffers to transmit data in Interrupt mode*/
void USART_Transmit_IT(USART_Struct_T *usartConfig, uint8_t *data, uint8_t length)
{
	if((usartConfig->TxBusy == 1) || length == 0)
		return;

	usartConfig->pTxBuffer = data;
	usartConfig->TxLength = length;
	usartConfig->TxIndex = 0;
	usartConfig->TxBusy = 1;

	usartConfig->USARTInstance->CR1 |= USARTx_CR1_TXEIE;
}

/*This function receives the data through the data buffer of length passed as param*/
void USART_Receive(USART_Struct_T *usartConfig, uint8_t *data, uint8_t length)
{
	USART_RegDef_T *pUsart;
	pUsart = usartConfig->USARTInstance;

	if(!usartConfig || !pUsart || !data || !length)
		return;

	for (uint32_t i=0; i< length; i++)
	{
		//Check the RXNE Flag in SR
		while(!(pUsart->SR & USARTx_SR_RXNE));

		//Read the DR
		data[i] = pUsart->DR & 0xFF;
	}
}

/*Setup the buffers to receive data in Interrupt mode*/
void USART_Receive_IT(USART_Struct_T *usartConfig, uint8_t *data, uint8_t length)
{
	if((usartConfig->RxBusy == 1) || length == 0)
			return;

	usartConfig->pRxBuffer = data;
	usartConfig->RxLength = length;
	usartConfig->RxIndex = 0;
	usartConfig->RxBusy = 1;

	usartConfig->USARTInstance->CR1 |= USARTx_CR1RXNEIE;
}

/* This function enables the USART for given USART Peripheral ID*/
void USART_Enable(USART_Struct_T *usartConfig)
{
	USART_RegDef_T *pUsart;
	pUsart = usartConfig->USARTInstance;

	if(!usartConfig || !pUsart )
		return;

	pUsart->CR1 |= USARTx_CR1_UE;

}

/* This function disables the USART for given USART Peripheral ID*/
void USART_Disable(USART_Struct_T *usartConfig)
{
	USART_RegDef_T *pUsart;
	pUsart = usartConfig->USARTInstance;

	if(!usartConfig || !pUsart )
		return;

	pUsart->CR1 &= ~USARTx_CR1_UE;
}

/*This function configures the GPIO peripheral for the given USART ID*/
void USART_ConfigureGPIO(USART_EN_ID_T usartId)
{

	GPIO_PINCONFIG_T GpioUsartPinConfig =
	{
			.pin = 0,
			.mode= GPIO_MODE_ALT,
			.otype=GPIO_OTYPE_PP,
			.speed=GPIO_SPEED_LOW,
			.pupdr=GPIO_NO_PULL,
			.alternatefunc=0
	};

	/*Configure the GPIO for USART1*/
	if(usartId == USART1_ID)
	{
		RCC_EnableGPIO(GPIOA);
		/* PA9-Tx and PA10-Rx; AF - 7  */
		GpioUsartPinConfig.pin = 9;
		GpioUsartPinConfig.alternatefunc = 7;
		GPIO_Init(GPIOA, &GpioUsartPinConfig);

		GpioUsartPinConfig.pin = 10;
		GPIO_Init(GPIOA, &GpioUsartPinConfig);

	}
	/*Configure the GPIO for USART2*/
	else if (usartId == USART2_ID)
	{
		RCC_EnableGPIO(GPIOA);
		/*PA2 -Tx and PA3-Rx; AF - 7  */
		GpioUsartPinConfig.pin = 2;
		GpioUsartPinConfig.alternatefunc = 7;
		GPIO_Init(GPIOA, &GpioUsartPinConfig);

		GpioUsartPinConfig.pin = 3;
		GPIO_Init(GPIOA, &GpioUsartPinConfig);
	}
	/*Configure the GPIO for USART6*/
	else if (usartId == USART6_ID)
	{
		RCC_EnableGPIO(GPIOC);
		/*PC6 -Tx and PC7-Rx; AF - 8  */
		GpioUsartPinConfig.pin = 6;
		GpioUsartPinConfig.alternatefunc = 8;
		GPIO_Init(GPIOC, &GpioUsartPinConfig);

		GpioUsartPinConfig.pin = 7;
		GPIO_Init(GPIOC, &GpioUsartPinConfig);
	}
	else
	{

	}
}



