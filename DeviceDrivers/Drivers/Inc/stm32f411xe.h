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

/*EXTI Register Stuct*/
typedef struct
{
	volatile uint32_t IMR;		/*Interrupt Mask Register*/
	volatile uint32_t EMR;		/*Event Mask Register*/
	volatile uint32_t RTSR;		/*Rising Trigger Selection Register*/
	volatile uint32_t FTSR;		/*Falling Trigger Selection Register*/
	volatile uint32_t SWIER;	/*Software Interrupt Event Register*/
	volatile uint32_t PR;		/*Pending Register*/
}EXTI_RegDef;

/*Macros related to EXTI Peripherals */
#define  EXTI_BASEADDR			0x40013C00U
#define  EXTI 					((EXTI_RegDef*)EXTI_BASEADDR)

/*EXTI Interrupt number*/
#define EXTI0_IRQn			6
#define EXTI1_IRQn			7
#define EXTI2_IRQn			8
#define EXTI3_IRQn			9
#define EXTI4_IRQn			10
#define EXTI9_5IRQn			23
#define EXTI15_10     	    40


/*RCC Pointer to Struct Macro*/
#define RCC      ((RCC_RegDef*)RCC_BASEADDR)


/*SYSCONFIG Related Macros*/
typedef struct
{
	volatile uint32_t MEMRMP;      // Memory Remap Register
	volatile uint32_t PMC;		   // Peripheral Mode Config Register
	volatile uint32_t EXTICR[4];   // External Interrupt Config Register
	volatile uint32_t RESERVED[2]; // Reserved Registers
	volatile uint32_t CMPCR; 	   // Compensation Cell Control Register
}SYSCFG_RegDef;


#define SYSCFG_BASE_ADDR   		0x40013800U

/*SYSCFG Pointer to Struct Macro */
#define SYSCFG					((SYSCFG_RegDef*)SYSCFG_BASE_ADDR)

/*NVIC Related Macros*/
#define NVIC_BASE_ADDR			 0xE000E100U

#define NVIC_ISERx_BASE			 ((volatile uint32_t*)NVIC_BASE_ADDR)
#define NVIC_ICERx_BASE          ((volatile uint32_t*)0xE000E180U)
#define NVIC_ISPRx_BASE          ((volatile uint32_t*)0xE000E200U)
#define NVIC_ICPRx_BASE          ((volatile uint32_t*)0xE000E280U)
#define NVIC_IABRx_BASE          ((volatile uint32_t*)0xE000E300U)
#define NVIC_IPRx_BASE		     ((volatile uint8_t*)0xE000E400U)

/*USART Peripheral related Macros*/
#define USART1_BASE_ADDR		 0x40011000U
#define USART2_BASE_ADDR		 0x40004400U
#define USART6_BASE_ADDR 		 0x40011400U

/*Register Structure for USARTx*/
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_RegDef_T;

/*Pointers to Register Struct for all USART Peripheral*/
#define USART1 		((USART_RegDef_T*)USART1_BASE_ADDR)
#define USART2 		((USART_RegDef_T*)USART2_BASE_ADDR)
#define USART6		((USART_RegDef_T*)USART6_BASE_ADDR)

/*USARTx Status Register related Macros*/
#define USARTx_SR_TXE	(1 << 7)
#define USARTx_SR_TC	(1 << 6)
#define USARTx_SR_RXNE  (1 << 5)

/*USARTx CR1 Register related Macros*/
#define USARTx_CR1_OVER8  (1 << 15)
#define USARTx_CR1_UE	  (1 << 13)
#define USARTx_CR1_TXEIE  (1 << 7)
#define USARTx_CR1_TCIE   (1 << 6)
#define USARTx_CR1RXNEIE  (1 << 5)
#define USARTx_CR1_TE	  (1 << 3)
#define USARTx_CR1_RE	  (1 << 2)

/*USARTx CR2 Register related macros*/
#define USARTx_CR2_STOPBIT1   (0b00 << 12)
#define USARTx_CR2_STOPBIT0_5 (0b01 << 12)
#define USARTx_CR2_STOPBIT1_5 (0b11 << 12)
#define USARTx_CR2_STOPBIT2   (0b10 << 12)

/*USARTx CR3 Register related Macros*/
#define USARTx_CR3_ONEBIT	(1 << 11)

/*SCB related macros*/
#define SCB_CPACR_ADDR		(*(volatile uint32_t*)0xE000ED88U)

#endif
