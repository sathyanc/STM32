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

	/*Configure the GPIO Peripheral for the given USART peripheral*/
	USART_ConfigureGPIO(usartConfig->usartID);

	if(usartConfig->usartID == USART1_ID)
	{
		/*Enable the Peripheral Clock*/
		RCC->APB2ENR |= ( 1 << 4);

		/*Set the Word Length*/
		if(usartConfig->wordLength == USART_WORDLENGTH_8B)
		{
			USART1->CR1 &= ~(1 << 12);
		}
		else
		{
			USART1->CR1 |= (1<<12); //9bits word length
		}
		/*Set the Stop bits*/
		USART1->CR2 &= ~(0b11 << 12);
		if(usartConfig->stopBits == USART_STOPBITS_0_5)
			USART1->CR2 |=  USARTx_CR2_STOPBIT0_5;
		else if(usartConfig->stopBits == USART_STOPBITS_1)
			USART1->CR2 |=  USARTx_CR2_STOPBIT1;
		else if(usartConfig->stopBits == USART_STOPBITS_1_5)
			USART1->CR2 |=  USARTx_CR2_STOPBIT1_5;
		else if(usartConfig->stopBits == USART_STOPBITS_2)
			USART1->CR2 |=  USARTx_CR2_STOPBIT2;


		/*Enable or Disable Parity*/
		if(usartConfig->parity != USART_PARITY_NONE)
		{
			/*Enable Parity*/
			USART1->CR1 |= (1 < 10);

			/*Set the Parity*/
			USART1->CR1 &= ~(1 << 9);
			if(usartConfig->parity == USART_PARITY_EVEN)
			{
				USART1->CR1 &= ~(1 << 9);
			}
			else if(usartConfig->parity == USART_PARITY_ODD)/*ODD*/
			{
				USART1->CR1 |= (1 << 9);
			}
		}

		/*Set Oversampling Flag OVER8*/
		if(usartConfig->oversampling == 8)
		{
			USART1->CR1 |= USARTx_CR1_OVER8;
			Over8Val =1;
		}
		else if(usartConfig->oversampling == 16)
		{
			USART1->CR1 &= ~USARTx_CR1_OVER8;
			Over8Val =0;
		}

		/*Set the Baud rate*/
		//USARTDIV = FClk / ( 8 x ( 2 - OVER8) x BaudRate)
		UsartDiv = (USART_PeripheralClockFreq / (8 * (2 - Over8Val) * usartConfig->baudrate));
		Mantissa = (uint32_t)UsartDiv;
		fraction = UsartDiv - Mantissa;

		if(Over8Val == 1)
		{
			USART1->BRR = (Mantissa << 4) | (uint8_t)(fraction * 8 + 0.5f);
		}
		else /*Oversampling by 16*/
		{
			USART1->BRR = (Mantissa << 4) | (uint8_t)(fraction * 16 + 0.5f);
		}

		/*Enable Transmitter/Receiver*/
	 	/*Enable USART*/
		USART1->CR1 |= (USARTx_CR1_TE) | (USARTx_CR1_RE) | (USARTx_CR1_UE);
	}
	else if(usartConfig->usartID == USART2_ID)
	{
		/*Enable the Peripheral Clock*/
		RCC->APB1ENR |= ( 1 << 17);

		/*Set the Word Length*/
		if(usartConfig->wordLength == USART_WORDLENGTH_8B)
		{
			USART2->CR1 &= ~(1 << 12);
		}
		else
		{
			USART2->CR1 |= (1<<12); //9bits word length
		}
		/*Set the Stop bits*/
		USART2->CR2 &= ~(0b11 << 12);
		if(usartConfig->stopBits == USART_STOPBITS_0_5)
			USART2->CR2 |=  USARTx_CR2_STOPBIT0_5;
		else if(usartConfig->stopBits == USART_STOPBITS_1)
			USART2->CR2 |=  USARTx_CR2_STOPBIT1;
		else if(usartConfig->stopBits == USART_STOPBITS_1_5)
			USART2->CR2 |=  USARTx_CR2_STOPBIT1_5;
		else if(usartConfig->stopBits == USART_STOPBITS_2)
			USART2->CR2 |=  USARTx_CR2_STOPBIT2;

		/*Enable or Disable Parity*/
		if(usartConfig->parity != USART_PARITY_NONE)
		{
			/*Enable Parity*/
			USART2->CR1 |= (1 < 10);

			/*Set the Parity*/
			USART2->CR1 &= ~(1 << 9);
			if(usartConfig->parity == USART_PARITY_EVEN)
			{
				USART2->CR1 &= ~(1 << 9);
			}
			else if(usartConfig->parity == USART_PARITY_ODD)/*ODD*/
			{
				USART2->CR1 |= (1 << 9);
			}
		}

				/*Set Oversampling Flag OVER8*/
		if(usartConfig->oversampling == 8)
		{
			USART2->CR1 |= USARTx_CR1_OVER8;
			Over8Val =1;
		}
		else if(usartConfig->oversampling == 16)
		{
			USART2->CR1 &= ~USARTx_CR1_OVER8;
			Over8Val =0;
		}

		/*Set the Baud rate*/
		//USARTDIV = FClk / ( 8 x ( 2 - OVER8) x BaudRate)
		UsartDiv = ((float)USART_PeripheralClockFreq / (float)((8 * (2 - Over8Val) * usartConfig->baudrate)));
		Mantissa = (uint32_t)UsartDiv;
		fraction = UsartDiv - Mantissa;

		if(Over8Val == 1)
		{
			USART2->BRR = (Mantissa << 4) | (uint8_t)(fraction * 8 + 0.5f);
		}
		else /*Oversampling by 16*/
		{
			USART2->BRR = (Mantissa << 4) | (uint8_t)(fraction * 16 + 0.5f);
		}

		/*Enable Transmitter/Receiver*/
	 	/*Enable USART*/
		USART2->CR1 |= (USARTx_CR1_TE) | (USARTx_CR1_RE) | (USARTx_CR1_UE);
	}
	else if(usartConfig->usartID == USART6_ID)
	{
		/*Enable the Peripheral Clock*/
		RCC->APB2ENR |= ( 1 << 5);

		/*Set the Word Length*/
		if(usartConfig->wordLength == USART_WORDLENGTH_8B)
		{
			USART6->CR1 &= ~(1 << 12);
		}
		else
		{
			USART6->CR1 |= (1<<12); //9bits word length
		}
		/*Set the Stop bits*/
		USART6->CR2 &= ~(0b11 << 12);
		if(usartConfig->stopBits == USART_STOPBITS_0_5)
			USART6->CR2 |=  USARTx_CR2_STOPBIT0_5;
		else if(usartConfig->stopBits == USART_STOPBITS_1)
			USART6->CR2 |=  USARTx_CR2_STOPBIT1;
		else if(usartConfig->stopBits == USART_STOPBITS_1_5)
			USART6->CR2 |=  USARTx_CR2_STOPBIT1_5;
		else if(usartConfig->stopBits == USART_STOPBITS_2)
			USART6->CR2 |=  USARTx_CR2_STOPBIT2;


		/*Enable or Disable Parity*/
		if(usartConfig->parity != USART_PARITY_NONE)
		{
			/*Enable Parity*/
			USART6->CR1 |= (1 < 10);

			/*Set the Parity*/
			USART6->CR1 &= ~(1 << 9);
			if(usartConfig->parity == USART_PARITY_EVEN)
			{
				USART6->CR1 &= ~(1 << 9);
			}
			else if(usartConfig->parity == USART_PARITY_ODD)/*ODD*/
			{
				USART6->CR1 |= (1 << 9);
			}
		}
		/*Set Oversampling Flag OVER8*/
		if(usartConfig->oversampling == 8)
		{
			USART6->CR1 |= USARTx_CR1_OVER8;
			Over8Val =1;
		}
		else if(usartConfig->oversampling == 16)
		{
			USART6->CR1 &= ~USARTx_CR1_OVER8;
			Over8Val =0;
		}

		/*Set the Baud rate*/
		//USARTDIV = FClk / ( 8 x ( 2 - OVER8) x BaudRate)
		UsartDiv = (USART_PeripheralClockFreq / (8 * (2 - Over8Val) * usartConfig->baudrate));
		Mantissa = (uint32_t)UsartDiv;
		fraction = UsartDiv - Mantissa;

		if(Over8Val == 1)
		{
			USART6->BRR = (Mantissa << 4) | (uint8_t)(fraction * 8 + 0.5f);
		}
		else /*Oversampling by 16*/
		{
			USART6->BRR = (Mantissa << 4) | (uint8_t)(fraction * 16 + 0.5f);
		}

		/*Enable Transmitter/Receiver*/
		/*Enable USART*/
		USART6->CR1 |= (USARTx_CR1_TE) | (USARTx_CR1_RE) | (USARTx_CR1_UE);
	}
	else
	{

	}

}

