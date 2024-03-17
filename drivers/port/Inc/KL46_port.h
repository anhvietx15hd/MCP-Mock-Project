/**
 * \file            port.h
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-02-18
 */
/*Include guard--------------------------------------------------------------*/
#ifndef _PORT_H_
#define _PORT_H_
/*INCLUDES-------------------------------------------------------------------*/
#include <stdint.h>
#include "MKL46Z4.h"
/*PROTOTYPES-------------------------------------------------------------------*/
typedef void(*Callback_Type)(void);
/*PORTx PCR mux*/
typedef enum {
    PORT_MUX_ANALOG                     = (0U),
    PORT_MUX_GPIO                       = (1U),
    PORT_MUX_ALT2                       = (2U),
    PORT_MUX_ALT3                       = (3U),
    PORT_MUX_ALT4                       = (4U),
    PORT_MUX_ALT5                       = (5U),
    PORT_MUX_ALT6                       = (6U),
    PORT_MUX_ALT7                       = (7U),
} PORT_Pin_Mux_t;

/*PORTx PCR PULL*/
typedef enum {
    PORT_PULL_DOWN                      = (0U),
    PORT_PULL_UP                        = (1U),
    PORT_NO_PULL                        = (2U),
}PORT_Pin_Pull_t;

/*PORTx PCR IRQC - Interupt configuration*/
typedef enum {
    PORT_IRQC_DISABLE                   = (0U),
    PORT_DMA_RISING_EDGE                = (1U),
    PORT_DMA_FAILLING_EDGE              = (2U),
    PORT_DMA_EITHER_EDGE                = (3U),
    PORT_INTERRUPT_LOGIC_ZERO           = (8U),
    PORT_INTERRUPT_RISING_EDGE          = (9U),
    PORT_INTERRUPT_FAILLING_EDGE        = (10U),
    PORT_INTERRUPT_EITHER_EDGE          = (11U),
    PORT_INTERRUPT_LOGIC_ONE            = (12U),
}PORT_Pin_IRQC_t;

/*Check parameters*/
#define IS_PORT(PORT)                   (((PORT) == PORTA) ||  \
                                         ((PORT) == PORTB) ||  \
                                         ((PORT) == PORTC) ||  \
                                         ((PORT) == PORTD) ||  \
                                         ((PORT) == PORTE))

#define IS_PORT_MUX(MUX)                (((MUX) <= PORT_MUX_ALT7) &&  \
                                         ((MUX) >= PORT_MUX_ANALOG))   

#define IS_PORT_PULL(PULL)              (((PULL) <= PORT_NO_PULL) &&  \
                                         ((PULL) >= PORT_PULL_DOWN))

#define IS_PORT_IRQC(IRQC)              (((IRQC) <= PORT_INTERRUPT_LOGIC_ONE) &&  \
                                         ((IRQC) >= PORT_IRQC_DISABLE))
            
#define IS_PORT_PIN_NUMBER(PIN)         (((PIN) <= 31U) &&  \
                                         ((PIN) >= 0U))
/*PORTx Pin config type*/
typedef struct {
    PORT_Pin_Mux_t              mux;
    PORT_Pin_Pull_t             pull;
    PORT_Pin_IRQC_t             irqc;
    Callback_Type               callback;
}PORT_Pin_Config_t;

/**
 * \brief           Init PORTx pin 
 * \param[in]       PORTx 
 * \param[in]       pin_number 
 * \param[in]       config 
 */
void PORT_Pin_Init(PORT_Type* PORTx, uint8_t pin_number, PORT_Pin_Config_t* config);

/**
 * \brief           Enable Interrupt for PORT           
 * \param[in]       PORTx 
 */
void PORT_Enable_Interrupt(PORT_Type* PORTx);

/**
 * \brief           Clear PORT Interrupt flag
 * \param[in]       PORTx 
 * \param[in]       pin_number 
 */
void PORT_Clear_ISF(PORT_Type* PORTx, uint8_t pin_number);

/**
 * \brief           Read the Interrupt flag status
 * \param[in]       PORTx 
 * \param[in]       pin_number 
 * \return          uint8_t : The PORTx Interrupt flag at pin_number pin
 */
uint8_t PORT_Read_ISF(PORT_Type* PORTx, uint8_t pin_number);

#endif /*_PORT_H_*/
/*EOF----------------------------------------------------------------------*/
