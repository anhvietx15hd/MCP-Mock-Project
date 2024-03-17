/*INCLUDES BEGIN-------------------------------------------------------------------*/
#include <stdint.h>
#include <assert.h>
#include "KL46_uart.h"
#include "KL46_timer.h"
/*INCLUDES END---------------------------------------------------------------------*/

/*STATIC VARIABLES BEGIN-----------------------------------------------------------*/
static volatile uint8_t cur_data[6];
static volatile uint8_t count = 0;
/*STATIC VARIABLES END-------------------------------------------------------------*/

void received(uint8_t data);
/*DEFINITIONS BEGIN----------------------------------------------------------------*/
void Device_UART0_Init(uint32_t baudrate) {
    UART_Config_Type config;
    /*TX*/
    config.tx.PORT = PORTA;
    config.tx.pin = 2;
    config.txEnable = 1;
    /*RX*/
    config.rx.PORT = PORTA;
    config.rx.pin = 1;
    config.rxEnable = 1;
    /*baudrate*/
    config.baudrate = baudrate;
    /*Data length*/
    config.dataLength = UART_DATA_8BIT;
    /*Stop bit*/
    config.stopBit = UART_SBNS_1BIT;
    /*parity*/
    config.parity = UART_PARITY_NONE;
    /*Significant*/
    config.MsbLsb = UART_LSB_FIRST;

    UART0_Init(&config);
}

/*DEFINITIONS END------------------------------------------------------------------*/

/*END OF FILE----------------------------------------------------------------------*/
