/*
 * HMC5883L.c
 *
 *  Created on: Jul 7, 2015
 *      Author: Sina Labbaf
 */

#include "HMC5883L.h"


signed short mag_x = 0;
signed short mag_y = 0;
signed short mag_z = 0;
float m_scale = 1.0;
#define PI 3.141592653

signed short make_word(unsigned char HB, unsigned char LB)
{
	signed short val = 0;

	val = HB;
	val <<= 8;
	val |= LB;
	return val;
}

/*
 * hmc5883l initializations
 */
void HMC5883L_init()
{
	HMC5883L_write(Config_Reg_A, 0x70);
	HMC5883L_write(Config_Reg_B, 0xA0);
	HMC5883L_write(Mode_Reg, 0x00);
	/*
	 * can select any valid scale
	 * 	see: HMC5883L_set_scale function
	 */
	HMC5883L_set_scale(1.3);
}


unsigned char HMC5883L_read(unsigned char reg)
{
	unsigned char val = 0;

	i2c_write(HMC5883L_WRITE_ADDR,1,0);
	i2c_write(reg,0,0);
	i2c_write(HMC5883L_READ_ADDR,1,0);
	val = i2c_read(0,1,0);
	return(val);
}


void HMC5883L_write(unsigned char reg_address, unsigned char value)
{
	i2c_write(HMC5883L_WRITE_ADDR,1,0);
	i2c_write(reg_address,0,0);
	i2c_write(value,0,1);
}

/*
 * reading compass axis data
 * refreshing mag_x, mag_y and mag_z variables
 */
void HMC5883L_read_data()
{
	unsigned char lsb = 0;
	unsigned char msb = 0;

	i2c_write(HMC5883L_WRITE_ADDR,1,0);
	i2c_write(X_MSB_Reg,0,0);
	i2c_write(HMC5883L_READ_ADDR,1,0);

	msb = i2c_read(0,0,1);
	lsb = i2c_read(0,0,1);
	mag_x = make_word(msb, lsb);

	msb = i2c_read(0,0,1);
	lsb = i2c_read(0,0,1);
	mag_z = make_word(msb, lsb);

	msb = i2c_read(0,0,1);
	lsb = i2c_read(0,1,0);
	mag_y = make_word(msb, lsb);
}


void HMC5883L_scale_axes()
{
   mag_x *= m_scale;
   mag_z *= m_scale;
   mag_y *= m_scale;
}


void HMC5883L_set_scale(float gauss)
{
	unsigned char value = 0;

	if(gauss == 0.88)
	{
	  value = 0x00;
	  m_scale = 0.73;
	}

	else if(gauss == 1.3)
	{
	  value = 0x01;
	  m_scale = 0.92;
	}

	else if(gauss == 1.9)
	{
	  value = 0x02;
	  m_scale = 1.22;
	}

	else if(gauss == 2.5)
	{
	  value = 0x03;
	  m_scale = 1.52;
	}

	else if(gauss == 4.0)
	{
	  value = 0x04;
	  m_scale = 2.27;
	}

	else if(gauss == 4.7)
	{
	  value = 0x05;
	  m_scale = 2.56;
	}

	else if(gauss == 5.6)
	{
	  value = 0x06;
	  m_scale = 3.03;
	}

	else if(gauss == 8.1)
	{
	  value = 0x07;
	  m_scale = 4.35;
	}

	value <<= 5;
	HMC5883L_write(Config_Reg_B, value);
}

/*
 * do refreshes and scales and
 * return the magnetic angle
 */
float HMC5883L_heading()
{
   float heading = 0.0;

   HMC5883L_read_data();
   HMC5883L_scale_axes();
   heading = atan2(mag_y, mag_x);
   heading += declination_angle;//declination_angle;

    if(heading < 0.0)
    {
      heading += (2.0 * PI);
    }

    if(heading > (2.0 * PI))
    {
      heading -= (2.0 * PI);
    }

   heading *= (180.0 / PI);

   return heading;
}
