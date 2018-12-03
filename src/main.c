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

#define LED_LOW			(BIT4)
#define LED_OK_LOW	(BIT3)
#define LED_OK			(BIT2)
#define LED_OK_HIGH	(BIT1)
#define LED_HIGH		(BIT0)

static void set_leds(float temperature){
	uint8_t mask = 0x00;
	// Temperature too low
	if (temperature < 18.0) {
		mask = LED_LOW;
	}
	else if (temperature < 18.5) {
		mask = LED_OK_LOW;
	}
	else if (temperature < 19.5) {
		mask = LED_OK;
	}
	else if (temperature < 20.0) {
		mask = LED_OK_HIGH;
	}
	else {
		mask = LED_HIGH;
	}
	P2OUT = mask;
}

static void go_to_12khz(){
	DCOCTL = 0;
	BCSCTL1 = 0;
	BCSCTL2 = SELM_3 | SELS;
	BCSCTL3 = LFXT1S_2;
}

static void go_to_1mhz(){
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 = 0;
	BCSCTL3 = 0;
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;         

	P1DIR &= ~BIT3;
	P1OUT |= BIT3;
	P1IE |= BIT3;

	__bis_SR_register(GIE);

	P2DIR = LED_LOW | LED_OK_LOW | LED_OK | LED_OK_HIGH | LED_HIGH;
	P2OUT = 0;

	uart_setup();

	go_to_12khz();
	
	while (1);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	go_to_1mhz();
	float temperature = 0.0;
	ds_get_temperature(1,4, &temperature);
		
	char string [6];
	sprintf(string, "%u.%02u", (int) temperature, (int) ((temperature - (float)((int)(temperature))) * 100));
	uart_tx_string("Temperature: ");
	uart_tx_string(string);
	uart_tx_string("\r\n");
	set_leds(temperature);
	__delay_cycles(1000000);
	P2OUT = 0x00;
	go_to_12khz();
	P1IFG &= ~BIT3;
}

