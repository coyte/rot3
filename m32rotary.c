/*
Rotary encoder test 
 */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "lcd.h"
#include "rotary.h"
#include "timer.h"
#include "usart.h"

#ifndef F_CPU
//define cpu clock speed if not defined
#define F_CPU 8000000
#endif


void MainInit(void)
	{
		DDRB = 0x01; //Set as output for LED
		lcd_init(LCD_DISP_ON_CURSOR); // Initialize the LCD
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("m32rotary");

		RotaryInit(); //init rotary functions
		Timer0_Init();
		Timer0_Start();
		sei();
	}



int main(void) {
	//initialize peripherals
	MainInit();
	USART_init();   // Initialize USART
	int secs = 0; //counter for turns of rotary encoder


	//start loop
	while(1)
	{
		//update LCD information on status change
		lcd_gotoxy(0,1); //go to second line
		switch (RotaryGetStatus())
		{
		case 1:
			lcd_puts("RIGHT ");
			secs++; //increase seconds counter
			break;
		case 2:
			lcd_puts("LEFT  ");
			secs--;
			break;
		case 3:
			lcd_puts("BUTTON");
			break;
		}
		RotaryResetStatus(); //reset
		lcd_gotoxy(9,1); //go to 9th position on second line
		lcd_puts(itoa(secs,"tmpstr",10)); //output the counter
	
	}

}
