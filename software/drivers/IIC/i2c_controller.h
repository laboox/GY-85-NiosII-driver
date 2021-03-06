/*
 * i2c_controller.h
 *
 *  Created on: Jul 7, 2015
 *      Author: Sina Labbaf
 */

#ifndef I2C_CONTROLLER_H_
#define I2C_CONTROLLER_H_

#include "oc_i2c_master.h" //Opencores' header function needed to use this functions
#include "io.h" //NIOS2 IO header need to use this header


// IMPORTANT: set this value to your I2C memory map instruction base address
#define IIC_BASE 0x21010

/*
 * initialize of Opencores' I2C controller
 * Pre-scale value can change bye the following formula:
 * 	value = ((base frequency)/(5 * I2C speed)) + 1
 */
void i2c_init();

/*
 * I2C write function
 */
void i2c_write(unsigned char data, unsigned char start, unsigned char stop);

/*
 * By this function write ACK from slave can be check
 */
char i2c_check_rxAck();

/*
 * I2C read function
 */
unsigned char i2c_read(unsigned char start, unsigned char stop, unsigned char ack);


#endif /* I2C_CONTROLLER_H_ */
