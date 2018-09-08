/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */

#include "easymsp/gpio.h"

#if defined(EASYMSP_GPIO) || defined(EASYMSP_FULL)

RC gpio_configure(uint8_t bank, uint8_t pin, Configuration configuration){
	// Pin bank 1 (obviously)
	if (bank == 1){
		// Checking, whether the pin exists
		if (pin > 7){
			return ERR;
		}
		else{
			uint8_t mask = (1 << pin);
		// Doing the actual configuration
		switch (configuration){
			case C_IN:
				P1DIR &= ~mask;      
				return OK;
			case C_IN_PULLUP:
				P1DIR &= ~mask;      
				P1OUT |= mask;
				P1REN |= mask;
				return OK;
			case C_OUT:
				P1DIR |= mask;      
				return OK;
			default:
				return ERR;
		}
		}
	} if (bank == 2){
		// Checking, whether the pin exists
		if (pin > 5){
			return ERR;
		}
		else{
			uint8_t mask = (1 << pin);
		// Doing the actual configuration
		switch (configuration){
			case C_IN:
				P2DIR &= ~mask;      
				return OK;
			case C_IN_PULLUP:
				P2DIR &= ~mask;      
				P2OUT |= mask;
				P2REN |= mask;
				return OK;
			case C_OUT:
				P2DIR |= mask;      
				return OK;
			default:
				return ERR;
		}
		}
	} else {
		return ERR;
	}
}

RC gpio_write(uint8_t bank, uint8_t pin, uint8_t level){
	if (bank == 1){
		if (pin > 7){
			return ERR;
		}
		else{
			uint8_t mask = (1 << pin);
			if (level != 0){
				P1OUT |= mask;
				return OK;
			}
			else{

				P1OUT &= ~mask;
				return OK;
			}
		}
	}
	else if (bank == 2){
		if (pin > 5){
			return ERR;
		}
		else{
			uint8_t mask = (1 << pin);
			if (level != 0){
				P1OUT |= mask;
				return OK;
			}
			else{
				P1OUT &= ~mask;
				return OK;
			}
		}
	}
	else{
		return 0xFF;
	}
}


RC gpio_read(uint8_t bank, uint8_t pin, uint8_t * const data){
	if (bank == 1){
		if (pin > 7) {
			 return 0xFF;
		}
		else {
			uint8_t mask = 1 << pin;
			if ((P1IN & mask) != 0){
				*data = HIGH;
			} else {
				*data = LOW;
			}
			return 0x00;
		}
	} else if (bank == 2){
		if (pin > 5){
			return 0xFF;
		}
		else {
			uint8_t mask = 1 << pin;
			if ((P2IN & mask) != 0){
				*data = HIGH;
			} else {
				*data = LOW;
			}
			return 0x00;
		}
	} else{
		return 0xFF;
	}
}

#endif // EASYMSP_GPIO
