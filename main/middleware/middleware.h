/*
 * middleware.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Admin
 */

#ifndef MIDDLEWARE_MIDDLEWARE_H_
#define MIDDLEWARE_MIDDLEWARE_H_

#include "common.h"
#include "gpio.h"
#include "port.h"
#include "sim.h"
#include "pit.h"

#define LED1_PIN	5U
#define LED1_GPIO	GPIOD
#define LED1_PORT	PORTD

#define LED2_PIN	29U
#define LED2_GPIO	GPIOE
#define LED2_PORT	PORTE

#define SW1_PIN		3U
#define SW1_PORT	PORTC

#define SW2_PIN		12U
#define SW2_PORT	PORTC

void M_Enable_Modules(void);
void M_Init_Board(void);
void M_Init_Timer(uint8_t channel, uint32_t ms);
void M_Config_LED(void);
void M_Enable_IRQHandler(void);

static inline void M_TurnOn_LED(GPIO_Type * GPIOx, uint8_t pin)
{
	GPIO_Clear_Pin(GPIOx, pin);
}

static inline void M_TurnOff_LED(GPIO_Type * GPIOx, uint8_t pin)
{
	GPIO_Set_Pin(GPIOx, pin);
}

static inline void M_Toggle_LED(GPIO_Type * GPIOx, uint8_t pin)
{
	GPIO_Toggle_Pin(GPIOx, pin);
}

static inline void M_Start_Timer(uint8_t channel)
{
	PIT_Enable_Timer(channel);
}

#endif /* MIDDLEWARE_MIDDLEWARE_H_ */
