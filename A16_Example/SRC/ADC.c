/*
 * ADC.c#
 *
 *  Created on: Jan 22, 2017
 *      Author: BillySullivan
 */

#include "RBELib/RBELib.h"
//#include <avr/io.h> // AVR IO
#include <avr/iom644p.h>
#include <avr/interrupt.h>


void initADC(int channel)
{

	ADMUX = (1 << REFS0); //Enable MUX
	ADMUX = (ADMUX & 0xF8)|(channel & 0x0007); //Enable ADC
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Prescaler
}

void clearADC(int channel)
{
	ADC = 0x0000; //Clear
}

unsigned short getADC(int channel)
{
	//ADMUX = (ADMUX & 0xF8)|(channel & 0x0007);
	changeADC(channel); //Set ADC MUX channel
	clearADC(channel); //Clears ADC
	ADCSRA |= (1<<ADSC); //Tells ADC to obtain the
	while(ADCSRA & (1<<ADSC)); //Waits for ADC
	return (ADC);
}

void changeADC(int channel)
{
	ADMUX = (ADMUX & 0xF8)|(channel & 0x0007); //Enable ADC
}
