//this code was edited from the toilet

#include <iostream>
#include <errno.h>

#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>

int main() {

        int dev_gyro = wiringPiI2CSetup(0x68);
        int data_gyro = wiringPiI2CReadReg8(dev_gyro,0x00);
        
        printf("Gyro device:%x\n", dev_gyro);
        printf("Gyro device id:%x\n\n", data_gyro);
        
        
        int dev_accel = wiringPiI2CSetup(0x53);
        int data_accel = wiringPiI2CReadReg8(dev_accel,0x00);
        
        printf("Accel device:%x\n", dev_accel);
        printf("Accel device id:%x\n", data_accel);
        return 0;
}

