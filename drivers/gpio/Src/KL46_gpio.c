/*INCLUDES-------------------------------------------------------------------*/
#include <assert.h>
#include "KL46_gpio.h"
/*DEFINES--------------------------------------------------------------------*/
#ifndef NULL
#define NULL ((void *)0)
#endif
/*DEFINITIONS-----------------------------------------------------------------*/
void GPIO_Pin_Init(GPIO_Type* GPIOx, uint8_t pin_number, GPIO_Pin_Config_t* config) {
    /*Check parameters*/
    assert(IS_GPIO(GPIOx));
    assert(IS_GPIO_PIN_NUMBER(pin_number));
    assert(IS_GPIO_DIRECTION(config->direction));
    /*Config direction*/
    GPIOx->PDDR &= (1U << pin_number);           /*Clear the Direction bit - INPUT*/
    if(config->direction == GPIO_OUTPUT) {
        GPIOx->PDDR |= (1U << pin_number); /*Set direction to OUTPUT*/
        assert(IS_GPIO_LOGIC(config->default_logic));
        if(config->default_logic == GPIO_LOGIC_HIGH) { /*Set the default output*/
            GPIO_Set_Pin(GPIOx, pin_number);
        } else {
            GPIO_Clear_Pin(GPIOx, pin_number);
        }
    } else {
        GPIOx->PDDR &= (~ (1U << pin_number)); /*Set direction to INPUT*/
    }
}

void GPIO_Toggle_Pin(GPIO_Type* GPIOx, uint8_t pin_number) {
    /*Check parameters*/
    assert(IS_GPIO(GPIOx));
    assert(IS_GPIO_PIN_NUMBER(pin_number));

    GPIOx->PTOR |= (1U << pin_number);
}

void GPIO_Set_Pin(GPIO_Type* GPIOx, uint8_t pin_number) {
    /*Check parameters*/
    assert(IS_GPIO(GPIOx));
    assert(IS_GPIO_PIN_NUMBER(pin_number));

    GPIOx->PSOR |= (1U << pin_number);
}

void GPIO_Clear_Pin(GPIO_Type* GPIOx, uint8_t pin_number) {
    /*Check parameters*/
    assert(IS_GPIO(GPIOx));
    assert(IS_GPIO_PIN_NUMBER(pin_number));
    
    GPIOx->PCOR |= (1U << pin_number);
}
/*EOF----------------------------------------------------------------------*/
