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
static void PIT_Handler(PIT_Channel_Type channel);
static void Button_Handler(uint8_t pin);

void main(void)
{
<<<<<<< HEAD
	Device_UART0_Init(115200);
=======
	Device_UART0_Init(150000);
>>>>>>> 93f18ee42cfe3efc931b3a400c7b89d4fb1971c0
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
				bootloader_jump_to_address(0xA000);
    			// app1_main();
    		}
    		if (check == 2)
    		{
    			BIOS_main();
    		}
    		check = 0;
    	}
    }
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

/**
 * Check the sector that if it is empty before flashing data to it
 * Check if start address of App is conflic with the boot loader
 * Check if the new app is conflic with others
 * Show the list of app, start address, and size  on flash erea and let user choose the app by the index
 * Add "Exit" command to bios
 */
