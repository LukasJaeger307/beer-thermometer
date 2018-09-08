/**\file */

/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include "easymsp/easymsp.h"

/**\page gpio Using pins as GPIO
 * Using a pin as a GPIO is a basic task when using microcontrollers.
 * But let's face it: Knowing all those register names and bitmasks
 * by heart is tedious. Using _gpio.h_ you don't have to. Just look
 * on the pin numberings of your LaunchPad. You'll see that every
 * pin is identified by a number consisting of the pin's pin bank
 * and its unique identification number within that bank. Let's take
 * the pin associated with LED2 on a G-series LaunchPad as an example.
 * Its number is 1.6, meaning it is located in bank 1 and has 6 as an ID.
 * Knowing that you can configure pins as a GPIO with the following line:
 *
 * ```c
 * gpio_configure(1, 6, C_OUT);	// Configures pin 1.6 as output
 * ```
 *
 * After successful configuration as output, you can write the pin like this:
 *
 * ```c
 * gpio_write(1, 6, HIGH);		// Sets the level of pin 1.6 to high
 * ```
 *
 * Configuring digital inputs is not that different. You can use the
 * same function for configuration and read a GPIO like this:
 *
 * ```c
 * gpio_configure(1, 6, C_IN);	// Configures pin 1.6 as input
 * uint8_t level;				// Stores the GPIO's level
 * gpio_read(1, 6, &level);		// Writes HIGH or LOW to level
 * ```
 *
 * Now let's assume you want to read a pin a button is connected to.
 * The G-series LaunchPad has an included button connected to pin 1.3.
 * You need to configure it as an input with activated pullup resistor.
 * 
 * ```c
 * gpio_configure(1, 3, C_IN_PULLUP);	// Activates the pullup resistor
 *										// while configuring 1.3 as input
 * ```
 *
 * You can now read the level with _gpio\_read_ . Keep in mind that a pullup
 * resistor inverts the logic levels.
 */

#if defined(EASYMSP_GPIO) || defined (EASYMSP_FULL)

/**
 * Macro for a high level on a GPIO
 */
#define HIGH (0xFF)

/**
 * Macro for a low level on a GPIO
 */
#define LOW (0x00)

/**
 * Contains all possible GPIO configurations
 */
typedef enum {C_IN, C_OUT, C_IN_PULLUP} Configuration;

/**
 * Configures a pin as input, input with pullup resistor activated or
 * output.
 * @param bank The bank of the pin
 * @param pin The pin
 * @param configuration The configuration of the pin
 * @return _OK_ if the configuration was successful and _ERR_ otherwise
 */
RC gpio_configure(uint8_t bank, uint8_t pin, Configuration configuration);

/**
 * Writes a logic level to a pin.
 * @param bank The bank of the pin
 * @param pin The pin
 * @param level The level of the pin
 * @return _OK_ if the writing operation was successful and _ERR_ otherwise
 */
RC gpio_write(uint8_t bank, uint8_t pin, uint8_t level);

/**
 * Reads a logic level from a pin.
 * @param bank The bank of the pin
 * @param pin The pin
 * @param data A place to write the level to
 * @return _OK_ if the reading operation was successful and _ERR_ otherwise
 */
RC gpio_read(uint8_t bank, uint8_t pin, uint8_t * const data);

#endif // EASYMSP_GPIO

#endif // _GPIO_H_
