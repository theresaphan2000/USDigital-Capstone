/*
 * USDigital.c
 *
 * Created: 12/27/2021 17:53:09
 * Author : Thiccresa
 */ 
#ifndef F_CPU 
#define F_CPU 1000000UL		//if CPU is not define, set it to 1MHZ for now 
#endif 

#include <avr/io.h>		//always include this in the program
#include <util/delay.h>		//for the delay function
#include "lcd/lcd.h"	//LCD library 
////////////////////////////////////////////////////////////////////////////
/*
Notes: 
DDRX: sets the ports as inputs or outputs 
PORTX: Sets as high or low output 
*/

//under PORTB mapped to pin PDX
#define RS	6 //resistor 
#define RW	5 //read write, low for write high for read
#define E   4 //enable pin
//4 bit? 
//mapped under PORTD which is for data
#define DB7 3
#define DB6 2
#define DB5 1
#define DB4	0
void LCD_CHECK_BUSY(void); 
void LCD_SEND_COMMAND(unsigned char command); 
void LCD_SEND_CHAR(unsigned char character); 

int main(void){
	DDRB |= 1<<E | 1<<RW | 1<<RS; 
	_delay_ms(15); 
	LCD_SEND_COMMAND(0x01); //clear screen 
	LCD_SEND_CHAR(0x41); //sending character A 
	
	while(1){
		
		
	}
	
}
void LCD_CHECK_BUSY(void){
	
}

void LCD_SEND_COMMAND(unsigned char command){
	PORTD = command; 
	PORTB &= ( 0 << RW | 0 << RS); //set RW as low for write command or RS to zero 
}
void LCD_SEND_CHAR(unsigned char character){
	
}
