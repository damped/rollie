
//authors Michael and Jonas
//description, Program to return an accurate angle from the IMU.
//
//Outputs


#include "imu.h"

//global constants
#define PI                          3.14159265359 // Its pi day... need at least 11 decimals
#define ACCELEROMETER_SENSITIVITY   8192.0
#define GYROSCOPE_SENSITIVITY       14.375
#define dt                          0.01    //sampling rate 0.01 = 10ms, need to add function input for this
#define UPPER_ACC_FORCE             32768  // max force





// function to configure the gyroscope
int gyroConfig(){

    int devGyro = wiringPiI2CSetup(0x68);
    wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
    wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);


  //  printf("gyro configured\n");

    return(devGyro);
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

   // printf("accelerometer configured\n");

    return(devAccel);
}

// accelerometer pitch
double accPitch(int devAccel){

    double aPitch,Xa,Ya,Za;
    short X,Y,Z;
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

    // scale the output for calculating the angle
    Xa = (double)X * 0.0039;
    Ya = (double)Y * 0.0039;
    Za = (double)Z * 0.0039;

  //  printf("hex X: %x, Y: %x, Z: %x\n",aX,aY,aZ);

    //calc angle
    aPitch = (atan(Xa/sqrt(Ya*Ya+Za*Za)) * 180.0) / PI;
   // printf("%lf,%lf,%lf\n",Xa,Ya,Za );
   // printf("pitch = %lf\n",aPitch);

    return(aPitch);
}


double gyroPitch(int devGyro)
{
  double gPitch,Xg,Yg,Zg;
  short X,Y,Z;
  int flag;


  do{
   flag = wiringPiI2CReadReg8(devGyro,(INT_STATUS));
  flag = flag & 0x01;
    }
  while(flag != 0x01);

  while(flag == 0x01){

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

  Xg = (double)X;
  Yg = (double)Y;
  Zg = (double)Z;

// printf("double conversion, Xg %lf, Yg %lf, Zg %lf", Xg, Yg, Zg);

  // Integrate the gyroscope data -> int(angularSpeed) = angle
  gPitch = (Xg / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis

  //PRINT  THE RESULT FROM THE GYROSCOPE
// printf("GYRO PITCH: %lf\n",gPitch);
  printf("\r flag, %x : X, %x : Xg : %lf : gPitch, %lf ", flag, X, Xg, gPitch);
  return(gPitch);
}
}

void getAngle(float *pitch, int devAccel, int devGyro)
{

    int aX,aY,aZ;
    float X,Y,Z,aPitch;
    int gX, gY, gZ;


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


    gX = wiringPiI2CReadReg8(devGyro,(GYRO_XOUT_H_REG));
    gX = (gX) << 8;
    gX = gX | wiringPiI2CReadReg8(devGyro, GYRO_XOUT_L_REG);

    gY = wiringPiI2CReadReg8(devGyro,(GYRO_YOUT_H_REG));
    gY = (gY) << 8;
    gY = gY | wiringPiI2CReadReg8(devGyro, GYRO_YOUT_L_REG);

    gZ = wiringPiI2CReadReg8(devGyro,(GYRO_ZOUT_H_REG));
    gZ = (gZ) << 8;
    gZ = gZ | wiringPiI2CReadReg8(devGyro, GYRO_ZOUT_L_REG);
    //printf("gyro output X: %x, Y: %x, Z: %x\n",gX,gY,gZ);


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


    //printf("hex acc X: %x, Y: %x, Z: %x\n",aX,aY,aZ);

    aPitch = (atan2(X,sqrt(Y*Y+Z*Z)) * 180.0) / PI;
    //float accP = aPitch;
    //printf("%lf,%lf,%lf\n",X,Y,Z );
    //printf("\raccel pitch = %f",aPitch);


    // Integrate the gyroscope data -> int(angularSpeed) = angle
    *pitch += ((float)gX * GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
    //float gpitch = pitch;
    //printf("Gyro Pitch: %f\n", *pitch);


    // Compensate for drift with accelerometer data if !bullshit
    // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
    int forceMagnitudeApprox = abs(X) + abs(Y) + abs(Z);

    //printf("forceMagnitudeApprox: %d\n",forceMagnitudeApprox);

    //if (forceMagnitudeApprox > ACCELEROMETER_SENSITIVITY && forceMagnitudeApprox < UPPER_ACC_FORCE)
    //{
    //Turning around the X axis results in a vector on the Y-axis
    //aPitch = atan2f((float)aY, (float)aZ) * 180 / M_PI;
    *pitch = *pitch * 0.98 + aPitch * 0.02;
    //printf("\rfiltered: %f, gyro: %f, accel: %f         ", pitch, gpitch, accP);

    //}

}
