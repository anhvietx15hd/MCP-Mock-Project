/*INCLUDES BEGIN-------------------------------------------------------------------*/
#include <stdint.h>
#include <assert.h>
#include "KL46_uart.h"
#include "KL46_timer.h"
#include "KL46_pit.h"
#include "KL46_port.h"
#include "KL46_device.h"
/*INCLUDES END---------------------------------------------------------------------*/

/*STATIC DEFINES BEGIN-----------------------------------------------------------*/
#define SW1_PORT		PORTC
#define SW1_PIN			3U
#define SW2_PORT		PORTC
#define SW2_PIN			12U
/*STATIC DEFINES END-------------------------------------------------------------*/

/*STATIC VARIABLES BEGIN-----------------------------------------------------------*/
static volatile uint8_t cur_data[6];
static volatile uint8_t count = 0;

static void PIT_Handler(PIT_Channel_Type channel);
static void Button_Handler(uint8_t pin);
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

void Device_Timer_Init(uint16_t time) {
    PIT_Config_Type PitConf = {
   		.timeout = time,
   		.pCallback = &PIT_Handler,
   		.tie = PIT_TIE_ENABLE,
   };

    PORT_Pin_Config_t ButtonConf = {
    		.mux = PORT_MUX_GPIO,
    		.pull = PORT_PULL_UP,
    		.callback = &Button_Handler,
    		.irqc = PORT_INTERRUPT_FAILLING_EDGE,
    };

    PIT_Init(PIT_CHANNEL_0, &PitConf);

    PORT_Pin_Init(SW1_PORT, SW1_PIN, &ButtonConf);
    PORT_Enable_Interrupt(SW1_PORT);
}

static void PIT_Handler(PIT_Channel_Type channel)
{
	PIT_DeInit(PIT_CHANNEL_0);
	PORT_Pin_DeInit(SW1_PORT, SW1_PIN);
	check = 1;
}

static void Button_Handler(uint8_t pin)
{
	PIT_DeInit(PIT_CHANNEL_0);
	PORT_Pin_DeInit(SW1_PORT, SW1_PIN);
	check = 2;
}

void Device_Timer_Start() {
    PIT_StartTimer(PIT_CHANNEL_0);
}

void Device_Startup(void) {
    UART0_SendString("Welcome to G2\n", 14, 0);
}

/*DEFINITIONS END------------------------------------------------------------------*/

/*END OF FILE----------------------------------------------------------------------*/
