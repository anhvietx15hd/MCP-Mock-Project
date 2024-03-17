/*INCLUDES-------------------------------------------------------------------*/
#include <assert.h>
#include "KL46_port.h"
#include "KL46_clock.h"
/*DEFINES--------------------------------------------------------------------*/
#ifndef NULL
#define NULL ((void *)0)
#endif
/*STATIC PROTYPES------------------------------------------------------------*/
static Callback_Type PORTA_Callback[32] = {0};
static Callback_Type PORTC_Callback[32] = {0};
static Callback_Type PORTD_Callback[32] = {0};

static void PORT_Callback_Init(PORT_Type* PORTx, uint8_t pin_number, Callback_Type callback);

#define PORT_READ_ISF(PORTx, pin_number) (((PORTx)->ISFR >> (pin_number)) & 1U)
#define PORT_CLEAR_ISF(PORTx, pin_number) ((PORTx)->ISFR |= (1U << (pin_number)))

/*DEFINITIONS-----------------------------------------------------------------*/
void PORT_Pin_Init(PORT_Type* PORTx, uint8_t pin_number, PORT_Pin_Config_t* config) {
    /*Check PORT parameters*/
    assert(IS_PORT(PORTx));
    assert(IS_PORT_PIN_NUMBER(pin_number));
    /*Enable clock for PORTx*/
    Clock_Port_Enable(PORTx);
    /*CLEAR fields*/
    PORTx->PCR[pin_number] &= (~ (PORT_PCR_MUX_MASK | PORT_PCR_IRQC_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK)); /*Clear*/
    /*Config mux field*/
    assert(IS_PORT_MUX(config->pull));
    PORTx->PCR[pin_number] |= (PORT_PCR_MUX(config->mux)); /*Mux*/
    /*Config pull*/
    assert(IS_PORT_PULL(config->pull));
    if(config->pull != PORT_NO_PULL) {
        PORTx->PCR[pin_number] |= (PORT_PCR_PE(1) | PORT_PCR_PS(config->pull)); /*Pull*/
    }
    /*Config irqc*/
    assert(IS_PORT_IRQC(config->irqc));
    if(config->irqc != PORT_IRQC_DISABLE) {
        /*Assign the IRQC function address*/
        PORT_Callback_Init(PORTx, pin_number, config->callback);
        PORTx->PCR[pin_number] |= (PORT_PCR_IRQC(config->irqc)); /*IRQC*/
    }
}

void PORT_Enable_Interrupt(PORT_Type* PORTx){
    /*Only port A C D have Interuprt*/
    assert((PORTx == PORTA) || (PORTx == PORTC) || (PORTx == PORTD));
    if(PORTx == PORTA) {
        NVIC_EnableIRQ(PORTA_IRQn);
    } else {
         NVIC_EnableIRQ(PORTC_PORTD_IRQn);
    }
}

void PORT_Clear_ISF(PORT_Type* PORTx, uint8_t pin_number) {
    /*Check parameters*/
    /*Only port A C D have Interuprt*/
    assert((PORTx == PORTA) || (PORTx == PORTC) || (PORTx == PORTD));
    assert(IS_PORT_PIN_NUMBER(pin_number));

    (PORTx->ISFR) |= (1U << pin_number);
}

uint8_t PORT_Read_ISF(PORT_Type* PORTx, uint8_t pin_number) {
    /*Check parameters*/
    /*Only port A C D have Interuprt*/
    assert((PORTx == PORTA) || (PORTx == PORTC) || (PORTx == PORTD));
    assert(IS_PORT_PIN_NUMBER(pin_number));

    return (((PORTx->ISFR) >> pin_number) & 1U);
}


void PORTC_PORTD_IRQHandler(void) {
    uint8_t index;
    /*Find interrupt position on PORTC*/
    if(((SIM->SCGC5 >> SIM_SCGC5_PORTC_SHIFT) & 1U)) {  //Just check the flag if port is clock granted
        for (index = 0; index < 32; ++index) {
            if(PORT_READ_ISF(PORTC, index) != 0U){
                PORT_CLEAR_ISF(PORTC, index); /*Clear interrupt flag*/
                PORTC_Callback[index]();
            }
        }
    }
    /*Find interrupt position on PORTD*/
    if(((SIM->SCGC5 >> SIM_SCGC5_PORTD_SHIFT) & 1U)) {  //Just check the flag if port is clock granted
        for (index = 0; index < 32; ++index) {
            if(PORT_READ_ISF(PORTD, index) != 0U){
                PORT_CLEAR_ISF(PORTD, index); /*Clear interrupt flag*/
                PORTD_Callback[index]();
            }
        }
    } 
}

static void PORT_Callback_Init(PORT_Type* PORTx, uint8_t pin_number, Callback_Type callback) {
    /*Check PORT parameters*/
    assert(IS_PORT(PORTx));
    assert(IS_PORT_PIN_NUMBER(pin_number));
    
    switch ((uint32_t)PORTx) {
        case PORTA_BASE: 
            PORTA_Callback[pin_number] = callback;
            break;
        case PORTC_BASE: 
            PORTC_Callback[pin_number] = callback;
            break;
        case PORTD_BASE: 
            PORTD_Callback[pin_number] = callback;
            break;
        default:
            break;
    }
}
/*EOF----------------------------------------------------------------------*/
