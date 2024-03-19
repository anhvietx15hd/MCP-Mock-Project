/**
 * \file            KL46_uart.h
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-03-16
 */
/*Include guard--------------------------------------------------------------*/
#ifndef _UART_H_
#define _UART_H_
/*INCLUDES BEGIN-------------------------------------------------------------*/
#include <stdint.h>
#include "MKL46Z4.h"
/*INCLUDES END---------------------------------------------------------------*/

/*DEFINES BEGIN--------------------------------------------------------------*/
#define IS_UART(x)                      (((x) == UART0_BASE) ||  \
                                         ((x) == UART1_BASE) ||  \
                                         ((x) == UART2_BASE))

typedef void(*UART0_Callback)(uint8_t);

typedef enum
{
	UART_SUCCESS,
	UART_TIMEOUT,
} UART_Status_Type;

typedef enum
{
	UART_DATA_8BIT,
	UART_DATA_9BIT,
	UART_DATA_10BIT,
} UART_Data_Length_Type;

typedef enum
{
	UART_PARITY_NONE = 0U,
	UART_PARITY_EVEN = 2U,
	UART_PARITY_ODD = 3U,
} UART_Parity_Type;

typedef enum
{
	UART_SBNS_1BIT,
	UART_SBNS_2BIT,
} UART_Stop_Bit_Type;

typedef enum
{
	UART_LSB_FIRST,
	UART_MSB_FIRST,
} UART_MSB_LSB_Type;

typedef struct
{
	PORT_Type* PORT;
	uint8_t pin;
} UART_Pin_Config_Type;

typedef struct
{
	UART_Pin_Config_Type	tx;
	UART_Pin_Config_Type 	rx;
	uint8_t 				txEnable;
	uint8_t					rxEnable;
	uint32_t				baudrate;
	UART_Data_Length_Type	dataLength;
	UART_Stop_Bit_Type		stopBit;
	UART_Parity_Type		parity;
	UART_MSB_LSB_Type		MsbLsb;
	UART0_Callback			RxCallback;
} UART_Config_Type;
/*DEFINES END----------------------------------------------------------------*/

/*APIs BEGIN-----------------------------------------------------------------*/
/**
 * \brief           Config for UART peripherals
 * \param           config 
 */
void UART0_Init(UART_Config_Type* config);

/**
 * \brief           Send single character via UART0 
 * \param           ch 
 * \param           timeout 
 * \return          UART_Status_Type 
 */
UART_Status_Type UART0_SendChar(uint8_t ch, uint32_t timeout);

/**
 * \brief           Send String via UART0 
 * \param           str 
 * \param           len 
 * \param           timeout 
 * \return          UART_Status_Type 
 */
UART_Status_Type UART0_SendString(uint8_t* str, uint8_t len, uint32_t timeout);

UART_Status_Type UART0_ReceiveCharBlocking(uint8_t* rxChar, uint32_t timeout);
void UART0_ReceiveCharNonBlocking();

void UART0_RxEnable(uint8_t status);

void UART0_Update_Rx_Handler(UART0_Callback RxCallback);

void UART0_DeInit(void);
/*APIs END-------------------------------------------------------------------*/

#endif /*_UART_H_*/