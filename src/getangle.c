
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

#include <stdint.h>


#define   PI          3.1415;


int main(){

  signed short aX,aY,aZ,pitch;

  // setup i2c
  int devAccel = wiringPiI2CSetup(0x53);
  int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);

// configure ADXL345 registers
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_POWER_CTL, 0x08);
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_DATA_FORMAT, 0x0);
  wiringPiI2CWriteReg8(devAccel,ADXL345_REG_INT_ENABLE, 0x80);




// grab raw data from accelerometer

     aX = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAX1));
     aX = (aX) << 8;
     aX = aX | wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAX0));

     aZ = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAZ1));
     aZ = (aZ) << 8;
     aZ = aZ | wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAZ0));

     aY = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAY1));
     aY = (aY) << 8;
     aY = aY | wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAY0));

     aX = aX * 0.0039;
     aY = aY * 0.0039;
     aY = aY * 0.0039;

     pitch = (atan2(aX,sqrt(aY*aY+aZ*aZ)) * 180.0) / PI;
     printf("%x,%x,%x\n",aX,aY,aZ );
     printf("pitch = %d\n",pitch);
     printf("data ready = %x\n",wiringPiI2CReadReg8(devAccel,(ADXL345_REG_INT_SOURCE)));


  return(0);
}
