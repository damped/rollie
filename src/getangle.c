
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
#include <stdlib.h>

//global constants
#define   PI          3.1415
#define ACCELEROMETER_SENSITIVITY 8192.0
#define GYROSCOPE_SENSITIVITY 14.375
#define dt            0.01                      //sampling rate **
#define UPPER_ACC_FORCE  32768                 // max force

//prototypes
double accPitch(int);
int accConfig(void);
void ComplementaryFilter(int, int, float *, float *);
int gyroConfig(void);


int main(){

  float pitch, roll;


  int accDev = accConfig();
  int devGyro = wiringPiI2CSetup(0x68);
  wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
  wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);

  while(1){
    ComplementaryFilter(accDev,devGyro,&pitch,&roll);


  }


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

void ComplementaryFilter(int accDev, int devGyro, float *pitch, float *roll)
{

    short aX,aY,aZ;
    float X,Y,Z,aPitch;
    short gX, gY, gZ,gData[3];


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


    gX = wiringPiI2CReadReg8(devGyro,(GYRO_XOUT_H_REG));
    gX = (gX) << 8;
    gX = gX | wiringPiI2CReadReg8(devGyro, GYRO_XOUT_L_REG);
    gData[0] = gX;

    gY = wiringPiI2CReadReg8(devGyro,(GYRO_YOUT_H_REG));
    gY = (gY) << 8;
    gY = gY | wiringPiI2CReadReg8(devGyro, GYRO_YOUT_L_REG);
    gData[1] = gY;

    gZ = wiringPiI2CReadReg8(devGyro,(GYRO_ZOUT_H_REG));
    gZ = (gZ) << 8;
    gZ = gZ | wiringPiI2CReadReg8(devGyro, GYRO_ZOUT_L_REG);
    gData[2] = gZ;
  //  printf("gyro output X: %x, Y: %x, Z: %x\n",gX,gY,gZ);


    if (gX>=0x8000) {
      gX = gX^0x1111;
      gX = gX+0x0001;
      gX = gX*(-1);
    }

    if (gY>=0x8000) {
      gY = gY^0x1111;
      gY = gY+0x0001;
      gY = gY*(-1);
    }
    if (gZ>=0x8000) {
      gZ = gZ^0x1111;
      gZ = gZ+0x0001;
      gZ = gZ*(-1);
    }


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


  //   printf("hex acc X: %x, Y: %x, Z: %x\n",aX,aY,aZ);

     aPitch = (atan2(X,sqrt(Y*Y+Z*Z)) * 180.0) / PI;
     float accP = aPitch;
     //printf("%lf,%lf,%lf\n",X,Y,Z );
  //   printf("\raccel pitch = %f",aPitch);


    // Integrate the gyroscope data -> int(angularSpeed) = angle
    *pitch += ((float)gData[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
    float gpitch = *pitch;
  //  printf("Gyro Pitch: %f\n", *pitch);


    // Compensate for drift with accelerometer data if !bullshit
    // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
    int forceMagnitudeApprox = abs(X) + abs(Y) + abs(Z);

  //  printf("forceMagnitudeApprox: %d\n",forceMagnitudeApprox);

  //  if (forceMagnitudeApprox > ACCELEROMETER_SENSITIVITY && forceMagnitudeApprox < UPPER_ACC_FORCE)
  //  {
	// Turning around the X axis results in a vector on the Y-axis
      //  aPitch = atan2f((float)aY, (float)aZ) * 180 / M_PI;
        *pitch = *pitch * 0.98 + aPitch * 0.02;
      printf("\rfiltered: %f, gyro: %f, accel: %f", pitch, gpitch, accP);

  //  }
}
