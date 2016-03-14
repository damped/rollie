
//authors Michael and Jonas
//description, Program to return an accurate angle from the IMU.
//
//Outputs


#include <iostream>
#include <errno.h>
#include <wiringPi.h>
#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>
#include "ADXL345.h"



int main(){

  int aX,aY,aZ;

// setup i2c
  int devAccel = wiringPiI2CSetup(0x53);
  int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);

// configure ADXL345 registers
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_POWER_CTL, 0x08);
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_DATA_FORMAT, 0x0B);

// grab raw data from accelerometer

   while (1)
   {
     aX = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAX0));
     printf("%x\n", aX);
     aX = (aX) << 8;
     printf("%x\n", aX);
     aX = aX | wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAX1));
     printf("%x\n", aX);
   }
  return(0);
}
