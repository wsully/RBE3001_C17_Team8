/*
 * main.c
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe Lombardi
 */

#include "RBELib/RBELib.h" //RBELib

volatile uint8_t tot_overflow;
int change = 0x00;
unsigned char count;
unsigned char downcycle;
unsigned char low;

void programThatOutputsASquareWave(){

}

void programThatTestsTheButtons(){
	PINBbits._P0 = PINDbits._P0;
	PINBbits._P1 = PINDbits._P1;
	PINBbits._P2 = PINDbits._P2;
	PINBbits._P3 = PINDbits._P3;
}


void initTC0(){
	//TCCR0A = 0b00000000;

	TCNT0 = 0x00; //initialize tick counts to 0

	TCCR0B |= (1 << CS02)|(1<<CS00); //start her up with no scaling

	TIMSK0 |= (1 << TOIE0); //enable interrupt on overflow

	TIFR0 |= (1<<TOV0);

	tot_overflow = 0; //total amounts of overflows initialized to 0

	sei(); //enable global interrupts

}


ISR(TIMER0_OVF_vect)
{
	//tot_overflow++;


	if(low){
	PINBbits._P0 = 1; //Sets Port B Pin 4 to low
	}

	if(!low){
	PINBbits._P0 = 0; //Sets Port B Pin 4 to high
	TCNT0 = 0xAA;
	}


	low = !low;

//
//	if(getADC(4) < 0x0FF){
//		PINBbits._P0 = 1; //Sets Port B Pin 4 to low
//	}
//	else
//		PINBbits._P0 = 0; //Sets Port B Pin 4 to low
//

//	PINBbits._P4 = 0; //Sets Port B Pin 4 to high

}




int main(void){
//	DDRBbits._P4 = OUTPUT; //Set Port B Pin 4 to output
//	DDRBbits._P0 = OUTPUT;

	DDRBbits._P0 = OUTPUT; //Set Port B Pin 4 to output
	DDRBbits._P1 = OUTPUT;
	DDRBbits._P2 = OUTPUT; //Set Port B Pin 4 to output
	DDRBbits._P3 = OUTPUT;
	DDRBbits._P4 = OUTPUT; //Set Port B Pin 4 to output
	DDRBbits._P5 = OUTPUT;
	DDRBbits._P6 = OUTPUT; //Set Port B Pin 4 to output
	DDRBbits._P7 = OUTPUT;

	DDRDbits._P0 = INPUT; //Set Port B Pin 4 to output
	DDRDbits._P1 = INPUT;
	DDRDbits._P2 = INPUT; //Set Port B Pin 4 to output
	DDRDbits._P3 = INPUT;
	DDRDbits._P4 = INPUT; //Set Port B Pin 4 to output
	DDRDbits._P5 = INPUT;
	DDRDbits._P6 = INPUT; //Set Port B Pin 4 to output
	DDRDbits._P7 = INPUT;

//	PINBbits._P4 = 1; //Sets Port B Pin 4 to low

	initRBELib(); //Enables printf
	initTC0();
	initADC(DDRAbits._P4);
	DDRB = 0xFF;
	debugUSARTInit(DEFAULT_BAUD);


	while(1){

		if(PINDbits._P7){ //
			count = 10;
			printf("1 Hz");
		}
		else if(PINDbits._P6){ //
			count = 56;
			printf("20 Hz");
		}
		else if(PINDbits._P5){ //
			count = 100;
			printf("100 Hz");
		}

//		if(tot_overflow >= count){
//				PINBbits._P0 = 1; //Sets Port B Pin 4 to low
//				tot_overflow = 0;
//				downcycle = (getADC(4)/1024)*count;
//		}
//
//		if(tot_overflow >= downcycle){
//			PINBbits._P0 = 0; //Sets Port B Pin 4 to high
//		}


//		printf("help");

		//programThatTestsTheButtons();

//		if(PINDbits._P0 == 0){
//			putCharDebug(0x29);
//		}
//		if(PINDbits._P7 == 0){
//			putCharDebug(0x28);
//		}


//		if(PINDbits._P0 == 0){
//			PINBbits._P3 = 1;
//		}
//		else
//		{
//			PINBbits._P3 = 0;
//		}

		//putCharDebug(0x29);
	//	print("help");

	}

return 0;

}

//int readADC

///create a program to read ADC value
///create program to transmit timestamp, ADC value in counts, Pot output in millivolts, and pot angle in degrees


//write that outputs a square wave using timer interrupt Pushbuttons for  1hz, 20 hz, 100hz
//adjusts duty cycle from 0 - 100 using pot





//endimundo


/* Billy's Code */

/*

#include <RBELib/RBELib.h> //RBELib
//#include "main.h"
#include <stdlib.h>

double mv, ang;

int main(void){
	initRBELib();
	initADC(4);

	DDRB = 0xFF; //Set PortB as an output
	//DDRB |= 0x01;

	debugUSARTInit(115200);

	//putCharDebug(0x29);


	while(1)
	{
		//putCharDebug(0x40);
		//putCharDebug('0');
		//putCharDebug('\n');

		mv = (getADC(4)*5.0)/1023.0;
		ang = (getADC(4)*300.0)/1023.0;

		printf("\nADC Count: %d , ", getADC(4));
		printf("Pot Output (mV): %f , ", mv);
		printf("Pot Output (Ang): %f ", ang);

		//putCharDebug(getADC(4));
	}




	DDRBbits._P4 = OUTPUT; //Set Port B Pin 4 to output
	DDRBbits._P2 = OUTPUT; //Set Port B Pin 2 to output
	while(1){
		PINBbits._P4 = 0; //Sets Port B Pin 4 to low
		_delay_ms(1000); //Delay .1 sec
		PINBbits._P2 = 0; //Sets Port B Pin 2 to low
		_delay_ms(1000); //Delay .1 sec
		PINBbits._P4 = 1; //Sets Port B Pin 4 to high
		_delay_ms(1000); //Delay .1 sec
		PINBbits._P2 = 1; //Sets Port B Pin 2 to high
		_delay_ms(1000); //Delay .1 sec
	}
return 0;
}
*/

