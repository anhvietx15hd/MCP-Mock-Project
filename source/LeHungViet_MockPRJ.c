/**
 * \file            LeHungViet_MockPRJ.c
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-03-16
 */
#include "KL46_device.h"
#include "KL46_bios.h"
uint32_t check = 0;

void main(void)
{
    Device_Startup();

    while (1)
    {
    	if(check)
    	{
    		if (check == 1)
    		{
				BIOS_Jump_To_Default_App();
    		}
    		if (check == 2)
    		{
    			BIOS_main();
    		}
    		check = 0;

    	}
    }
}


/**
 * Check if start address of App is conflic with the boot loader
 * Check if the new app is conflic with others
 * Show the list of app, start address, and size  on flash erea and let user choose the app by the index
 * Add "Exit" command to bios
 */
