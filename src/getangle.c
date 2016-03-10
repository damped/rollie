
//authors Michael and Jonas
//description, Program to return an accurate angle from the IMU.
//
//Outputs


#include <iostream>
#include <errno.h>

#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>

/*
 //function prototypes
void accelGetc0ord(void);   //grabs the  coordinates and from accelerometer
void gyroGetcoord(void);    //grabs the coordinates from gyro
void imuSetup(void);        //setup
*/

int main() {

        int ret;
        int devGyro = wiringPiI2CSetup(0x68);
        int dataGyro = wiringPiI2CReadReg8(devGyro,0x00);

        printf("Gyro device:%x\n", devGyro);
        printf("Gyro device id:%x\n\n", dataGyro);

        wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
        wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);

	printf("Gyro Data:\n");

        for (int i = 0; i<=3; i++)
        {
                int a = i*2;
                double angles = wiringPiI2CReadReg16(devGyro,(0x1d+a));
                printf("%x: %lf\n", i+0x1d, angles);
        }

//      accelerometer code
/*
        int devAccel = wiringPiI2CSetup(0x53);
        int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);

        printf("\nAccel device:%x\n", devAccel);
        printf("Accel device id:%x\n", dataAccel);
*/

        return 0;
}
