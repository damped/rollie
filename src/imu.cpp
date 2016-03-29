
//authors Michael and Jonas
//description, Program to return an accurate angle from the IMU.
//
//Outputs


#include "imu.h"

//global constants
#define PI                          3.14159265359 // Its pi day... need at least 11 decimals
#define ACCELEROMETER_SENSITIVITY   2047.97 //+-16 g full scale range of accelerometer
#define GYROSCOPE_SENSITIVITY       14.375  //LSB/(deg/s)
#define dt                          0.01    //sampling rate 0.01 = 10ms, need to add function input for this
#define UPPER_ACC_FORCE             4095.94  // max force 2g*2047.97


// function to configure the gyroscope
int gyroConfig(){

    int devGyro = wiringPiI2CSetup(0x68);
    wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
    wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);
    wiringPiI2CWriteReg8(devGyro, 0x17, 0x01);



  //  printf("gyro configured\n");

    return(devGyro);
}

// function to configure the accelerometer
int accConfig(){

    // setup i2c
    int devAccel = wiringPiI2CSetup(0x53);
  //  int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);

    // configure ADXL345 registers
    wiringPiI2CWriteReg8(devAccel, ADXL345_REG_POWER_CTL, 0x08);
    wiringPiI2CWriteReg8(devAccel, ADXL345_REG_DATA_FORMAT, 0x0B);
    wiringPiI2CWriteReg8(devAccel, ADXL345_REG_INT_ENABLE, 0x80);  //
    wiringPiI2CWriteReg8(devAccel, ADXL345_REG_FIFO_CTL, 0x00);    //bypass fifo
   // printf("accelerometer configured\n");

    return(devAccel);
}

// accelerometer pitch
void accPitch(float *aPitch, int devAccel){

    int forceMagnitudeApprox;
    float Xa,Ya,Za;
    short X,Y,Z;
    int flag;

    do{
         flag = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_INT_SOURCE));
         flag = flag & 0x80;
         printf("flag = %x\n",flag);

      }while(flag != 0x80);

      // grab raw data from accelerometer
    X = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAX1));
    X = (X) << 8;
    X = X | wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAX0));

    Z = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAZ1));
    Z = (Z) << 8;
    Z = Z | wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAZ0));

    Y = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAY1));
    Y = (Y) << 8;
    Y = Y | wiringPiI2CReadReg8(devAccel,(ADXL345_REG_DATAY0));


    forceMagnitudeApprox = abs(X)+abs(Y)+abs(Z);

    // scale the output for calculating the angle
    Xa = (float)X * 0.0039;
    Ya = (float)Y * 0.0039;
    Za = (float)Z * 0.0039;

  //  printf("hex X: %x, Y: %x, Z: %x\n",aX,aY,aZ);
    //calc angle
    *aPitch = (atan2(Xa,sqrt(Ya*Ya+Za*Za)) * 180.0) / PI;
   // printf("%lf,%lf,%lf\n",Xa,Ya,Za );
    printf("pitch = %lf\n",*aPitch);

}


void gyroPitch(float *gyroPitch, int devGyro)
{
  float Xg,Yg,Zg;
  short X,Y,Z;
  int flag;


  do{
       flag = wiringPiI2CReadReg8(devGyro,(INT_STATUS));
       flag = flag & 0x01;

    }while(flag != 0x01);

        // read from the gyro and grab the accelerational data for each axis
        X = wiringPiI2CReadReg8(devGyro,(GYRO_XOUT_H_REG));
        X = (X) << 8;
        X = X | wiringPiI2CReadReg8(devGyro, GYRO_XOUT_L_REG);

        Y = wiringPiI2CReadReg8(devGyro,(GYRO_YOUT_H_REG));
        Y = (Y) << 8;
        Y = Y | wiringPiI2CReadReg8(devGyro, GYRO_YOUT_L_REG);

        Z = wiringPiI2CReadReg8(devGyro,(GYRO_ZOUT_H_REG));
        Z = (Z) << 8;
        Z = Z | wiringPiI2CReadReg8(devGyro, GYRO_ZOUT_L_REG);

      // printf("hex output: X, %x, Y, %x, Z %x", X, Y, Z);

        Xg = (float)X;
        Yg = (float)Y;
        Zg = (float)Z;

      // printf("double conversion, Xg %lf, Yg %lf, Zg %lf", Xg, Yg, Zg);

        // Integrate the gyroscope data -> int(angularSpeed) = angle
        *gyroPitch = (Xg / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
        //PRINT THE RESULT FROM THE GYROSCOPE
      //  printf("\r flag, %x : X, %x : Xg : %lf : gPitch, %lf ", flag, X, Xg, *gPitch);
}

void getAngle(float *pitch, int devAccel, int devGyro)
{
    float aPitch,gyroPitch;

    accPitch(&aPitch, devAccel);      // get pitch from the accelerometer
    gyroPitch(&gyroPitch, devGyro);   //get pitch from Gyro

    printf("gyroPitch = %f, accPitch = %f\n",gyroPitch,aPitch);

    *pitch = gyroPitch * 0.98 + aPitch * 0.02;

}
