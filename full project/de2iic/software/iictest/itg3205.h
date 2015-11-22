/*
 * itg3205.h
 *
 *  Created on: Jul 11, 2015
 *      Author: Sina Labbaf
 */

#ifndef ITG3205_H_
#define ITG3205_H_

#include "i2c_controller.h" // i2c_controller needed to use this code

#define GYRO_W 0xD0
#define GYRO_R 0xD1
#define G_SMPLRT_DIV 0x15
#define G_DLPF_FS 0x16
#define G_INT_CFG 0x17
#define G_PWR_MGM 0x3E
#define G_TO_READ 8

void writeTo(unsigned char address, unsigned char val);
void readFrom(unsigned char address, int num, unsigned char buff[]);

/*
 * initialize gyro
 */
void gyro_init();

/*
 * refreshes alpha_x, alpha_y, alpha_z and tempeture variables
 */
void gyro_read_data();

#endif /* ITG3205_H_ */
