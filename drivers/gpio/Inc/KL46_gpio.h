/**
 * \file            gpio.h
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-02-18
 */
/*Include guard--------------------------------------------------------------*/
#ifndef _GPIO_H_
#define _GPIO_H_
/*INCLUDES-------------------------------------------------------------------*/
#include <stdint.h>
#include "MKL46Z4.h"
/*PROTOTYPES-----------------------------------------------------------------*/
/*GPIO Direction*/
typedef enum {
    GPIO_INPUT                      = (0U),
    GPIO_OUTPUT                     = (1U),
}GPIO_Direction_t;
/*GPIO Logic Level*/
typedef enum {
    GPIO_LOGIC_LOW                  = (0U),
    GPIO_LOGIC_HIGH                 = (1U),
}GPIO_Logic_t;
/*GPIO Cofig Type*/
typedef struct {
    GPIO_Direction_t            direction;
    GPIO_Logic_t                default_logic;
}GPIO_Pin_Config_t;

#define IS_GPIO(GPIO)                   (((GPIO) == GPIOA) ||  \
                                         ((GPIO) == GPIOB) ||  \
                                         ((GPIO) == GPIOC) ||  \
                                         ((GPIO) == GPIOD) ||  \
                                         ((GPIO) == GPIOE))

#define IS_GPIO_DIRECTION(DIR)          (((DIR) == GPIO_INPUT) ||  \
                                         ((DIR) == GPIO_OUTPUT))

#define IS_GPIO_LOGIC(LOGIC)            (((LOGIC) == GPIO_LOGIC_LOW) ||  \
                                         ((LOGIC) == GPIO_LOGIC_HIGH))        

#define IS_GPIO_PIN_NUMBER(PIN)         (((PIN) >= 0U )  ||  \
                                         ((PIN) <= 31U))

/**
 * \brief           Init GPIO pin 
 * \param[in]       GPIOx 
 * \param[in]       pin_number 
 * \param[in]       config 
 */
void GPIO_Pin_Init(GPIO_Type* GPIOx, uint8_t pin_number, GPIO_Pin_Config_t* config);

/**
 * \brief           Toggle GPIO Pin output 
 * \param[in]       GPIOx 
 * \param[in]       pin_number 
 */
void GPIO_Toggle_Pin(GPIO_Type* GPIOx, uint8_t pin_number);

void GPIO_Set_Pin(GPIO_Type* GPIOx, uint8_t pin_number);

void GPIO_Clear_Pin(GPIO_Type* GPIOx, uint8_t pin_number);

#endif /*_GPIO_H_*/
/*EOF----------------------------------------------------------------------*/
