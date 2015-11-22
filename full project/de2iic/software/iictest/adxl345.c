/*
 * adxl345.c
 *
 *  Created on: Jul 7, 2015
 *      Author: Sina Labbaf
 */

#include "adxl345.h"

signed short acc_x, acc_y, acc_z;

/*
 * to read an axis call adxl_read2(ADXL_REG_X)
 */
signed short adxl_read2(unsigned char reg){
    unsigned char DY0,DY1;
    i2c_write(0xA6,1,0);
    i2c_write(reg,0,0);
    i2c_write(0xA7,1,0);
    DY0 = i2c_read(0,0,1);
    DY1 = i2c_read(0,1,0);
    return (DY1<<8 | DY0);
}

unsigned char adxl_read(unsigned char reg){
    unsigned char DY0;
    i2c_write(0xA6,1,0);
	i2c_write(reg,0,0);
	i2c_write(0xA7,1,0);
	DY0 = i2c_read(0,1,0);
	return DY0;
}

void adxl_write(unsigned char reg, unsigned char data){
	i2c_write(0xA6,1,0);
	i2c_write(reg,0,0);
	i2c_write(data,0,1);
}

/*
 * call this function to setup ADXL345
 * scale can be changed
 */
void adxl_init(){
	adxl_write(0x2D, 0x08); //MEASURE ON scale +/- 08
}

/*
 * To read ADXL345 data you can call this function and read acc_x, acc_y and acc_z
 */
void adxl_read_data(){
	unsigned char DY0,DY1;
	i2c_write(0xA6,1,0);
	i2c_write(ADXL_REG_X,0,0);
	i2c_write(0xA7,1,0);
	DY0 = i2c_read(0,0,1);
	DY1 = i2c_read(0,0,1);
	acc_x = (DY1<<8 | DY0);
	DY0 = i2c_read(0,0,1);
	DY1 = i2c_read(0,0,1);
	acc_y = (DY1<<8 | DY0);
	DY0 = i2c_read(0,0,1);
	DY1 = i2c_read(0,1,0);
	acc_z = (DY1<<8 | DY0);
}
