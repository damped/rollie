
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
//      accelerometer code

        int devAccel = wiringPiI2CSetup(0x53);
        int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);





	printf("Gyro Data:\n");

        for (int i = 0; i<=2; i++)
        {
                int a = i*2;
                int gyroAngles = wiringPiI2CReadReg16(devGyro,(0x1d+a));

                //printf("GYRO ANGLES\n" );
                printf("%x: %d\n", a+0x1d, gyroAngles);
        }

        printf("\nAccel device:%x\n", devAccel);
        printf("Accel device id:%x\n", dataAccel);
        
	printf("Acc Data:\n");
        for (int j = 0; j<=2; j++)
        {
                int b = j*2;
                int accAngles = wiringPiI2CReadReg16(devAccel,(0x32+b));

                //printf("ACC ANGLES\n" );
                printf("%x: %d\n", b+0x32, accAngles);
        }




        return 0;
}
