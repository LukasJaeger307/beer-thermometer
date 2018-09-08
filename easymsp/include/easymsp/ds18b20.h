/**\file */

/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */

#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "easymsp/easymsp.h"

/**
 * \page ds18b20 Interfacing a DS18B20-thermometer with MSP430
 * Maxim's DS18B20-thermometers are to be accessed with Maxim's own
 * OneWire-protocol. Unlike SPI or I2C it is not supported natively
 * by an MSP430 so the protocol is emulated. I don't wanna bore you
 * with details on the protocol and if you want to use your DS18B20
 * you just need to connect your thermometer with your LaunchPad and
 * call a single function to get the temperature in degrees celsius.
 * If you want any other unit, convert it yourself or even better
 * get used to the metric system.
 * Connect the _VDD_-line of the DS18B20 with the _VDD_-line of your
 * LaunchPad. Do the same with the _GND_ line and connect the data wire
 * with a free digital pin of your LaunchPad. Insert a resistor of
 * about 5 Kiloohms between _VDD_ and the data line. Now add the 
 * temperature measuring code to your software. Make sure, your MSP
 * runs with a clock frequency of 1MHz. Otherwise you need to change
 * the parameters of all _delay_cycle_-functions. Let's assume you chose
 * pin 1.4 for your data wire. Measure the temperature with
 * 
 * ```c
 * float temperature;
 * ds_get_temperature(1, 4, &temperature);
 * ```
 *
 * Printing it is a little difficult since there is no _itoa_ on an
 * MSP430. I did it that way:
 *
 * ```c
 * char string [6];
 * sprintf(string, "%u.%02u", (int) temperature, (int) ((temperature - (float)((int)(temperature))) * 100));
 * uart_tx_string("Temperature: ");
 * uart_tx_string(string);
 * uart_tx_string("\r\n");
 * ```
 * 
 * which is admittedly not elegant but works fine.
 */
  
#if defined(EASYMSP_DS18B20) || defined (EASYMSP_FULL)

/**
 * Resets the DS18B20-thermometer.
 * @param bank The bank of pins the thermometer is connected to
 * @param pin The pin the thermometer is connected to
 * @return _OK_ if the initialization was successful and _ERR_ otherwise
 */
RC ds_initialize(uint8_t bank, uint8_t pin);

/**
 * Sends a single char to the DS18B20-thermometer.
 * @param bank The bank of pins the thermometer is connected to
 * @param pin The pin the thermometer is connected to
 * @param data The char to send to the thermometer
 * @return _OK_ if the transmission was successful and _ERR_ otherwise
 */
RC ds_send_char(uint8_t bank, uint8_t pin, uint8_t data);

/**
 * Reads the temperature value from the DS18B20-thermometer.
 * This value is not yet scaled and converted to degrees celsius.
 * @param bank The bank of pins the thermometer is connected to
 * @param pin The pin the thermometer is connected to
 * @param data A place to write the temperature to
 * @return _OK_ if the reading operation was successful and _ERR_ otherwise
 */
RC ds_read(uint8_t bank, uint8_t pin, uint16_t * const data);

/**
 * Retrieves the temperature in degrees celsius from the thermometer.
 * @param bank The bank of pins the thermometer is connected to
 * @param pin The pin the thermometer is connected to
 * @param temperature The temperature measured by the thermometer
 * @return _OK_ if the reading operation was successful and _ERR_ otherwise
 */
RC ds_get_temperature(uint8_t bank, uint8_t pin, float * const temperature);

#endif //EASYMSP_DS18B20

#endif // _DS18B20_H_
