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

void CLOCK_PITEnable()
{
	SIM->SCGC6 |= SIM_SCGC6_PIT(1U);
}

uint32_t CLOCK_GetBusClock()
{
	SystemCoreClockUpdate();
	uint32_t outdiv4 = (SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT;
	uint32_t bus_clock = SystemCoreClock/(outdiv4+1);
	return bus_clock;
}
/*DEFINITIONS END------------------------------------------------------------------*/

/*END OF FILE----------------------------------------------------------------------*/
