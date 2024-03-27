/*INCLUDES BEGIN-------------------------------------------------------------------*/
#include <stdint.h>
#include <assert.h>
#include "KL46_clock.h"
#include "KL46_port.h"
#include "KL46_uart.h"
/*INCLUDES END---------------------------------------------------------------------*/

/*DEFINES BEGIN--------------------------------------------------------------------*/
#ifndef NULL
#define NULL ((void *)0)
#endif

#define MIN_OSR							(3U)
#define MAX_OSR							(31U)
/*DEFINES END--------------------------------------------------------------------*/

/*STATIC VARIABLES BEGIN-----------------------------------------------------------*/
static UART0_Callback RxCompleteCallback = NULL;
static UART0_Callback TxCompleteCallback = NULL;
static volatile uint8_t rxData;
/*STATIC VARIABLES END-------------------------------------------------------------*/

/*STATIC PROTOTYPES BEGIN-----------------------------------------------------------*/
static uint8_t UART_Find_OSR(uint32_t baudrate);
/*STATIC PROTOTYPES END-------------------------------------------------------------*/

/*DEFINITIONS BEGIN----------------------------------------------------------------*/
void UART0_RxEnable(uint8_t status)
{
	if (status)
	{
		UART0->C2 |= UART0_C2_RE(1U);
	}
	else
	{
		UART0->C2 &= ~UART0_C2_RE_MASK;
		rxData = UART0->D;
	}
}

static inline void UART0_TxEnable(uint8_t status)
{
	if (status)
	{
		UART0->C2 |= UART0_C2_TE(1U);
	}
	else
	{
		UART0->C2 &= ~UART0_C2_TE_MASK;
	}
}

void UART0_Init(UART_Config_Type* config)
{

	uint8_t osr;
    uint16_t sbr;

	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1U);  //MCGFLLCLK
	Clock_UART0_Enable();

	PORT_Pin_Config_t port_conf = {
			.pull = PORT_PULL_UP,
	};

	if (config->txEnable)
	{
		if (config->tx.PORT == PORTE && config->tx.pin == 20U)
		{
			port_conf.mux = PORT_MUX_ALT4;
		}
		else if (config->tx.PORT == PORTA && config->tx.pin == 2U)
		{
			port_conf.mux = PORT_MUX_ALT2;
		}
		else if (config->tx.PORT == PORTA && config->tx.pin == 14U)
		{
			port_conf.mux = PORT_MUX_ALT3;
		}
		else if (config->tx.PORT == PORTB && config->tx.pin == 17U)
		{
			port_conf.mux = PORT_MUX_ALT3;
		}
		else if (config->tx.PORT == PORTD && config->tx.pin == 7U)
		{
			port_conf.mux = PORT_MUX_ALT3;
		}

		PORT_Pin_Init(config->tx.PORT, config->tx.pin, &port_conf);
	}

	if (config->rxEnable)
	{
		if (config->rx.PORT == PORTE && config->rx.pin == 21U)
		{
			port_conf.mux = PORT_MUX_ALT4;
		}
		else if (config->rx.PORT == PORTA && config->rx.pin == 1U)
		{
			port_conf.mux = PORT_MUX_ALT2;
		}
		else if (config->rx.PORT == PORTA && config->rx.pin == 15U)
		{
			port_conf.mux = PORT_MUX_ALT3;
		}
		else if (config->rx.PORT == PORTB && config->rx.pin == 16U)
		{
			port_conf.mux = PORT_MUX_ALT3;
		}
		else if (config->rx.PORT == PORTD && config->rx.pin == 6U)
		{
			port_conf.mux = PORT_MUX_ALT3;
		}

		PORT_Pin_Init(config->rx.PORT, config->rx.pin, &port_conf);
	}

	UART0_RxEnable(0);
	UART0_TxEnable(0);

    osr = UART_Find_OSR(config->baudrate);
    sbr = (uint16_t)((DEFAULT_SYSTEM_CLOCK ) / ((osr + 1) * config->baudrate));

	/*Set the OSR at c4 register*/
    UART0->C4 = osr;
	if((osr >= 3) && (osr <= 6)) {
		UART0->C5 |= UART0_C5_BOTHEDGE(1U); // both edge
	}
    // Set the Baud Rate Divisor
    UART0->BDH = UART_BDH_SBR((sbr >> 8) & 0x1F);
    UART0->BDL = UART_BDL_SBR(sbr & 0xFF);

	if (config->dataLength != UART_DATA_10BIT)
	{
		UART0->C4 &= ~UART0_C4_M10_MASK;
		UART0->C1 &= ~UART0_C1_M_MASK;
		UART0->C1 |= UART0_C1_M(config->dataLength);
	}
	else
	{
		UART0->C4 |= UART0_C4_M10(1U);
	}

	if (config->parity != UART_PARITY_NONE)
	{
		UART0->C1 |= UART0_C1_PE(1U);
		UART0->C1 |= UART0_C1_PT(config->parity & 1U);
	}

	if (config->stopBit != UART_SBNS_1BIT)
	{
		UART0->BDH |= UART_BDH_SBNS(1U);
	}

	if (config->MsbLsb != UART_LSB_FIRST)
	{
		UART0->S2 |= UART0_S2_MSBF(1U);
	}

	RxCompleteCallback = config->RxCallback;
}

