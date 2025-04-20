#ifndef STM32F411XE_H
#define STM32F411XE_H

#include "stdint.h"

/* Macros related to all peripheral address, sram, flash address
 * Data structures related to peripherals
 * Peripherals bit definitions*/

#define FLASH_BASEADRR  	0x08000000U
#define FLASH_ENDADDR       0x0807FFFFU
#define SYSMEM_BASEADDR     0x1FFF0000U
#define OPTBYTES_BASEADDR   0x1FFFC000U
#define SRAM_BASEADDR		0x20000000U
#define SRAM_ENDADDR		0x20020000U

/*APB & AHB Peripherals*/
#define APB1PERIPH_BASEADDR 0x40000000U
#define APB2PERIPH_BASEADDR 0x40007400U
#define AHB1PERIPH_BASEADDR 0x40020000U
#define AHB2PERIPH_BASEADDR 0x50000000U

/*RCC Peripheral Address*/
#define RCC_BASEADDR 		0x40023800U

/*GPIO Peripherals address*/
#define GPIOA_BASEADDR 		(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR      (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR      (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR      (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR      (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOH_BASEADDR      (AHB1PERIPH_BASEADDR + 0x1C00)

/*GPIO Struct definitions*/
typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_RegDef;

/*RCC Struct definitions*/
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t RESERVED1;
	volatile uint32_t RESERVED2;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED3;
	volatile uint32_t RESERVED4;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RESERVED5;
	volatile uint32_t RESERVED6;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED7;
	volatile uint32_t RESERVED8;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED9;
	volatile uint32_t RESERVED10;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED11;
	volatile uint32_t RESERVED12;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED13;
	volatile uint32_t RESERVED14;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t RESERVED15;
	volatile uint32_t DCKCFGR;
}RCC_RegDef;

/*GPIO Stuct Macros*/
#define GPIOA    ((GPIO_RegDef*)GPIOA_BASEADDR)
#define GPIOB    ((GPIO_RegDef*)GPIOB_BASEADDR)
#define GPIOC    ((GPIO_RegDef*)GPIOC_BASEADDR)
#define GPIOD    ((GPIO_RegDef*)GPIOD_BASEADDR)
#define GPIOE    ((GPIO_RegDef*)GPIOE_BASEADDR)
#define GPIOH    ((GPIO_RegDef*)GPIOH_BASEADDR)

#define GPIO_MODER_BITMASK 		0x3
#define GPIO_OSPEEDR_BITMASK    0x3
#define GPIO_PUPDR_BITMASK		0x3
#define GPIO_AFR_MASK     	 	0xF
#define GPIO_MODER_SHIFT_BITS 	0x2
#define GPIO_OSPEEDR_SHIFT_BITS 0x2
#define GPIO_PUPDR_SHIFT_BITS 	0x2
#define GPIO_AFR_SIZE      		0x8
#define GPIO_AFR_MAXSIZE   		0xf
#define GPIO_AFR_SHIFT_BITS 	0x4


/*RCC Pointer to Struct Macro*/
#define RCC      ((RCC_RegDef*)RCC_BASEADDR)

#endif
