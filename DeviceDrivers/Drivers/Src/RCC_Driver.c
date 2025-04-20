#include "RCC_Driver.h"

/*Enables the GPIO Peripheral Clock for a particular GPIO port */
void RCC_EnableGPIO(GPIO_RegDef *port)
{
	if(port == GPIOA)
	{
		RCC->AHB1ENR |= ( 1 << 0);
	}
	else if (port == GPIOB)
	{
		RCC->AHB1ENR |= ( 1 << 1);
	}
	else if (port == GPIOC)
	{
		RCC->AHB1ENR |= ( 1 << 2);
	}
	else if (port == GPIOD)
	{
		RCC->AHB1ENR |= ( 1 << 3);
	}
	else if (port == GPIOE)
	{
		RCC->AHB1ENR |= ( 1 << 4);
	}
	else if (port == GPIOH)
	{
		RCC->AHB1ENR |= ( 1 << 7);
	}
}

/*Disables the GPIO Peripheral Clock for a particular GPIO port */
void RCC_DisableGPIO(GPIO_RegDef *port)
{
	if(port == GPIOA)
	{
		RCC->AHB1ENR &= ~( 1 << 0);
	}
	else if (port == GPIOB)
	{
		RCC->AHB1ENR &= ~( 1 << 1);
	}
	else if (port == GPIOC)
	{
		RCC->AHB1ENR &= ~( 1 << 2);
	}
	else if (port == GPIOD)
	{
		RCC->AHB1ENR &= ~( 1 << 3);
	}
	else if (port == GPIOE)
	{
		RCC->AHB1ENR &= ~( 1 << 4);
	}
	else if (port == GPIOH)
	{
		RCC->AHB1ENR &= ~( 1 << 7);
	}
}
