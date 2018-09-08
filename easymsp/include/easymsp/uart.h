/**\file */
#ifndef _UART_H_
#define _UART_H_

/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */


/**
  * \page uart The UART-header
  * A header that provides some helpful functions to setup the UART-interface
  * on your MSP430. Set your UART-jumpers to hardware UART before usage. You can
  * setup the interface with 9600 baud using \ref uart_setup. After you have done
  * that you can transmit single chars using \ref uart_tx and whole strings
  * (null-terminated please) with \ref uart_tx_string. It's as easy as this:
  * ```c
  * uart_setup();
  * uart_tx_string("Hello world\r\n");
  * ```
  */

#include "easymsp/easymsp.h"

#if defined(EASYMSP_UART) || defined(EASYMSP_FULL)

/**
  * Sets up the UART interface with 9600 bauds. Other freqencies may be included
  * in future releases. You may need adjust the implementation to fit to your
  * MCU and LaunchPad.
  */
void uart_setup();

/**
  * Transmits a single char over the UART interface.
  * @param c The char to transmit
  */
void uart_tx(char c);

/**
  * Transmits a string over the UART interface. Make sure it ends with 0x00
  * or this function will transmit forever.
  * @param s The string to transmit
  */
void uart_tx_string(char const * const s);

#endif // EASYMSP_UART

#endif //_UART_H_
