#include "led.h"

void led_init(GPIO_Type* GPIOx, uint8_t pin)
{
	PORT_Config_Type port_config = {
			.pull	= PORT_PULL_DISABLE,
			.mux	= PORT_MUX_GPIO,
			.irqc 	= PORT_IRQC_DISABLE,
	};

	PORT_Type* PORTx = (PORT_Type*)	(((uint32_t)GPIOx - GPIOA_BASE)/(GPIOB_BASE - GPIOA_BASE) * (PORTB_BASE - PORTA_BASE) + PORTA_BASE);
	PORT_Init(PORTx, pin, &port_config);

	GPIO_Config_Type output_config = {
			.direction 		= GPIO_PDDR_OUTPUT,
			.initial_value 	= GPIO_PIN_HIGH,
	};
	GPIO_Init(GPIOx, pin, &output_config);
}

LED_Status_t led_on(GPIO_Type* GPIOx, uint8_t pin)
{
	LED_Status_t status = LED_NOT_INIT;
	if (((GPIOx->PDDR & (1U << pin)) >> pin) == GPIO_PDDR_OUTPUT)
	{
		GPIO_ClearPin(GPIOx, pin);
	}

	return status;
}

LED_Status_t led_off(GPIO_Type* GPIOx, uint8_t pin)
{
	LED_Status_t status = LED_NOT_INIT;
	if (((GPIOx->PDDR & (1U << pin)) >> pin) == GPIO_PDDR_OUTPUT)
	{
		GPIO_SetPin(GPIOx, pin);
	}

	return status;
}

LED_Status_t led_toggle(GPIO_Type* GPIOx, uint8_t pin)
{
	LED_Status_t status = LED_NOT_INIT;
	if (((GPIOx->PDDR & (1U << pin)) >> pin) == GPIO_PDDR_OUTPUT)
	{
		GPIO_TogglePin(GPIOx, pin);
	}

	return status;
}
