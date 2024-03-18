/**
 * \file            KL46_device.h
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-03-16
 */
/*Include guard--------------------------------------------------------------*/
#ifndef _DEVICE_H_
#define _DEVICE_H_
/*INCLUDES BEGIN-------------------------------------------------------------*/
#include <stdint.h>
/*INCLUDES END---------------------------------------------------------------*/

/*DEFINES BEGIN--------------------------------------------------------------*/

/*DEFINES END----------------------------------------------------------------*/

/*APIs BEGIN-----------------------------------------------------------------*/
void Device_UART0_Init(uint32_t baudrate);
void Device_ADC_Init();
/*APIs END-------------------------------------------------------------------*/

#endif /*_DEVICE_H_*/
