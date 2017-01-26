/*
 * USART.c
 *
 *  Created on: Jan 26, 2015
 *      Author: joest
 */

#include "RBELib/USARTDebug.h"
#include "RBELib/RBELib.h"
#include <avr/iom644p.h>
#include <avr/io.h>
//#include <avr/io.h>

void debugUSARTInit(unsigned long baudrate)
{
	int UBRR1base = (CLK/(16*baudrate) - 1); //Calculate baudrate and set registers
	UBRR1H = (UBRR1base >> 8);
	UBRR1L = UBRR1base;

	UCSR1B |= (1<<TXEN1)|(1<<RXEN1); // Enable USART1 transmit and receive
	UCSR1C |= (1<<UCSZ10)|(1<<UCSZ11); //Set 8bit data format
}


void putCharDebug(char byteToSend) // See pages datasheet 21.6.
{
	 /* Wait for empty transmit buffer */
	while(!(UCSR1A & (1<<UDRE1)));
	/* Put data into buffer, sends the data */
	UDR1 = byteToSend;
}

unsigned char getCharDebug(void)
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)));
	/* Get and return received data from buffer */
	return UDR1;
}
