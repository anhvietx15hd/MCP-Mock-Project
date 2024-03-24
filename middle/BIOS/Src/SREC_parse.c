/*
 * SREC_parse.c
 *
 *  Created on: Mar 17, 2024
 *      Author: DELL
 */

#include "SREC_parse.h"
#include <math.h>
#include "KL46_uart.h"
#include "KL46_flash.h"

#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define ASCII_TO_HEX(ch) ((ch >= '0' && ch <= '9') ? (ch - '0') : \
						    ((ch >= 'A' && ch <= 'F') ? (ch - 'A' + 10U) : (ASCII_ERROR)))

static char *mess = "SREC file is in wrong format\n";

static volatile SREC_Status_t status = SREC_START;
static volatile uint32_t app_address = 0;
static volatile uint8_t idx = 0, dataIdx = 0;
static volatile uint8_t bytecount = 0, checksum = 0;
static volatile uint8_t address_digit;
static volatile uint8_t dataArray[4] = {0};
static volatile uint32_t address, sum;
static volatile uint8_t load_file_done = 0;
static volatile uint8_t converted_number = 0;


void SREC_Parse(uint8_t ch)
{
	converted_number = ASCII_TO_HEX(ch);

	switch (status)
	{
		case SREC_START:
			if (ch == 'S') {
				status = SREC_TYPE;
			} else {
				status = SREC_ERROR;
				UART0_SendChar('5', 0);
			}
			break;

		case SREC_TYPE:
			if (ch > '0' && ch < '4') {
				address_digit = ((ch - '0') + 1) * 2;
				status = SREC_BYTECOUNT;
				idx = dataIdx = sum = 0;
			} else if (ch >= '7' && ch <= '9') {
				status = SREC_EOF;
			} else if (ch == '0') {
				status = SREC_HEADER;
			} else {
				status = SREC_ERROR;
				UART0_SendChar('4', 0);
			}
			break;

		case SREC_HEADER:
			if (ch == '\n') {
				status = SREC_START;
			}
			break;

		case SREC_BYTECOUNT:
			if (converted_number != ASCII_ERROR) {
				if(idx == 0) {
					bytecount = (converted_number <<4);
					idx ++;
				} else if (idx == 1) {
					status = SREC_ADDRESS;
					bytecount += converted_number;
					sum += bytecount;
					idx = address = 0;
				} 
			} else {
				status = SREC_ERROR;
 				UART0_SendChar('3', 0);
			}
			break;


		case SREC_ADDRESS:
			if (converted_number != ASCII_ERROR)
			{
				if (idx < address_digit) {
					address = ((address << 4) + converted_number);
					idx++;
				}
				if (idx >= address_digit) {
					status = SREC_DATA;
					idx = dataIdx = 0;
					if (app_address == 0) app_address = address;
//					sum += (uint8_t)address + (uint8_t)(address >> 8);
					sum += (uint8_t)address + (uint8_t)(address >> 8) + (uint8_t)(address >> 16) + (uint8_t)(address >> 24);
				}
			} else {
				status = SREC_ERROR;
				UART0_SendChar('2', 0);
			}
			break;

		case SREC_DATA:
			if (converted_number != ASCII_ERROR) {
				if (bytecount - address_digit/2 >= 2) {
					if (idx < 8) {
						/*Store each byte to array*/
						if (idx % 2 == 0) {
							dataArray[idx /2] = (converted_number << 4);
							sum += (converted_number << 4);
						} else {
							dataArray[idx /2] += (converted_number);
							bytecount--;
							sum += converted_number;
						}
						idx ++;
					}
					if (idx >= 8) {
						Program_LongWord_8B(address + 4 * dataIdx, dataArray);

						dataIdx++;
						idx = 0;

						if (bytecount - address_digit/2 == 1) {
							status = SREC_CHECKSUM;
							checksum = 0;
						}
					}
				}
			} else {
				status = SREC_ERROR;
				UART0_SendChar('0', 0);
			}
			break;

		case SREC_CHECKSUM:
			if (ASCII_TO_HEX(ch) != ASCII_ERROR) {
				if (idx == 0) {
					checksum = (ASCII_TO_HEX(ch) << 4);
					idx ++;
				} else {
					checksum += ASCII_TO_HEX(ch);
					if ((uint8_t)sum + checksum == 0xFF) {
						idx = 0;
						status = SREC_EOL;
					} else {
						status = SREC_ERROR;
						UART0_SendChar('s', 0);
					}
				}
			} else {
				status = SREC_ERROR;
				UART0_SendChar('1', 0);
			}
			break;

		case SREC_EOL:
			if (idx < 2 && ch == '\r') {
				idx++;
			} else if (idx == 1 && ch == '\n') {
				status = SREC_START;
			}
			break;

		case SREC_EOF:
			load_file_done = 1;
			UART0_RxEnable(0);
			break;

		default:
			break;
	}

	if (status == SREC_ERROR)
	{
		UART0_SendString(mess, strlen(mess), 0);
		if (app_address) {
			Erase_Multi_Sector(app_address, 10);
			app_address = 0;
		}
	}
}

uint8_t SREC_Load_Done(uint32_t* load_address)
{
	uint8_t ret = 0;
	if (load_file_done)
	{
		ret = 1;
		*load_address = app_address;
	}
	else if (status == SREC_ERROR)
	{
		status = SREC_START;
		*load_address = 0;
		ret = 2;
	}

	return ret;
}

SREC_Status_t SREC_Get_Status()
{
	return status;
}
