#include "easymsp/spi.h"

#if defined(EASYMSP_SPI) || defined(EASYMSP_FULL)

RC spi_setup(size_t cs_line_port, size_t cs_line_pin){
	switch (cs_line_port){
		case 1:
			if (cs_line_pin > 4){
				return ERR;
			}
			P1DIR |= BM(cs_line_pin);
			P1OUT |= BM(cs_line_pin);
			break;
		case 2:
			if (cs_line_pin > 5){
				return ERR;
			}
			P2DIR |= BM(cs_line_pin);
			P2OUT |= BM(cs_line_pin);
			break;
		default:
			return ERR;
	}
	// Configuring pins for USI B
	P1SEL  |= BIT5 | BIT6 | BIT7;
	P1SEL2 |= BIT5 | BIT6 | BIT7;

	// Configuring USI B
	UCB0CTL1 = UCSWRST;
	UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;
	UCB0CTL1 |= UCSSEL_2;	
	UCB0BR0 = 0x02;
	UCB0BR1 = 0;
	UCA0MCTL = 0;
	UCA0CTL1 &= ~UCSWRST;

	return OK;
}

uint8_t spi_transmit(uint8_t data){
	while(!(IFG2 & UCB0TXIFG));
	UCB0TXBUF = data;
	while(!(IFG2 & UCB0RXIFG));
	return UCB0RXBUF;
}

#endif // EASYMSP_SPI
