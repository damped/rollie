
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

  int aX,aY,aZ;
  double X,Y,Z,pitch;

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

     if (aX>=8000) {
       aX = aX^0x1111;
       aX = aX+0x0001;
     }

     if (aY>=8000) {
       aY = aY^0x1111;
       aY = aY+0x0001;
     }
     if (aZ>=8000) {
       aZ = aZ^0x1111;
       aZ = aZ+0x0001;
     }

     X = aX * 0.0039;
     Y = aY * 0.0039;
     Z = aZ * 0.0039;


     printf("hex X: %x, Y: %x, Z: %x\n",aX,aY,aZ);

     pitch = (atan2(X,sqrt(Y*Y+Z*Z)) * 180.0) / PI;
     printf("%lf,%lf,%lf\n",X,Y,Z );
     printf("pitch = %f\n",pitch);
     printf("data ready = %x\n",wiringPiI2CReadReg8(devAccel,(ADXL345_REG_INT_SOURCE)));


  return(0);
}
