/*
 * SREC_parse.h
 *
 *  Created on: Mar 17, 2024
 *      Author: DELL
 */

#ifndef SREC_PARSE_H_
#define SREC_PARSE_H_

#include <stdint.h>

#define ERROR	16

typedef enum
{
	SREC_START,
	SREC_HEADER,
	SREC_TYPE,
	SREC_BYTECOUNT,
	SREC_ADDRESS,
	SREC_DATA,
	SREC_CHECKSUM,
	SREC_ERROR,
	SREC_EOL,
	SREC_EOF
} SREC_Status_t;

uint8_t SREC_Load_Done(uint32_t* load_address);
void SREC_Parse(uint8_t ch);


#endif /* SREC_PARSE_H_ */
