//this code was edited from the toilet

#include <iostream>
#include <errno.h>

#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>

int main() {

        int dev_gyro = wiringPiI2CSetup(0x68);
        int data_accel = wiringPiI2CReadReg8(fd,0x00);
        
        printf("Gyro device:%x\n", dev_gyro);
        printf("Gyro device id:%x\n", data_accel);
        
        
        int dev_accel = wiringPiI2CSetup(0x53);
        int data_accel = wiringPiI2CReadReg8(fd,0x00);
        
        printf("Accel device:%x", dev_gyro);
        printf("Accel device id:%x", data_accel);
        return fd;
}

