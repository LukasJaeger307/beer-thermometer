/**\file */
#ifndef _EASYMSP_H_
#define _EASYMSP_H_

/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */

/**
 * \page easymsp The main header for easymsp
 * All source files include this header. It contains helpful macros, includes
 * for other headers that every sane person includes in source files anyway
 * and defines for the modularization system.
 */

// Some defines that include modules

/**
 * Includes the GPIO-module
 */
#define EASYMSP_GPIO

/**
 * Includes the SPI-module
 */
#define EASYMSP_SPI

/**
 * Includes the UART-module
 */
#define EASYMSP_UART

/**
 * Includes the DS18B20-module
 */
#define EASYMSP_DS18B20

/**
 * Includes all modules
 */
#define EASYMSP_FULL


#include <msp430.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * The frequency of the MSP's internal oscillator
 */
#define MHZ 1

/**
 * A return code for functions
 */
typedef uint8_t RC;

/**
 * Return if Not Null
 */
#define RNN(x){		\
	RC tmp = (x);	\
	if (tmp != 0){	\
		return tmp;	\
	}				\
}

/**
 * Bitmask macro
 */
#define BM(x) (1 << (x))

/**
 * OK return code
 */
#define OK (0x00)

/**
 * Error return code
 */
#define ERR (0xFF)

#endif //_EASYMSP_H_H
