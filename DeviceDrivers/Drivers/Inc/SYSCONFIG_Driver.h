/*
 * SYSCONFIG_Driver.h
 *
 *  Created on: May 2, 2025
 *      Author: sathyan
 */

#ifndef SYSCONFIG_DRIVER_H_
#define SYSCONFIG_DRIVER_H_

#include "stm32f411xe.h"
#include "stdint.h"

void SYSCFG_SetEXTISource(uint8_t EXTILine, uint8_t EXTILineVal);

#endif /* SYSCONFIG_DRIVER_H_ */
