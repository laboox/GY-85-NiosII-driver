# Using GY85 with NiosII processor
You can use this hardware and software codes to use GY-85 IMU sensors with NiosII processor on Altera FPGAs.
You can use IIC_Controller that provided in this project  to connect any other IIC (I2C or TWI) devices. There are three main folders in this repository full_project, hardware, and software.

## Hardware
HDL codes that are used for this projects are downloaded from Opencores website. This I2C Controller is compatible with Philips I2c bus standards. This I2C Controller is a memory mapped core that is using WISHBONE bus standards which is compatible with Avalone bus.
You can simply visit the original project website on [opencores](http://opencores.org/project,i2c).
There are two folders under hardware folder. One is the original version of the I2C Controller and one is the revised version of the controller that I removed the arbitration control feature of the bus in it. If you want to use this project in a multi-master platform you must use the original one.

## Software
In software folder drivers and examples are held.

### Drivers
In the Drivers folder you can find IIC Driver which you can use to initialize, read, or write on I2C bus with. if you didn't unsderstood how to use them just read the comments above each function.
In the IMU folder there are some drivers for using sensors on GY-85 you can easily find how to use them by reading the comments.

### Example
I also provided an example which is clearly teaches you how to use the drivers.

## Full project
in this folder there is a sample project that uses a Nios-II Processor to use GY-85 IMU. To use this project you can simply program it on a *DE2-115* FPGA board or you can use any other Altera FPGAs by changing the pin planar.

### SoC specs
For customizing some features of you Nios-II processor you can edit `nios.qsys` file using Altera Qsys or Altera SOPC builder.

### Software
you can see and change example software codes by openning projects folders under `software` folder with Nios-II Eclipse.
