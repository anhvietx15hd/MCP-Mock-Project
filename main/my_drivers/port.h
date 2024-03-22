/*
 * port.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Admin
 */

#ifndef MY_DRIVERS_PORT_H_
#define MY_DRIVERS_PORT_H_

#include "MKL46Z4.h"
#include "common.h"

typedef enum {
	PORT_INTR_RISING  = 9U,
	PORT_INTR_FALLING = 10U,
}PORT_IRQC_Type;

static inline void PORT_MUX_GPIO(PORT_Type *PORTx, uint8_t pin)
{
	PORTx->PCR[pin] = (PORTx->PCR[pin] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(1U);
}

static inline void PORT_Enable_PullUp(PORT_Type *PORTx, uint8_t pin)
{
	PORTx->PCR[pin] |= PORT_PCR_PE(1U) | PORT_PCR_PS(1U);
}

static inline void PORT_Config_Interrupt(PORT_Type *PORTx, uint8_t pin, PORT_IRQC_Type irqc)
{
	PORTx->PCR[pin] = (PORTx->PCR[pin] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(irqc);
}

static inline void PORT_Clear_InterruptFlag(PORT_Type *PORTx, uint8_t pin)
{
	PORTx->ISFR = (1U << pin); //w1c
}

static inline uint8_t PORT_InterruptFlag_isSet(PORT_Type *PORTx, uint8_t pin)
{
	return (PORTx->ISFR & (1U << pin)) != 0;
}

#endif /* MY_DRIVERS_PORT_H_ */
