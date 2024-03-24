/**
 * \file            bios.h
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-02-18
 */
/*Include guard--------------------------------------------------------------*/
#ifndef _BIOS_H_
#define _BIOS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/*INCLUDES-------------------------------------------------------------------*/
#include <stdint.h>
/*Prototypes*/

 typedef enum {
     ADD                          = 0U,
     DELETE                       = 1U,
 } App_Actiont_t;

 typedef struct
 {
 	uint32_t app_address;
 	uint8_t app_size;
 } App_Info_t;

/**
 * \brief           Handle BIOS mode for application setting 
 */
void BIOS_main(void);

#ifdef __cplusplus
}
#endif
#endif /*_BIOS_H_*/
/*EOF----------------------------------------------------------------------*/
