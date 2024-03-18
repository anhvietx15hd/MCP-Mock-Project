/*INCLUDES BEGIN-------------------------------------------------------------------*/
#include <stdint.h>
#include <assert.h>
#include "KL46_uart.h"
#include <string.h>
#include "KL46_flash.h"
#include "KL46_bios.h"
#include "SREC_parse.h"
/*INCLUDES END---------------------------------------------------------------------*/
#ifndef NULL
#define NULL ((void *)0)
#endif
/*STATIC VARIABLES BEGIN-----------------------------------------------------------*/
#define BIOS_CMD_BUFFER_MAX_SIZE        20U
static volatile uint8_t s_cmd_buffer[BIOS_CMD_BUFFER_MAX_SIZE];
static volatile uint8_t s_received_count = 0U;
static uint8_t* CMD_dictionry[] = {
    "LOAD",
    "ERASE"
};

typedef enum {
    BIOS                                = 0U,
    FLASH                               = 1U,
    APPLICATION                         = 2U
} SYSTEM_STATUS_t;

static volatile SYSTEM_STATUS_t system_current_status = BIOS;
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
static uint32_t BIOS_Load(void);
static void BIOS_Erase(uint32_t address);
static uint32_t String2Hexa(uint8_t* str, uint8_t len);
/*STATIC PROTOTYPES END------------------------------------------------------------*/

/*DEFINITIONS BEGIN----------------------------------------------------------------*/
void bootloader_jump_to_address(uint32_t address)
{
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
}

void BIOS_main(void) {
    //Overload the handler funtion to handle user command
    UART0_Update_Rx_Handler(&BIOS_Handler);
    //Start receiving
    UART0_ReceiveCharNonBlocking();

    while(1)
    {
    	if (system_current_status == FLASH)
    	{
    		uint32_t address = BIOS_Load();
    		system_current_status = APPLICATION;
    		bootloader_jump_to_address(address);
    	}
    }
}

static void BIOS_Handler(uint8_t data) {
    /*Store to buffer*/
    s_cmd_buffer[s_received_count] = data;
    ++ s_received_count;
    if((data == 'e') || (s_received_count >= BIOS_CMD_BUFFER_MAX_SIZE)) {
        BIOS_Cmd_Handler();
    }
}

static void BIOS_Cmd_Handler(void) {
    /*Disable Receiver*/
    UART0_RxEnable(0);
    /*Check the validation of user command*/
    if((s_cmd_buffer[0] == 'b') && (s_cmd_buffer[s_received_count - 1] == 'e')) {
        /*Extract cmd and address*/
        uint8_t* cmd = s_cmd_buffer + 1;  /*Skip the first character is <*/
        uint8_t* address;
        s_cmd_buffer[s_received_count - 1] = '\0'; 

        /*Find the colon address*/
        uint8_t* colon_position = strchr(s_cmd_buffer, ':');

        if(colon_position != NULL) {
            *colon_position = '\0';
            address = colon_position + 1;
        }
        /*Handle the command*/
        if(strcmp(cmd, CMD_dictionry[0]) == 0) {
        	system_current_status = FLASH;
        } else if (strcmp(cmd, CMD_dictionry[1]) == 0) {
            BIOS_Erase(String2Hexa(address, strlen(address)));
        } else {
            UART0_SendString("Invalid command\n", 17, 0);
        }
    } else {
        UART0_SendString("Invalid command\n", 17, 0);
    }
    
    if(system_current_status == BIOS) {
        /*Turn on RX for next Command*/
        BIOS_Reset_Cmd_Buffer();
        UART0_RxEnable(1);
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

static uint32_t BIOS_Load(void) {
	uint32_t load_address = 0;

	UART0_Update_Rx_Handler(&SREC_Parse);

    UART0_SendString("LOADING\n", sizeof("LOADING\n"), 0);

	UART0_ReceiveCharNonBlocking();
	while(!SREC_Load_Done(&load_address));

	UART0_RxEnable(0);
	UART0_SendString("LOAD DONE\n", sizeof("LOAD DONE\n"), 0);

	if (!load_address) {
		UART0_SendString("LOAD ERROR\n", sizeof("LOAD ERROR\n"), 0);
	}

	return load_address;
}

static void BIOS_Erase(uint32_t address) {
    if(((address >= 0x400) && (address < 0x7ff)) || (address == 0)){
        return;
    } else {
        Erase_Sector(address);
    }
}

/*DEFINITIONS END------------------------------------------------------------------*/

/*END OF FILE----------------------------------------------------------------------*/
