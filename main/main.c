#include "config.h"
#include "middleware.h"

CallBack_Type boot_mode = NULL;
CallBack_Type app_mode  = NULL;

void app1(void)
{
	M_Toggle_LED(LED1_GPIO, LED1_PIN);
}

void app2(void)
{
	M_Toggle_LED(LED2_GPIO, LED2_PIN);
}

void boot_loader(void)
{
	if ( PORT_InterruptFlag_isSet(SW1_PORT, SW1_PIN) )
	{
		PORT_Clear_InterruptFlag(SW1_PORT, SW1_PIN);
		boot_mode();
	}
	else
	{
		if ( app_mode != NULL)
		{
			app_mode();
		}
		else
		{
			boot_mode();
		}
	}
}

void PIT_IRQHandler(void)
{
	if ( PIT_InterruptFlag_isSet(1) )
	{
		PIT_Clear_InterruptFlag(1);
		PIT_Enable(1U);
		boot_loader();
	}
}

void main(void)
{
	boot_mode = app1;
//	app_mode  = app2;

	M_Enable_Modules();
	M_Enable_IRQHandler();
	M_Init_Board();
	M_Config_LED();
	M_Init_Timer(1, 3000);

	M_Start_Timer(1);

	while(1);
}
