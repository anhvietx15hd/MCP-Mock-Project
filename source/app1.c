/*
 * app1.c
 *
 *  Created on: Mar 18, 2024
 *      Author: DELL
 */

#include "KL46_device.h"
#include "KL46_timer.h"

void app1_main()
{
	Device_UART0_Init(9600);
	UART0_SendString("app1\n", sizeof("app1\n"), 0);

	while(1)
	{

	}
}
