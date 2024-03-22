/*
 * middleware.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Admin
 */
#include "config.h"
#include "middleware.h"

void M_Enable_Modules(void) // sim
{
#ifdef ENABLE_PORTD
	// Enable SIM_PORTD for LED1,...
	SIM_Enable_PORTD();
#endif

#ifdef ENABLE_PORTE
	// Enable SIM_PORTE for LED2,...
	SIM_Enable_PORTE();

#endif

#ifdef ENABLE_PORTC
	// Enable SIM_PORTC for SW1, SW2
	SIM_Enable_PORTC();
#endif

#ifdef ENABLE_PIT
	// Enable SIM_PIT for Timer
	SIM_Enable_PIT();
#endif
}

void M_Init_Board(void) // port
{
#ifdef INIT_LED1
	// Register GPIO for LED1
	PORT_MUX_GPIO(LED1_PORT, LED1_PIN);
#endif

#ifdef INIT_LED2
	// Register GPIO for LED2
	PORT_MUX_GPIO(LED2_PORT, LED2_PIN);
#endif

#ifdef INIT_SW1
	// Register GPIO for SW1
	PORT_MUX_GPIO(SW1_PORT, SW1_PIN);
	// Enable Pull and Select pull-up for SW1
	PORT_Enable_PullUp(SW1_PORT, SW1_PIN);
	// Enable interrupt flag with falling edge for SW1
	PORT_Config_Interrupt(SW1_PORT, SW1_PIN, PORT_INTR_FALLING);
#endif

#ifdef INIT_SW2
	// Register GPIO for SW2
	PORT_MUX_GPIO(SW2_PORT, SW2_PIN);
	// Enable Pull and Select pull-up for SW2
	PORT_Enable_PullUp(SW2_PORT, SW2_PIN);
	// Enable interrupt flag with falling edge for SW2
	PORT_Config_Interrupt(SW2_PORT, SW2_PIN, PORT_INTR_FALLING);
#endif
}

void M_Init_Timer(uint8_t channel, uint32_t ms) // pit
{
	PIT_Enable(0U);
	PIT_Load_Value(channel, ms);
	PIT_Enable_Interrupt(channel);
}

void M_Config_LED(void) //gpio
{
#ifdef INIT_LED1
	// register output direction for lED1
	GPIO_Direction_Output(LED1_GPIO, LED1_PIN);
#endif

#ifdef INIT_LED2
	// register output direction for lED2
	GPIO_Direction_Output(LED2_GPIO, LED2_PIN);
#endif
}

void M_Enable_IRQHandler(void) //nvic
{
#ifdef ENABLE_IRQ_PORTC_PORTD
	// Enable interrupt handler for SW1, SW2
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);
#endif

#ifdef ENABLE_IRQ_PIT
	// Enable interrupt handler for Timer
	NVIC_EnableIRQ(PIT_IRQn);
#endif
}
