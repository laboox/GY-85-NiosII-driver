/*
 * itg3205.c
 *
 *  Created on: Jul 11, 2015
 *      Author: Sina Labbaf
 */

#include "itg3205.h"

// offsets should be calculated for each chip
short g_offx = 0;
short g_offy = 0;
short g_offz = 0;

short alpha_x, alpha_y, alpha_z, temp;

void writeTo(unsigned char address, unsigned char val) {
	i2c_write(GYRO_W,1,0);
	i2c_write(address,0,0);
	i2c_write(val,0,1);
}

void readFrom(unsigned char address, int num, unsigned char buff[]) {
	int i = 0;
	i2c_write(GYRO_W,1,0);
	i2c_write(address,0,1);

	i2c_write(GYRO_R,1,0);

	for (i=0;i<num-1;i++){
		buff[i] = i2c_read(0,0,1);
	}
	buff[5] = i2c_read(0,1,0);
}

/*
 * initialize gyro
 */
void gyro_init(){
	/*****************************************
	* ITG 3200
	* power management set to:
	* clock select = internal oscillator
	* no reset, no sleep mode
	* no standby mode
	* sample rate to = 125alpha_z
	* parameter to +/- 2000 degrees/sec
	* low pass filter = 5alpha_z
	* no interrupt
	******************************************/
	writeTo(G_PWR_MGM, 0x00);
	writeTo(G_SMPLRT_DIV, 0x07); // EB, 50, 80, 7F, DE, 23, 20, FF
	writeTo(G_DLPF_FS, 0x1E); // +/- 2000 dgrs/sec, 1Kalpha_z, 1E, 19
	writeTo(G_INT_CFG, 0x00);
}

/*
 * refreshes alpha_x, alpha_y, alpha_z and tempeture variables
 */
void gyro_read_data(){
	/**************************************
	Gyro ITG-3200 I2C
	registers:
	temp MSB = 1B, temp LSB = 1C
	x axis MSB = 1D, x axis LSB = 1E
	y axis MSB = 1F, y axis LSB = 20
	z axis MSB = 21, z axis LSB = 22
	*************************************/
	unsigned char regAddress = 0x1B;
	unsigned char buff[G_TO_READ];
	readFrom(regAddress, G_TO_READ, buff);
	alpha_x = ((buff[2] << 8) | buff[3]) + g_offx;
	alpha_y = ((buff[4] << 8) | buff[5]) + g_offy;
	alpha_z = ((buff[6] << 8) | buff[7]) + g_offz;
	temp = (buff[0] << 8) | buff[1];
}
