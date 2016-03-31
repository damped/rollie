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
#include "stepper.h"

//#include <thread>
//#include <wiringPi.h>

//#include "getangle.c"
#include "pid.h"

#include <thread>

// function prototypes
void loop(pid_filter_t *pid, int devAccel, int devGyro);


int main()
{
    using namespace std;


    /* PID controller setup */
    pid_filter_t pid;
    pid_init(&pid);
    pid_set_gains(&pid, 1.0, 0.0001, 0.00001);

    /* IMU setup */
    int devAccel = accConfig();
    int devGyro = gyroConfig();

    /* Start Stepper Motor Thread */
    float rate = 0.0;
    
    std::thread t_stepper;
    t_stepper = std::thread(stepperControl, &rate);
    printf("Thread started\n");

    bool enable = 0;
    while (1){
      printf("Set rate to 100000\n");
      enable = true;
      rate = 100000.0;
      delay(10000);
     /* printf("Set rate to -100000\n");
      enable = true;
      rate = -100000.0;
      delay(10000); */
      printf("Set rate to  200000\n");
      enable = true;
      rate = 200000.0;
      delay(10000);
    }
    
    
    
    
    
    

    loop(&pid, devAccel, devGyro);
    

    return 0;
}


void loop(pid_filter_t *pid, int devAccel, int devGyro)
{
    float error;
    float setpoint = 0;

    while (1) {
        float current = getAngle(devAccel, devGyro);
        error = setpoint - current;
        float pidOutput = pid_process(pid, error);
        printf("\rSetPnt = %f, Current = %f, Error = %f, PIDout = %f", setpoint, current, error, pidOutput);
    }
}
