/*INCLUDES BEGIN-------------------------------------------------------------------*/
#include <stdint.h>
#include <assert.h>
#include "KL46_uart.h"
#include <string.h>
#include "KL46_flash.h"
#include "KL46_bios.h"
#include "SREC_parse.h"
#include "stdlib.h"
/*INCLUDES END---------------------------------------------------------------------*/
/*StATIC DEFINES BEGIN-------------------------------------------------------------*/
#ifndef NULL
#define NULL ((void *)0)
#endif
 typedef enum {
     ADD                          = 0U,
     DELETE                       = 1U,
 } App_Actiont_t;

/*StATIC DEFINES END-------------------------------------------------------------*/
/*STATIC VARIABLES BEGIN-----------------------------------------------------------*/
#define BIOS_CMD_BUFFER_MAX_SIZE        20U
#define BIOS_APP_INFO					(0x3FC00U)

static volatile uint8_t s_cmd_buffer[BIOS_CMD_BUFFER_MAX_SIZE];
static volatile uint32_t s_jump_address = 0;
static volatile uint8_t s_received_count = 0U;
static volatile uint8_t s_is_receiving_cmd = 0;
extern uint32_t first_empty_sector_address;
static uint8_t* CMD_dictionry[] = {
    "LOAD",
    "ERASE",
    "EXIT", 
    "GO",
};

typedef enum {
    BIOS                                = 0U,
    FLASH                               = 1U,
    APPLICATION                         = 2U
} SYSTEM_STATUS_t;

#define SWAP_ENDIAN_32(x) \
    (((x) >> 24) & 0xff) |        /* Move byte 3 to byte 0 */ \
    (((x) << 8) & 0xff0000) |     /* Move byte 1 to byte 2 */ \
    (((x) >> 8) & 0xff00) |       /* Move byte 2 to byte 1 */ \
    (((x) << 24) & 0xff000000)    /* Move byte 0 to byte 3 */


static volatile SYSTEM_STATUS_t system_current_status = BIOS;
static uint8_t* welcome_mess = "Welcome to G2 BIOS\n";
static uint8_t* hints = "<GO:[index]> to go to Application\n<ERASE:[index]> to erase an application\n<LOAD> to flash a new application\n<EXIT> to end the BIOS program\n";
static uint8_t* erase_done_mess = "ERASE DONE\n";
static uint8_t* erase_error_mess = "You don't have permision to erase this erea\n";
/*STATIC VARIABLES END-------------------------------------------------------------*/

/*STATIC PROTOTYPES BEGIN----------------------------------------------------------*/

/**
 * \brief           Received command from user 
 * \param           data 
 */
static void BIOS_Handler(uint8_t data);

/**
 * \brief           Extract and handle user command 
 */
static void BIOS_Cmd_Handler(void);
static void BIOS_Reset_Cmd_Buffer(void);
static void BIOS_Load(void);
static void BIOS_Erase_App(uint8_t app_idx);
static uint32_t String2Hexa(uint8_t* str, uint8_t len);

static uint8_t App_Count();
static void App_Show();
static void App_Action(App_Info_t app_info, App_Actiont_t action);
void App_Get_Info(uint8_t app_idx, App_Info_t* app_info);


/*STATIC PROTOTYPES END------------------------------------------------------------*/

/*DEFINITIONS BEGIN----------------------------------------------------------------*/
void bootloader_jump_to_address(uint32_t address)
{
	if(address != 0xFFFFFFFF) {
		/*Deinit*/
	UART0_DeInit();
    typedef void (*app_reset_handler)(void);
    app_reset_handler resethandler_address;
    uint32_t FLASH_SECTOR2_BASE_ADDRESS = address;

    //disbale interuppts
    __disable_irq();
    /*Set the vector table address off set*/
    SCB->VTOR = FLASH_SECTOR2_BASE_ADDRESS; //0xA000

    uint32_t msp_value = *(__IO uint32_t *)FLASH_SECTOR2_BASE_ADDRESS;
    __set_MSP(msp_value);

    resethandler_address = *(__IO uint32_t *) (FLASH_SECTOR2_BASE_ADDRESS + 4);
    /*Reset the address of vector table*/
    resethandler_address();
	} else {
		BIOS_main();
	}
}

