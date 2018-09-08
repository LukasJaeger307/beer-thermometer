/**\file */
#ifndef _SPI_H_
#define _SPI_H_

/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */

#include "easymsp/easymsp.h"

#if defined(EASYMSP_SPI) || defined (EASYMSP_FULL)

/**
 * Sets up the USI-interface B as an SPI-interface.
 * @param cs_line_port The port of the CS-line
 * @param cs_line_pin The CS-line
 * @return _OK_ if the setup was successful and _ERR_ otherwise
 */
RC spi_setup(size_t cs_line_port, size_t cs_line_pin);

/**
 * Transmits a single char over the USI-interface B. Take care
 * of the CS-line yourself, please.
 * @param data The char to transmit
 * @return The received char
 */
uint8_t spi_transmit(uint8_t data);

#endif // EASYMSP_SPI

#endif //_SPI_H_
