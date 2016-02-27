//this code was edited from the toilet

#include <iostream>
#include <errno.h>

#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>

int main() {

        int ret;
        int devGyro = wiringPiI2CSetup(0x68);
        int dataGyro = wiringPiI2CReadReg8(devGyro,0x00);
        
        printf("Gyro device:%x\n", devGyro);
        printf("Gyro device id:%x\n\n", dataGyro);
        
        wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
        wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);
        
        for (int i = 0; i>=5; i++)
        {
                printf("%x\n", wiringPiI2CReadReg8(devGyro,(0x1d+i)));
                printf("I: %d",i);
        }
        
        int devAccel = wiringPiI2CSetup(0x53);
        int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);
        
        printf("Accel device:%x\n", devAccel);
        printf("Accel device id:%x\n", dataAccel);
        return 0;
}

