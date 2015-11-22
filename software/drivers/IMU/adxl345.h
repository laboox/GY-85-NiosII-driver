/*
 * adxl345.h
 *
 *  Created on: Jul 7, 2015
 *      Author: Sina Labbaf
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "i2c_controller.h" // i2c_controller needed to use this code

#define ADXL_REG_X   0x32
#define ADXL_REG_Y   0x34
#define ADXL_REG_Z   0x36

void adxl_write(unsigned char reg, unsigned char data);
unsigned char adxl_read(unsigned char reg);

/*
 * to read an axis call adxl_read2(ADXL_REG_X)
 */
signed short adxl_read2(unsigned char reg);

/*
 * call this function to setup ADXL345
 * scale can be changed
 */
void adxl_init();

/*
 * To read ADXL345 data you can call this function and read acc_x, acc_y and acc_z
 */
void adxl_read_data();

#endif /* ADXL345_H_ */
