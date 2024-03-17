#ifndef LED_H_
#define LED_H_

#include "port.h"
#include "gpio.h"
#include "pit.h"

typedef enum
{
	LED_SUCESS = 0U,
	LED_NOT_INIT,
} LED_Status_t;

/*!
 * @brief Initializes an LED on a specific GPIO pin, default state is off.
 *
 * @param GPIOx The GPIO port to which the LED is connected.
 * @param pin The pin number on the GPIO port to which the LED is connected.
 */
void led_init(GPIO_Type* GPIOx, uint8_t pin);

/*!
 * @brief Turns on the LED connected to a specific GPIO pin.
 *
 * @param GPIOx The GPIO port to which the LED is connected.
 * @param pin The pin number on the GPIO port to which the LED is connected.
 * @return LED_Status_t LED status.
 */
LED_Status_t led_on(GPIO_Type* GPIOx, uint8_t pin);

/*!
 * @brief Turns off the LED connected to a specific GPIO pin.
 *
 * @param GPIOx The GPIO port to which the LED is connected.
 * @param pin The pin number on the GPIO port to which the LED is connected.
 * @return LED_Status_t LED status.
 */
LED_Status_t led_off(GPIO_Type* GPIOx, uint8_t pin);

/*!
 * @brief Toggles the state of the LED connected to a specific GPIO pin.
 *
 * @param GPIOx The GPIO port to which the LED is connected.
 * @param pin The pin number on the GPIO port to which the LED is connected.
 * @return LED_Status_t LED status.
 */
LED_Status_t led_toggle(GPIO_Type* GPIOx, uint8_t pin);

#endif /* LED_H_ */
