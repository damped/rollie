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
#include <wiringPi.h>

//#include "getangle.c"
#include "pid.h"

#include <thread>

// function prototypes
void loop(pid_filter_t *pid, int devAccel, int devGyro);


int main()
{
<<<<<<< HEAD
    using namespace std;
	wiringPiSetupGpio();
=======
    //using namespace std;

>>>>>>> steppercontroll

    /* PID controller setup */
    pid_filter_t pid;
    pid_init(&pid);
    pid_set_gains(&pid, 1.0, 0.0001, 0.00001);

    /* IMU setup */
    int devAccel = accConfig();
    int devGyro = gyroConfig();

<<<<<<< HEAD
    pinMode (17, OUTPUT);
=======
    /* Start Stepper Motor Thread */
    float period = 0.0;

    std::thread t_stepper;
    t_stepper = std::thread(stepperControl, &period);
    printf("Thread started\n");

    bool enable = 1;
    while (1){
      printf("Set velocity to 0.01 m/s\n");
      setSpeed(1, &period);
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






>>>>>>> steppercontroll

    loop(&pid, devAccel, devGyro);


    return 0;
}


void loop(pid_filter_t *pid, int devAccel, int devGyro)
{
<<<<<<< HEAD
    float error;
    float setpoint = 0;
	

	while(1){
    //for (int i = 0; i < 1000; i++) {
        //float current = 99;//getAngle(devAccel, devGyro);
        //error = setpoint - current;
        //float pidOutput = pid_process(pid, error);
        //printf("\rSetPnt = %f, Current = %f, Error = %f, PIDout = %f", setpoint, current, error, pidOutput);
	digitalWrite (17, LOW);
	//delay(5);
	digitalWrite (17, HIGH);
	//delay(5);
=======
    float  error, pitch;
    float  setpoint = 0.0;

    while (1){

        getAngle(&pitch,devAccel,devGyro);

        error = setpoint - pitch;
        float pidOutput = pid_process(pid, error);


        printf("\r error = %f, PID = %f", error, pidOutput);

>>>>>>> imuFixes
    }
}
