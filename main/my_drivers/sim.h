/*
 * sim.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Admin
 */

#ifndef MY_DRIVERS_SIM_H_
#define MY_DRIVERS_SIM_H_

#include "MKL46Z4.h"
#include "common.h"

static inline void SIM_Enable_PORTA(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA(1U);
}

static inline void SIM_Enable_PORTB(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1U);
}

static inline void SIM_Enable_PORTC(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1U);
}

static inline void SIM_Enable_PORTD(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD(1U);
}

static inline void SIM_Enable_PORTE(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE(1U);
}

static inline void SIM_Enable_PIT(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT(1U);
}

#endif /* MY_DRIVERS_SIM_H_ */
