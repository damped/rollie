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
#include <math.h>

#define DEADBAND 0.0    // Absolute amount of angle error that is exeptable

// function prototypes
void loop(pid_filter_t *pidAngle, pid_filter_t *pidPos, int devAccel, int devGyro, stepper *stepper);


int main()
{
    /* Angle PID controller setup */
    pid_filter_t pidAngle;
    pid_init(&pidAngle);

    /* Position PID controller setup */
    pid_filter_t pidPos;
    pid_init(&pidPos);

    /* Set the maximum positinal PID limit */
    pid_set_integral_limit(&pidPos,10.0);

    /* Preset the integral */
    pid_set_integral(&pidPos,6.0);

    // pid_set_gains(&pid, 0.026, /*0.0000108*/0.0, 0.000024);
    // pid_set_gains(&pid, 0.020, /*0.0000108*/0.0, 0.00004);
    // pid_set_gains(&pid, 0.027,/* 0.0000808*/0.0, /*0.000024*/ 0.001);
    // pid_set_gains(&pid, 0.029,/* 0.0000808*/0.0, /*0.000024*/ 0.001);
    // pid_set_gains(&pid, 0.050,/* 0.0000808*/0.0, /*0.000024*/ 0.002);
    // pid_set_gains(&pid, 0.20,/* 0.0000808*/0.00001, /*0.000024*/ 0.003);
    //pid_set_gains(&pidAngle, 0.260,/* 0.0000808*/0.0000, /*0.000024*/ 0.000010);
    //pid_set_gains(&pidPos, -0.0000000000,/* 0.0000808*/0.000007, /*0.000024*/ 0.05);

    pid_set_gains(&pidAngle, 0.250, 0.0000, 0.000010);
    pid_set_gains(&pidPos, 0.0000000000, 0.000007, 0.05);



    /* IMU setup */
    int devAccel = accConfig();
    int devGyro = gyroConfig();
/*    float pitch = ;
    for (size_t i = 0; i < 200; i++) {
      getAngle(&pitch,devAccel,devGyro); // Get an agle to clear out the crap
    }
*/

    /* Start Stepper Motor Thread */
    stepper stepper;
    setSpeed(0.0, &stepper.period);

    std::thread t_stepper;
    t_stepper = std::thread(stepperControl, &stepper);

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

    loop(&pidAngle, &pidPos, devAccel, devGyro, &stepper);


    return 0;
}


void loop(pid_filter_t *pidAngle, pid_filter_t *pidPos, int devAccel, int devGyro, struct stepper *stepper)
{
    float errorPos = 0.0;
    float setpointPos = 0.0;
    float pitch = 0.0;
    float errorAngle = 0.0;
    float setpointAngle = 0.0;
    float pidOutput = 0.0;

    //for(int i = 0; i >= 10; i++) { getAngle(&pitch,devAccel,devGyro); }

    while (1){
//	time = micros();

        getAngle(&pitch,devAccel,devGyro);

        //printf("\rGA: %u                   ", (micros()-time));

         //if(abs(error) < DEADBAND){
         //  error = 0;
         //}


	/////////// Get and set the frequency
	//pid_set_frequency(pidPos, (float)(micros() - pidTimer));
	//pid_set_frequency(pidAngle, (float)(micros() - pidTimer));
	//printf("%f", (float)(micros() - pidTimer));
	//pidTimer = micros();



        errorPos = setpointPos - stepper->count;
        setpointAngle = pid_process(pidPos, errorPos);

        errorAngle = setpointAngle - pitch;
        pidOutput = pid_process(pidAngle, errorAngle);

        setSpeed(pidOutput, &stepper->period);
	//printf("\r Comp Angle: %0.2f", pitch);
        printf("\rerPos = %f, spAngle = %f, ActualA = %f, erAngle = %f, PID = %f",errorPos, setpointAngle, pitch, errorAngle, pidOutput);

    }
}
