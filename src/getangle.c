
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

double accPitch(int);
int accConfig(void);

int main(){

  int acc = accConfig();
  
  double pitch = accPitch(acc);

  return(0);
}

int accConfig(){

      // setup i2c
      int devAccel = wiringPiI2CSetup(0x53);
      int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);

    // configure ADXL345 registers
      wiringPiI2CWriteReg8(devAccel, ADXL345_REG_POWER_CTL, 0x08);
      wiringPiI2CWriteReg8(devAccel, ADXL345_REG_DATA_FORMAT, 0x0B);
      wiringPiI2CWriteReg8(devAccel,ADXL345_REG_INT_ENABLE, 0x80);

      return(devAccel);
}
double accPitch(int accDev){

      short aX,aY,aZ;
      double X,Y,Z,aPitch;

  // grab raw data from accelerometer

       aX = wiringPiI2CReadReg8(accDev,(ADXL345_REG_DATAX1));
       aX = (aX) << 8;
       aX = aX | wiringPiI2CReadReg8(accDev,(ADXL345_REG_DATAX0));

       aZ = wiringPiI2CReadReg8(accDev,(ADXL345_REG_DATAZ1));
       aZ = (aZ) << 8;
       aZ = aZ | wiringPiI2CReadReg8(accDev,(ADXL345_REG_DATAZ0));

       aY = wiringPiI2CReadReg8(accDev,(ADXL345_REG_DATAY1));
       aY = (aY) << 8;
       aY = aY | wiringPiI2CReadReg8(accDev,(ADXL345_REG_DATAY0));

       // convert from twos compliment
       if (aX>=0x8000) {
         aX = aX^0x1111;
         aX = aX+0x0001;
         aX = aX*(-1);
       }

       if (aY>=0x8000) {
         aY = aY^0x1111;
         aY = aY+0x0001;
         aY = aY*(-1);
       }
       if (aZ>=0x8000) {
         aZ = aZ^0x1111;
         aZ = aZ+0x0001;
         aZ = aZ*(-1);
       }

       X = aX * 0.0039;
       Y = aY * 0.0039;
       Z = aZ * 0.0039;


       printf("hex X: %x, Y: %x, Z: %x\n",aX,aY,aZ);

       aPitch = (atan(X/sqrt(Y*Y+Z*Z)) * 180.0) / PI;
       printf("%lf,%lf,%lf\n",X,Y,Z );
       printf("pitch = %f\n",aPitch);

       return(aPitch);

}