UART_Status_Type UART0_SendChar(uint8_t ch, uint32_t timeout)
{
	UART0_TxEnable(1);

	UART_Status_Type status = UART_TIMEOUT;

	if (timeout == 0)
	{
		while((UART0->S1 & UART0_S1_TDRE_MASK) == 0);
		UART0->D = ch;
		while((UART0->S1 & UART0_S1_TC_MASK) == 0);
		status = UART_SUCCESS;
	}
	else
	{
		while((UART0->S1 & UART0_S1_TDRE_MASK) == 0U && --timeout);
		if ((UART0->S1 & UART0_S1_TDRE_MASK) != 0U)
		{
			UART0->D = ch;
			while((UART0->S1 & UART0_S1_TC_MASK) == 0U && --timeout);
			if ((UART0->S1 & UART0_S1_TC_MASK) == 0U)
			{
				status = UART_SUCCESS;
			}
		}
	}

	UART0_TxEnable(0);

	return status;
}

UART_Status_Type UART0_SendString(uint8_t* str, uint8_t length, uint32_t timeout)
{
	uint8_t i = 0;
	UART_Status_Type status = UART_TIMEOUT;
	for (i = 0; i < length; i++)
	{
		status = UART0_SendChar(str[i], timeout);
		if (status != UART_SUCCESS)
		{
			break;
		}
	}

	return status;
}

UART_Status_Type UART0_ReceiveCharBlocking(uint8_t* rxChar, uint32_t timeout)
{
	UART_Status_Type status = UART_TIMEOUT;

	UART0_RxEnable(1);

	while((UART0->S1 & UART0_S1_RDRF_MASK) == 0U && --timeout);
	if ((UART0->S1 & UART0_S1_RDRF_MASK) == 0U)
	{
		*rxChar = UART0->D;
		status = UART_SUCCESS;
	}

	UART0_RxEnable(0);

	return status;
}

void UART0_ReceiveCharNonBlocking()
{	
	UART0->C2 |= UART0_C2_RIE(1U);
	UART0->S1 |= UART0_S1_OR_MASK;
	UART0->D;
	NVIC_EnableIRQ(UART0_IRQn);

	UART0_RxEnable(1);
}

void UART0_IRQHandler()
{
	if ((UART0->S1 & UART0_S1_RDRF_MASK) != 0U)
	{
		rxData = UART0->D;
		if (RxCompleteCallback)
		{
			RxCompleteCallback(rxData);
		}
	}
}

void UART0_Update_Rx_Handler(UART0_Callback RxCallback) {
    RxCompleteCallback = RxCallback;
}

void UART0_DeInit(void) {
	UART0_RxEnable(0);
	UART0_TxEnable(0);
	NVIC_DisableIRQ(UART0_IRQn);

	SIM->SOPT2 &= (~SIM_SOPT2_UART0SRC_MASK);
	UART0->BDH = 0;
	UART0->BDL = (1<<2);
	UART0->C1 = 0;
	UART0->C2 = 0;
	UART0->C3 = 0;


	Clock_UART0_Diable();
}

static uint8_t UART_Find_OSR(uint32_t baud_rate){
    uint8_t index;
    uint8_t osr;
    uint16_t error;
    uint16_t sbr;
    uint16_t min_error = 5000u;
    uint32_t temp_baud_rate;
    osr = MIN_OSR;
    for(index = MIN_OSR; index <= MAX_OSR; index ++){
        /*calculate sbr with osr*/
        sbr = (uint16_t)(DEFAULT_SYSTEM_CLOCK / ((index + 1) * baud_rate));
        /*calculate baudrate with recent sbr*/
        temp_baud_rate = (uint32_t)(DEFAULT_SYSTEM_CLOCK / ((index + 1) * sbr));
        /*find the best osr with smallest baud rate error*/
        error = abs(temp_baud_rate - baud_rate);
        if(error < min_error){
            min_error = error;
            osr = index;
        }
    }
    return osr;
}
/*DEFINITIONS END------------------------------------------------------------------*/

/*END OF FILE----------------------------------------------------------------------*/