void BIOS_main(void) {
//	 Erase_Multi_Sector(0xA000, 10);
    system_current_status = BIOS;
	UART0_SendString(welcome_mess, strlen(welcome_mess) , 0);
    UART0_SendString(hints, 139, 0);
	App_Show();
    //Overload the handler funtion to handle user command
    UART0_Update_Rx_Handler(&BIOS_Handler);
    //Start receiving
    UART0_ReceiveCharNonBlocking();

    while(system_current_status != APPLICATION)
    {
    	if (system_current_status == FLASH)
    	{
    		BIOS_Load();
    	}
    }

	bootloader_jump_to_address(s_jump_address);
}

static void BIOS_Handler(uint8_t data) {
    /*Store to buffer*/
	if(data == 'b') {
		s_is_receiving_cmd = 1;
	}

	if(s_is_receiving_cmd) {
		s_cmd_buffer[s_received_count] = data;
		++ s_received_count;
		if((data == 'e') || (s_received_count >= BIOS_CMD_BUFFER_MAX_SIZE)) {
			s_is_receiving_cmd = 0;
			BIOS_Cmd_Handler();
    	}
	}
    
}

static void BIOS_Cmd_Handler(void) {
    /*Disable Receiver*/
    UART0_RxEnable(0);
	/*Extract cmd and address*/
	uint8_t* cmd = s_cmd_buffer + 1;  /*Skip the first character is <*/
	uint8_t* value;
	s_cmd_buffer[s_received_count - 1] = '\0'; 

	/*Find the colon value*/
	uint8_t* colon_position = strchr(s_cmd_buffer, ':');

	if(colon_position != NULL) {
		*colon_position = '\0';
		value = colon_position + 1;
	}
	/*Handle the command*/
	if(strcmp(cmd, CMD_dictionry[0]) == 0) {
		/*Go to flash mode*/
		system_current_status = FLASH;
		BIOS_Reset_Cmd_Buffer();

	} else if (strcmp(cmd, CMD_dictionry[1]) == 0) {
		/*Erase application*/
		BIOS_Erase_App(String2Hexa(value, strlen(value)));
	} 

	else if (strcmp(cmd, CMD_dictionry[2]) == 0) {
		/*Exit the bios*/
		system_current_status = APPLICATION;
		App_Info_t app_info;
		App_Get_Info(String2Hexa(0, strlen(value)), &app_info);
		s_jump_address = app_info.app_address;
	}

	else if (strcmp(cmd, CMD_dictionry[3]) == 0) {
		/*GO to application*/
		system_current_status = APPLICATION;
		App_Info_t app_info;
		App_Get_Info(String2Hexa(value, strlen(value)), &app_info);
		s_jump_address = app_info.app_address;

	} else {
		UART0_SendString("Invalid command\n", 17, 0);
	}
    
	BIOS_Reset_Cmd_Buffer();
    if(system_current_status == BIOS) {
        /*Turn on RX for next Command*/
        UART0_ReceiveCharNonBlocking();
    }
}

static void BIOS_Reset_Cmd_Buffer(void) {
    uint8_t index = 0;

    for(index; index < s_received_count; ++index) {
        s_cmd_buffer[index] = NULL;
    }
    s_received_count = 0;
}

