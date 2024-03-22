/*
 * gpio.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Admin
 */

#ifndef MY_DRIVERS_GPIO_H_
#define MY_DRIVERS_GPIO_H_

#include "MKL46Z4.h"
#include "common.h"

static inline void GPIO_Direction_Output(GPIO_Type * GPIOx, uint8_t pin)
{
	GPIOx->PDDR |= (1U << pin);
}

static inline void GPIO_Toggle_Pin(GPIO_Type * GPIOx, uint8_t pin)
{
	GPIOx->PTOR = (1U << pin);
}

static inline void GPIO_Set_Pin(GPIO_Type * GPIOx, uint8_t pin)
{
	GPIOx->PSOR = (1U << pin);
}

static inline void GPIO_Clear_Pin(GPIO_Type * GPIOx, uint8_t pin)
{
	GPIOx->PCOR = (1U << pin);
}

#endif /* MY_DRIVERS_GPIO_H_ */