/*This function DeInitializes the USART peripheral based on the USART ID passed as a param*/
void USART_DeInit(USART_EN_ID_T usartId)
{
	if(usartId == USART1_ID)
	{
		/*Disable USART1 through CR1 Register*/
		USART1->CR1 &= ~(USARTx_CR1_UE);

		/*Disable USART1 Peripheral Clock through APB RCC Register */
		RCC->APB2ENR &= ~( 1 << 4);
	}
	else if(usartId == USART2_ID)
	{
		/*Disable USART2 through CR1 Register*/
		USART2->CR1 &= ~(USARTx_CR1_UE);

		/*Disable USART1 Peripheral Clock through APB RCC Register */
		RCC->APB1ENR &= ~( 1 << 17);
	}
	else if(usartId == USART6_ID)
	{
		/*Disable USART2 through CR1 Register*/
		USART6->CR1 &= ~(USARTx_CR1_UE);

		/*Disable USART1 Peripheral Clock through APB RCC Register */
		RCC->APB2ENR &= ~( 1 << 5);
	}
}

/*This function transmits the data of length passed as param*/
void USART_Transmit(USART_EN_ID_T usartId, uint8_t *data, uint8_t length)
{
	if(usartId == USART1_ID)
	{
		for (uint32_t i=0; i<length; i++ )
		{
			while (!(USART1->SR & USARTx_SR_TXE));

			//Transmit the data
			USART1->DR = data[i] & 0xff;
		}
		//Check the TC Flag
		while (!(USART1->SR & USARTx_SR_TC));
	}

	else if(usartId == USART2_ID)
	{
		for (uint32_t i=0; i<length; i++ )
		{
			while (!(USART2->SR & USARTx_SR_TXE));

			//Transmit the data
			USART2->DR = data[i] & 0xff;
		}
		//Check the TC Flag
		while(!(USART2->SR & USARTx_SR_TC));
	}
	else if(usartId == USART6_ID)
	{
		for (uint32_t i=0; i<length; i++ )
		{
			while(!(USART6->SR & USARTx_SR_TXE));

			//Transmit the data
			USART6->DR = data[i] & 0xff;
		}
		//Check the TC Flag
		while (!(USART6->SR & USARTx_SR_TC));
	}

}

