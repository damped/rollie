
//authors Michael and Jonas
//description, Program to return an accurate angle from the IMU.
//
//Outputs

// libraries and header files
#include <iostream>
#include <errno.h>
#include <wiringPi.h>
#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>
#include "6dofIMU.h"
#include <stdint.h>

//global constants
#define   PI          3.1415;

//prototypes
double accPitch(int);
int accConfig(void);

int gyroConfig(void);


int main(){

  int acc = accConfig();
  double pitch = accPitch(acc);

  short gX, gY, gZ;

  int devGyro = wiringPiI2CSetup(0x68);
  int dataGyro = wiringPiI2CReadReg8(devGyro,0x00);

  wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
  wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);

  gX = wiringPiI2CReadReg8(devGyro,(GYRO_XOUT_H_REG));
  gX = (gX) << 8;
  gX = gX | wiringPiI2CReadReg8(devGyro, GYRO_XOUT_L_REG);

  gY = wiringPiI2CReadReg8(devGyro,(GYRO_YOUT_H_REG));
  gY = (gY) << 8;
  gY = gY | wiringPiI2CReadReg8(devGyro, GYRO_YOUT_L_REG);

  gZ = wiringPiI2CReadReg8(devGyro,(GYRO_ZOUT_H_REG));
  gZ = (gZ) << 8;
  gZ = gZ | wiringPiI2CReadReg8(devGyro, GYRO_ZOUT_L_REG);

  printf("gyro output X: %x, Y: %x, Z: %x",gX,gY,gZ);

  return(0);
}



// function to configure the accelerometer
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

//
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