static uint32_t String2Hexa(uint8_t* str, uint8_t len) {
    uint32_t result = 0;
    uint8_t index = 0;
    if((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
        index = 2;
    }

    for(index; index < len; ++ index) {
        result = (result << 4);
        if((str[index] >= '0') && (str[index] <= '9')) {
            result += (str[index] - '0');
        } else if ((str[index] >= 'A') && (str[index] <= 'F')) {
            result += (str[index] - 'A' + 10);
        } else {
            result = 0;
        }
    }

    return result;
}

static void BIOS_Load(void) {
	App_Info_t app_info = {0};

	UART0_Update_Rx_Handler(&SREC_Parse);

    UART0_SendString("CHOOSE SREC FILE TO FLASH\n", sizeof("CHOOSE SREC FILE TO FLASH"), 0);

	UART0_ReceiveCharNonBlocking();
	while(!SREC_Load_Done(&app_info));
	
	UART0_RxEnable(0);
	system_current_status = BIOS;
	if (!(app_info.app_address)) {
		UART0_SendString("LOAD ERROR\n", sizeof("LOAD ERROR"), 0);
	}
	else {
		UART0_SendString("LOAD DONE\n", sizeof("LOAD DONE"), 0);
		App_Action(app_info, ADD);
	}
	App_Show();
	/*return to BIOS mode*/
	UART0_Update_Rx_Handler(&BIOS_Handler);
	UART0_ReceiveCharNonBlocking();
}

static void BIOS_Erase_App(uint8_t app_idx) {
	App_Info_t app_info = {0};
	App_Get_Info(app_idx, &app_info);
    if(((app_info.app_address >= 0x400) && (app_info.app_address < 0x7ff)) || \
	    (app_info.app_address <= first_empty_sector_address)               ||  \
		app_idx > App_Count()){
		UART0_SendString(erase_error_mess, strlen(erase_error_mess), 0);
        return;
    } else {
        Erase_Multi_Sector(app_info.app_address, app_info.app_size);
		App_Action(app_info, DELETE);
		UART0_SendString(erase_done_mess, strlen(erase_done_mess), 0);
		App_Show();
    }
}

static uint8_t App_Count()
{
	uint8_t count = 0;
	uint32_t data;
	while(1)
	{
		data = Read_FlashAddress(BIOS_APP_INFO + count * 8);
		if (data != 0xFFFFFFFFU)
		{
			count++;
		}
		else
		{
			break;
		}
	}

	return count;
}

static void App_Show()
{
	uint8_t idx;
	uint8_t app_number = App_Count();
	App_Info_t app_info;

	uint8_t str[] = "APP 1 | ADDRESS 0x00000000 | SIZE 000\n";

	if (app_number == 0)
	{
		UART0_SendString("NO FIRMWARE FOUND\n", sizeof("NO FIRMWARE FOUND\n"), 0);
	}
	else
	{
		for (idx = 0; idx < app_number; idx++)
		{
			App_Get_Info(idx+1, &app_info);
			sprintf(str, "APP %d | ADDRESS 0x%08X | SIZE %03d KB\n", idx + 1, app_info.app_address, app_info.app_size);
			UART0_SendString(str, strlen(str), 0);
		}
	}
}

static void App_Action(App_Info_t app_info, App_Actiont_t action)
{
	uint8_t app_number = App_Count();
	uint8_t idx, app_idx;
	uint32_t * tmp_addr = (uint32_t *)malloc(app_number * sizeof(uint32_t));
	uint32_t * tmp_size = (uint32_t *)malloc(app_number * sizeof(uint32_t));

	for (idx = 0; idx < app_number; idx++)
	{
		tmp_addr[idx] = Read_FlashAddress(BIOS_APP_INFO + 8 * idx);
		tmp_size[idx] = Read_FlashAddress(BIOS_APP_INFO + 8 * idx + 4);

		if (tmp_addr[idx] == app_info.app_address && action == DELETE)
		{
			app_idx = idx;
		}
	}

	Erase_Sector(BIOS_APP_INFO);

	if (action == ADD)
	{
		for (idx = 0; idx < app_number; idx++)
		{
			Program_LongWord(BIOS_APP_INFO + 8 * idx, SWAP_ENDIAN_32(tmp_addr[idx]));
			Program_LongWord(BIOS_APP_INFO + 8 * idx + 4, SWAP_ENDIAN_32(tmp_size[idx]));
		}

		Program_LongWord(BIOS_APP_INFO + 8 * app_number, SWAP_ENDIAN_32(app_info.app_address));
		Program_LongWord(BIOS_APP_INFO + 8 * app_number + 4, SWAP_ENDIAN_32(app_info.app_size));
	}

	else if (action == DELETE)
	{
		idx = 0;
		while(idx < app_number)
		{
			if (idx < app_idx)
			{
				Program_LongWord(BIOS_APP_INFO + 8 * idx, SWAP_ENDIAN_32(tmp_addr[idx]));
				Program_LongWord(BIOS_APP_INFO + 8 * idx + 4, SWAP_ENDIAN_32(tmp_size[idx]));
			}
			else if (idx > app_idx)
			{
				Program_LongWord(BIOS_APP_INFO + 8 * idx - 8, SWAP_ENDIAN_32(tmp_addr[idx]));
				Program_LongWord(BIOS_APP_INFO + 8 * idx - 4, SWAP_ENDIAN_32(tmp_size[idx]));
			}
			idx++;
		}
	}

	free(tmp_addr);
	free(tmp_size);
}

void App_Get_Info(uint8_t app_idx, App_Info_t* app_info)
{
	app_info->app_address = Read_FlashAddress(BIOS_APP_INFO + 8 * app_idx - 8);
	app_info->app_size = Read_FlashAddress(BIOS_APP_INFO + 8 * app_idx - 4);
}

void BIOS_Jump_To_Default_App(void) {
	App_Info_t app_info;
	App_Get_Info(1, &app_info);
    bootloader_jump_to_address(app_info.app_address);
}
/*DEFINITIONS END------------------------------------------------------------------*/

/*END OF FILE----------------------------------------------------------------------*/
