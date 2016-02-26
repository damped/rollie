//this code was edited from the toilet

#include <iostream>
#include <errno.h>

#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>

int main() {

        int fd, data;

        fd = wiringPiI2CSetup(0x68);
        
        data = int wiringPiI2CReadReg16 (fd, 0) ;
        
        printf("fd:%d", fd);
        printf("Data:%d", data);
        return fd;
}

