/*
 * config.h
 *
 *  Created on: Mar 19, 2024
 *      Author: Admin
 */

#ifndef CONFIG_H_
#define CONFIG_H_


/* Config here*****************************************************************************/
/* Board config*/
#define INIT_LED1
#define INIT_LED2
#define INIT_SW1
//#define INIT_SW2
//#define ENABLE_IRQ_SW

////////////////////////////////////////////////////////////////////////////////////////////
/* Timer config*/
#define INIT_TIMER
#define ENABLE_IRQ_TIMER

/******************************************************************************************/

// No config
#ifdef INIT_LED1
	#ifndef ENABLE_PORTD
	#define ENABLE_PORTD
	#endif
#endif

#ifdef INIT_LED2
	#ifndef ENABLE_PORTE
	#define ENABLE_PORTE
	#endif
#endif

#if (defined(INIT_SW1) || defined(INIT_SW2))
	#ifndef ENABLE_PORTC
	#define ENABLE_PORTC
	#endif
#endif

#ifdef INIT_TIMER
	#ifndef ENABLE_PIT
	#define ENABLE_PIT
	#endif
#endif

#ifdef ENABLE_IRQ_SW
	#ifndef ENABLE_IRQ_PORTC_PORTD
	#define ENABLE_IRQ_PORTC_PORTD
	#endif
#endif

#ifdef ENABLE_IRQ_TIMER
	#ifndef ENABLE_IRQ_PIT
	#define ENABLE_IRQ_PIT
	#endif
#endif

#endif /* CONFIG_H_ */
