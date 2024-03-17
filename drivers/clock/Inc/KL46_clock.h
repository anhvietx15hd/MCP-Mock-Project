/**
 * \file            KL46_clock.h
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-03-16
 */
/*Include guard--------------------------------------------------------------*/
#ifndef _CLOCK_H_
#define _CLOCK_H_
/*INCLUDES BEGIN-------------------------------------------------------------*/
#include <stdint.h>
#include "MKL46Z4.h"
/*INCLUDES END---------------------------------------------------------------*/

/*APIs BEGIN-----------------------------------------------------------------*/
/**
 * \brief           Enable clock for PORT peripherals 
 * \param           PORTx 
 */
void Clock_Port_Enable(PORT_Type* PORTx);

/**
 * \brief           Diable clock for PORT peripherals 
 * \param           PORTx 
 */
void Clock_Port_Disable(PORT_Type* PORTx);

/**
 * \brief           Enable clock for UART0 peripheral
 */
void Clock_UART0_Enable(void);

/**
 * \brief           Diable clock for UART0 peripheral
 */
void Clock_UART0_Diable(void);
/*APIs END-------------------------------------------------------------------*/

#endif /*_CLOCK_H_*/
/*EOF----------------------------------------------------------------------*/
