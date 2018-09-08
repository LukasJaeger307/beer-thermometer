/* 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. 
 */

#include "easymsp/uart.h"

#if defined(EASYMSP_UART) || defined(EASYMSP_FULL)

#define RXD        BIT1 //Check your launchpad rev to make sure this is the case. Set jumpers to hardware uart.
#define TXD        BIT2 // TXD with respect to what your sending to the computer. Sent data will appear on this line


void uart_setup(){
	//TODO: Add frequency

	P1SEL = RXD + TXD ;               // Select TX and RX functionality for P1.1 & P1.2
	P1SEL2 = RXD + TXD ;              //
	UCA0CTL1 |= UCSSEL_2;             // Have USCI use System Master Clock: AKA core clk 1MHz
	UCA0BR0 = 104;                    // 1MHz 9600, see user manual
	UCA0BR1 = 0;                      //
	UCA0MCTL = UCBRS0;                // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;             // Start USCI state machine
}

void uart_tx(char c){
	while (UCA0STAT & UCBUSY);
	UCA0TXBUF = c;
}

void uart_tx_string(char const * const s){
	size_t i = 0;
	while(s[i] != 0x00) {
        while (UCA0STAT & UCBUSY); 
        UCA0TXBUF = s[i]; 
		i++;
    }
}

#endif // EASYMSP_UART