/*This function receives the data through the data buffer of length passed as param*/
void USART_Receive(USART_EN_ID_T usartId, uint8_t *data, uint8_t length)
{
	if(usartId == USART1_ID)
	{
		for (uint32_t i=0; i< length; i++)
		{
			//Check the RXNE Flag in SR
			while(!(USART1->SR & USARTx_SR_RXNE));

			//Read the DR
			data[i] = USART1->DR & 0xFF;
		}
	}
	else if(usartId == USART2_ID)
	{
		for (uint32_t i=0; i< length; i++)
		{
			//Check the RXNE Flag in SR
			while(!(USART2->SR & USARTx_SR_RXNE));

			//Read the DR
			data[i] = USART2->DR & 0xFF;
		}
	}
	else if(usartId == USART6_ID)
	{
		for (uint32_t i=0; i< length; i++)
		{
			//Check the RXNE Flag in SR
			while(!(USART6->SR & USARTx_SR_RXNE));

			//Read the DR
			data[i] = USART6->DR & 0xFF;
		}
	}
}

/* This function enables the USART for given USART Peripheral ID*/
void USART_Enable(USART_EN_ID_T usartId)
{
	if(usartId == USART1_ID)
	{
		USART1->CR1 |= USARTx_CR1_UE;
	}
	else if (usartId == USART2_ID)
	{
		USART2->CR1 |= USARTx_CR1_UE;
	}
	else if (usartId == USART6_ID)
	{
		USART6->CR1 |= USARTx_CR1_UE;
	}
}

/* This function disables the USART for given USART Peripheral ID*/
void USART_Disable(USART_EN_ID_T usartId)
{
	if(usartId == USART1_ID)
	{
		USART1->CR1 &= ~USARTx_CR1_UE;
	}
	else if (usartId == USART2_ID)
	{
		USART2->CR1 &= ~USARTx_CR1_UE;
	}
	else if (usartId == USART6_ID)
	{
		USART6->CR1 &= ~USARTx_CR1_UE;
	}
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
