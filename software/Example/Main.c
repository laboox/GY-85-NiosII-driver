/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <system.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include "adxl345.h"
#include "HMC5883L.h"
#include "itg3205.h"

extern signed short acc_x, acc_y, acc_z;
extern signed short alpha_x, alpha_y, alpha_z, temp;

#define LCD_WR_DATA_REG  2
#define LCD_WR_COMMAND_REG 0
#define LCD_BASE LCD_16207_0_BASE

void lcd_init( void ) {
	/* Set Function Code Four Times -- 8-bit, 2 line, 5x7 mode */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
	usleep(4100); /* Wait 4.1 ms */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
	usleep(100); /* Wait 100 us */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
	usleep(5000); /* Wait 5.0 ms */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
	usleep(100);
	/* Set Display to OFF */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x08 );
	usleep(100);
	/* Set Display to ON */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x0C );
	usleep(100);
	/* Set Entry Mode -- Cursor increment, display doesn't shift */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x06 );
	usleep(100);
	/* Set the cursor to the home position */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x02 );
	usleep(2000);
	/* Clear the display */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x01 );
	usleep(2000);
}

void lcd_clear( void ) {
	/* Set the cursor to the home position */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x02 );
	usleep(2000);
	/* Clear the display */
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x01 );
	usleep(2000);
}

void lcd_putchar ( char c ) {
	/* Write char on LCD */
	IOWR(LCD_BASE, LCD_WR_DATA_REG, c);
	usleep(2000);
}

void lcd_puts ( const char* string ) {
	int i;
	for(i=0;i<strlen(string);i++){
		lcd_putchar(string[i]);
	}
}

int main()
{
	float head = 0;

	lcd_init();
	i2c_init();
	HMC5883L_init();
	gyro_init();
	adxl_init();

	while(1){
		adxl_read_data();
		head = HMC5883L_heading();
		gyro_read_data();
		printf("acc_x: %d, acc_y: %d, acc_z: %d\n", acc_x, acc_y, acc_z);
		printf("compass heading: %d\n", (int)head);
		printf("alpha_x: %d, alpha_y: %d, alpha_z: %d\n\n", alpha_x, alpha_y, alpha_z);

		usleep(10000);
	}
	return 0;
}