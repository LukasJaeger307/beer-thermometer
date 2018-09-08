/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */

#include "easymsp/ds18b20.h"

#if defined (EASYMSP_DS18B20) || defined(EASYMSP_FULL)

RC ds_initialize(uint8_t bank, uint8_t pin){
	if (bank == 1){
		if (pin > 7){
			return ERR;
		}
		P1DIR |= BM(pin);
		P1OUT &= ~BM(pin);
		__delay_cycles(500);
		P1OUT |= BM(pin);
		P1DIR &= ~BM(pin);
		__delay_cycles(500);
		return OK;
	} else if (bank == 2){
		if (pin > 5){
			return ERR;
		}
		P2DIR |= BM(pin);
		P2OUT &= ~BM(pin);
		__delay_cycles(500);
		P2OUT |= BM(pin);
		P2DIR &= ~BM(pin);
		__delay_cycles(500);
		return OK;
	} else {
		return ERR;
	}
}


RC ds_send_char(uint8_t bank, uint8_t pin, uint8_t data){
	if (bank == 1){
		if (pin > 7) {
			return ERR;
		}
		for (uint8_t i = 0; i < 8; i++){
			P1DIR |= BM(pin);
			P1OUT &= ~BM(pin);
			__delay_cycles(2);
			if ((data & 0x01) != 0x00){
				P1OUT |= BM(pin);	
			}
			__delay_cycles(60);
			P1OUT |= BM(pin);
			P1DIR &= ~BM(pin);			
			data >>=1;
		}
		return OK;
	} else if (bank == 2){
		if (pin > 5) {
			return ERR;
		}
		for (uint8_t i = 0; i < 8; i++){
			P2DIR |= BM(pin);
			P2OUT &= ~BM(pin);
			__delay_cycles(2);
			if ((data & 0x01) != 0x00){
				P2OUT |= BM(pin);	
			}
			__delay_cycles(60);
			P2OUT |= BM(pin);
			P2DIR &= ~BM(pin);			
			data >>=1;
		}
		return OK;
	} else {
		return ERR;
	}
}


RC ds_read(uint8_t bank, uint8_t pin, uint16_t * const data){
	uint8_t in;
	if (bank == 1){
		if (pin > 7){
			return ERR;
		}
		for(uint8_t i = 0; i < 16; i++){
			P1DIR |= BM(pin);
			P1OUT &= ~BM(pin);
			__delay_cycles(2);
			P1OUT |= BM(pin);
			P1DIR &= ~BM(pin);
			__delay_cycles(8);
			if(P1IN & BM(pin)){
				*data |= 0x8000;
			}
			*data = *data >> 1;
			__delay_cycles(120);
		}
	} else if (bank == 2){
		if (pin > 5){
			return ERR;
		}
		for(uint8_t i = 0; i < 16; i++){
			P2DIR |= BM(pin);
			P2OUT &= ~BM(pin);
			__delay_cycles(2);
			P2OUT |= BM(pin);
			P2DIR &= ~BM(pin);
			__delay_cycles(8);
			if(P2IN & BM(pin)){
				*data |= 0x8000;
			}
			*data = *data >> 1;
			__delay_cycles(120);
		}
	}
	return OK;
}


RC ds_get_temperature(uint8_t bank, uint8_t pin, float * const data){
		ds_initialize(bank, pin);
		ds_send_char(bank, pin, 0xcc);   
		ds_send_char(bank, pin, 0x44);
		__delay_cycles(100);

		ds_initialize(bank, pin);
		ds_send_char(bank, pin, 0xcc);
		ds_send_char(bank, pin, 0xbe);

		uint16_t temp; 
		ds_read(bank, pin, &temp);
		*data = ((float)temp/8.0);
		return OK;
}

#endif // EASYMSP_DS18B20
