/**
 * \file            LeHungViet_MockPRJ.c
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-03-16
 */
#include "KL46_device.h"
#include "KL46_bios.h"
#include "KL46_pit.h"
#include "KL46_port.h"

#define SW1_PORT		PORTC
#define SW1_PIN			3U
#define SW2_PORT		PORTC
#define SW2_PIN			12U

uint32_t check = 0;
extern void app1_main();
static void PIT_Handler(PIT_Channel_Type channel);
static void Button_Handler(uint8_t pin);

void main(void)
{
	Erase_Multi_Sector(0xa000, 10);

    Device_UART0_Init(9600);
    UART0_SendChar('A', 0);
    UART0_SendChar('\n', 0);

    PIT_Config_Type PitConf = {
    		.timeout = 3000,
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

    PIT_StartTimer(PIT_CHANNEL_0);

    while (1)
    {
    	if(check)
    	{
    		if (check == 1)
    		{
    			app1_main();
    		}
    		if (check == 2)
    		{
    			BIOS_main();
    		}
    		check = 0;
    	}
    }

    /*Idea
    * Giới hạn số từ trong lệnh
    * Khi bắt được ký tự kết thúc lệnh hay đạt giới hạn lệnh -> diable RX và xử lý lệnh, xử lý xong enble lại
    * Sửa lại code để gen baudrate cao hơn*/
}

static void PIT_Handler(PIT_Channel_Type channel)
{
	PIT_StopTimer(PIT_CHANNEL_0);
	PIT_DeInit(PIT_CHANNEL_0);
	PORT_Pin_DeInit(SW1_PORT, SW1_PIN);
	check = 1;
}

static void Button_Handler(uint8_t pin)
{
	PIT_StopTimer(PIT_CHANNEL_0);
	PIT_DeInit(PIT_CHANNEL_0);
	PORT_Pin_DeInit(SW1_PORT, SW1_PIN);
	check = 2;
}
