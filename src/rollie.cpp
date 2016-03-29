/*************************************************************
*
*  rollie.cpp - Self balencing robot project
*
*  Authours: Jonas Menge and Michael Jones
*
*  Usage:
*
*
*************************************************************/

#include <stdio.h>
#include "imu.h"

//#include <thread>
//#include <wiringPi.h>

//#include "getangle.c"
#include "pid.h"


// function prototypes
void loop(pid_filter_t *pid, int devAccel, int devGyro);


int main()
{
    using namespace std;


    /* PID controller setup */
    pid_filter_t pid;
    pid_init(&pid);
    pid_set_gains(&pid, 10.0, 0.1, 4.0);

    /* IMU setup */
    int devAccel = accConfig();
    int devGyro = gyroConfig();



    loop(&pid, devAccel, devGyro);

    return 0;
}


void loop(pid_filter_t *pid, int devAccel, int devGyro)
{
    float  error, pitch;
    float  setpoint = 0.0;
    float  gP,aP;

    while (1) {

        gyroPitch(&gP,devGyro);
        accPitch(&aP,devAccel);

        //take average of two outputs for pitch
        pitch = 0.98*gP +(0.02)*aP;
	pitch = gP;

       // getAngle(&pitch, devAccel, devGyro);
        error = setpoint - pitch;
        float pidOutput = pid_process(pid, error);
        printf("\r Current = %f, gPitch = %f, aPitch = %f", pitch, gP, aP);
    }
}
