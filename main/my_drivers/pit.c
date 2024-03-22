/*
 * pit.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Admin
 */

#include "pit.h"

void PIT_Load_Value(uint8_t channel, uint32_t ms)
{
	uint8_t outdiv4;
	uint32_t ms_max;
	uint32_t load_value;

	SystemCoreClockUpdate();
	outdiv4 = 1U + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT);

	ms_max = 0xFFFFFFFFU / SystemCoreClock * outdiv4 * 1000U;
	if (ms > ms_max) ms = ms_max; // prevent bit overflow

	load_value = SystemCoreClock / outdiv4 / 1000U * ms - 1U; // beware of bit overflow
	PIT->CHANNEL[channel].LDVAL = (PIT->CHANNEL[channel].LDVAL & ~PIT_LDVAL_TSV_MASK) | PIT_LDVAL_TSV(load_value);
}
