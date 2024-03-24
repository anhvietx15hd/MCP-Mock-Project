/*
 * SREC_parse.h
 *
 *  Created on: Mar 17, 2024
 *      Author: DELL
 */

#ifndef SREC_PARSE_H_
#define SREC_PARSE_H_

#include <stdint.h>

#define ASCII_ERROR	(16U)

typedef enum
{
	SREC_START,
	SREC_HEADER,
	SREC_TYPE,
	SREC_BYTECOUNT,
	SREC_ADDRESS,
	SREC_DATA,
	SREC_CHECKSUM,
	SREC_EOL,
	SREC_EOF, 
	SREC_ERROR,
	SREC_APP_CONFLIC,
	SREC_BOOT_CONFLIC
} SREC_Status_t;

 typedef struct
 {
 	uint32_t app_address;
 	uint8_t app_size;
 } App_Info_t;

uint8_t SREC_Load_Done(App_Info_t* app_info);
void SREC_Parse(uint8_t ch);


#endif /* SREC_PARSE_H_ */
