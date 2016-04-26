
//authors Michael and Jonas
//description, Program to return an accurate angle from the IMU.
//
//Outputs


#include "imu.h"

//global constants
#define PI                          3.14159265359 // Its pi day... need at least 11 decimals
//#define ACCELEROMETER_SENSITIVITY   2047.97 //+-16 g full scale range of accelerometer
#define ACCELEROMETER_SENSITIVITY   1000 //+-16 g full scale range of accelerometer
#define GYROSCOPE_SENSITIVITY       1/14.375  //LSB/(deg/s)
#define dt                          0.01    //sampling rate 0.01 = 10ms, need to add function input for this
#define UPPER_ACC_FORCE             4095.94  // max force 2g*2047.97
#define PIDIV			    0.31831	//1/PI because multiplication is faster

// function to configure the gyroscope
int gyroConfig(){

  int devGyro = wiringPiI2CSetup(0x68);
  wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
  wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);
  wiringPiI2CWriteReg8(devGyro, 0x17, 0x01);

  return(devGyro);
}

// function to configure the accelerometer
int accConfig(){

  // setup i2c
  int devAccel = wiringPiI2CSetup(0x53);

  // configure ADXL345 registers
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_POWER_CTL, 0x08);
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_DATA_FORMAT, 0x0B);
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_INT_ENABLE, 0x80);  //
  wiringPiI2CWriteReg8(devAccel, ADXL345_REG_FIFO_CTL, 0x00);    //bypass fifo

  return(devAccel);
}

// accelerometer pitch
void accPitch(float *aPitch, int devAccel){

  int forceMagnitudeApprox;
  float Xa,Ya,Za;
  short X,Y,Z;
  int flag;

  do{

    do{
      flag = wiringPiI2CReadReg8(devAccel,(ADXL345_REG_INT_SOURCE));
      flag = flag & 0x80;
      //   printf("flag = %x\n",flag);
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

    //calc angle
    *aPitch = (atan2(Xa,sqrt(Ya*Ya+Za*Za)) * 180.0)*PIDIV; /// PI;

    //printf("pitch = %lf",*aPitch);

  } while (forceMagnitudeApprox > ACCELEROMETER_SENSITIVITY && forceMagnitudeApprox < 32768);
  
}

void gyroPitch(float *gyrPitch, int devGyro)
{
  float Yg;
  short Y;
  int flag;

  do{
    flag =wiringPiI2CReadReg8(devGyro,(INT_STATUS));
    flag= flag & 0x01;
    }while(flag != 0x01);


  Y = wiringPiI2CReadReg8(devGyro,(GYRO_YOUT_H_REG));
  Y = (Y) << 8;
  Y = Y | wiringPiI2CReadReg8(devGyro, GYRO_YOUT_L_REG);

  Yg = (float)Y;

  // Integrate the gyroscope data -> int(angularSpeed) = angle
  *gyrPitch = (Yg/* * GYROSCOPE_SENSITIVITY*/); // Angle around the X-axis
}

void getAngle(float *pitch, int devAccel, int devGyro)
{
  	float aPitch,gyrPitch;

	//timing start timer
	unsigned int time = micros();

  	accPitch(&aPitch, devAccel);      // get pitch from the accelerometer
  	gyroPitch(&gyrPitch, devGyro);   //get pitch from Gyro

  	//end timer
	time = micros() - time;

	//convert to seconds from micro
	//time = time * 0.000001;
	//printf("time: %f",time);
  	*pitch = (*pitch + (gyrPitch / GYROSCOPE_SENSITIVITY * ((float)time * 0.000001))) * 0.99 + aPitch * 0.01;

}
