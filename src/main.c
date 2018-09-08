/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */


#include "easymsp/easymsp.h"
#include "easymsp/uart.h"
#include "easymsp/gpio.h"
#include "easymsp/ds18b20.h"
#include <stdio.h>

#define BUTTON BIT3

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;         
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	gpio_configure(1,3, C_IN_PULLUP);
	gpio_configure(1,6, C_OUT);

	uart_setup();
	while(1)               
	{
		uint8_t level = LOW;
		float temperature;
		ds_get_temperature(1,4, &temperature);
		
		char string [6];
		sprintf(string, "%u.%02u", (int) temperature, (int) ((temperature - (float)((int)(temperature))) * 100));
		uart_tx_string("BUTTS\r\n");
		uart_tx_string("Temperature: ");
		uart_tx_string(string);
		uart_tx_string("\r\n");
		__delay_cycles(1000000);
	}
}

