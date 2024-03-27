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
	SREC_START = 0,
	SREC_HEADER = 1,
	SREC_TYPE = 2,
	SREC_BYTECOUNT = 3,
	SREC_ADDRESS = 4,
	SREC_DATA = 5,
	SREC_CHECKSUM = 6,
	SREC_EOL = 7,
	SREC_EOF = 8, 
	SREC_ERROR = 9,
} SREC_Status_t;

 typedef struct
 {
 	uint32_t app_address;
 	uint8_t app_size;
 } App_Info_t;

uint8_t SREC_Load_Done(App_Info_t* app_info);
void SREC_Parse(uint8_t ch);


#endif /* SREC_PARSE_H_ */
