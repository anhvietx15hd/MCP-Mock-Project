/*INCLUDES BEGIN-------------------------------------------------------------------*/
#include <stdint.h>
#include <assert.h>
#include "KL46_clock.h"
/*INCLUDES END---------------------------------------------------------------------*/

/*DEFINITIONS BEGIN----------------------------------------------------------------*/
void Clock_Port_Enable(PORT_Type* PORTx) {
    switch ((uint32_t)PORTx) {
        case PORTA_BASE: 
            SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
            break;
        case PORTB_BASE: 
            SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
            break;
        case PORTC_BASE: 
            SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
            break;
        case PORTD_BASE: 
            SIM->SCGC5 |= SIM_SCGC5_PORTD(1);
            break;
        case PORTE_BASE: 
            SIM->SCGC5 |= SIM_SCGC5_PORTE(1);
            break;
        default: 
            break;
    }
}

void Clock_Port_Diable(PORT_Type* PORTx) {
    switch ((uint32_t)PORTx) {
        case PORTA_BASE: 
            SIM->SCGC5 &= (~SIM_SCGC5_PORTA(1));
            break;
        case PORTB_BASE: 
            SIM->SCGC5 &= (~SIM_SCGC5_PORTB(1));
            break;
        case PORTC_BASE: 
            SIM->SCGC5 &= (~SIM_SCGC5_PORTC(1));
            break;
        case PORTD_BASE: 
            SIM->SCGC5 &= (~SIM_SCGC5_PORTD(1));
            break;
        case PORTE_BASE: 
            SIM->SCGC5 &= (~SIM_SCGC5_PORTE(1));
            break;
        default:
            break;
    }
}

void Clock_UART0_Enable(void) {
    SIM->SCGC4 |= (SIM_SCGC4_UART0(1));
}

void Clock_UART0_Diable(void) {
    SIM->SCGC4 &= (~SIM_SCGC4_UART0_MASK);
}
/*DEFINITIONS END------------------------------------------------------------------*/

/*END OF FILE----------------------------------------------------------------------*/
