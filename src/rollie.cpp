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
#include "imu.h"
#include "pid.h"
#include "stepper.h"

#include <stdio.h>
#include <wiringPi.h>
#include <thread>


// function prototypes
void loop(pid_filter_t *pid, int devAccel, int devGyro, float *period);


int main()
{
    /* PID controller setup */
    pid_filter_t pid;
    pid_init(&pid);
    pid_set_gains(&pid, 1.0, 0.0001, 0.00001);

    /* IMU setup */
    int devAccel = accConfig();
    int devGyro = gyroConfig();

    /* Start Stepper Motor Thread */
    float period;
    setSpeed(0.0, &period);

    std::thread t_stepper;
    t_stepper = std::thread(stepperControl, &period);

    //bool enable = 1;
    /* Motor tester eh
    while (1){
      printf("Set velocity to 0.01 m/s\n");
      setSpeed(0.01, &period);
      delay(10000);
      printf("Set velocity to 0.02 m/s\n");
      setSpeed(0.02, &period);
      delay(10000);
      printf("Set velocity to 0.03 m/s\n");
      setSpeed(0.03, &period);
      delay(10000);
      printf("Set velocity to 0.04 m/s\n");
      setSpeed(0.04, &period);
      delay(10000);
      printf("Set velocity to 0.05 m/s\n");
      setSpeed(0.05, &period);
      delay(10000);
    }
  */


    loop(&pid, devAccel, devGyro, &period);


    return 0;
}


void loop(pid_filter_t *pid, int devAccel, int devGyro, float *period)
{
    float error, pitch;
    float setpoint = 0.0;
    float pidOutput;

    while (1){

        getAngle(&pitch,devAccel,devGyro);

        error = setpoint - pitch;
        pidOutput = pid_process(pid, error);

        setSpeed(pidOutput, period);

        printf("\r error = %f, PID = %f", error, pidOutput);

    }
}
