#include <stdint.h>
#include <pic32mx.h>
#include "Snakeshooter.h"

void user_isr(){
	return;
}

int main(void){
	/*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	display_init(); //Initialize OLED display 

	score = 0;

	
	gun.x = gunX;
	gun.y = gunY;

	dart.x = dartX;
	dart.y = dartY;

	//snake.x = snakeX;
	//snake.y = snakeY;

	gun.x[0] = 4;
	gun.y[0] = 0;
	gun.x[1] = 5;
	gun.y[1] = 0;
	gun.x[2] = 6;
	gun.y[2] = 0;

	gun.length = 3;
	gun.dir = 'U';

	dart.x[0] = 7;
	dart.y[0] = 0;
	dart.x[1] = 8;
	dart.y[1] = 0;

	dart.length = 2;

	int i, j;
	SnakeRows[0] = 1;
	SnakeRows[1] = 10;
	SnakeRows[2] = 18;
	SnakeRows[3] = 24;

	for(i = 0; i < 4; i++){
		Snake s;
		s.length = 12;
		s.width = 5;
		s.x[0] = 127 - s.length;
		s.y = SnakeRows[i];

		for(j = 1; j < s.length; j++) {
			s.x[j] = s.x[0]+j;
		}
		
		snakes[i] = s;
	}

	while(1){
		display_start(); //Start display
	}

	return;
	
}