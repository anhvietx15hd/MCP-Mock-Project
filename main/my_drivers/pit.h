/*
 * pit.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Admin
 */

#ifndef MY_DRIVERS_PIT_H_
#define MY_DRIVERS_PIT_H_

#include "MKL46Z4.h"
#include "common.h"

void PIT_Load_Value(uint8_t channel, uint32_t ms);

// enable PIT module
static inline void PIT_Enable(uint8_t mdis)
{
	PIT->MCR = PIT_MCR_MDIS(mdis);
}

// enable Timer interrupts
static inline void PIT_Enable_Interrupt(uint8_t channel)
{
	PIT->CHANNEL[channel].TCTRL |= PIT_TCTRL_TIE(1U);
}

// start Timer
static inline void PIT_Enable_Timer(uint8_t channel)
{
	PIT->CHANNEL[channel].TCTRL |= PIT_TCTRL_TEN(1U);
}

static inline void PIT_Clear_InterruptFlag(uint8_t channel)
{
	PIT->CHANNEL[channel].TFLG = PIT_TFLG_TIF(1U);
}

static inline uint8_t PIT_InterruptFlag_isSet(uint8_t channel)
{
	return (PIT->CHANNEL[channel].TFLG & PIT_TFLG_TIF(1U)) != 0;
}

#endif /* MY_DRIVERS_PIT_H_ */
