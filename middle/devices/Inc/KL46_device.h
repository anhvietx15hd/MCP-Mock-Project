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
/*GLOBAL VARIABLES BEGIN--------------------------------------------------------------*/
extern uint32_t check;
/*GLOBAL VARIABLES  END----------------------------------------------------------------*/

/*APIs BEGIN-----------------------------------------------------------------*/
void Device_UART0_Init(uint32_t baudrate);
void Device_ADC_Init();
void Device_Timer_Init(uint16_t time);
void Device_Timer_Start();
void Device_Startup(void);
/*APIs END-------------------------------------------------------------------*/

#endif /*_DEVICE_H_*/
