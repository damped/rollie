/*************************************************************
*
*   rollie.cpp - Self balencing robot project
*
*   Authours: Jonas Menge and Michael Jones
*
*   Usage: sudo ./rollie
*
*
*************************************************************/
#include "imu.h"        // Inertial measurment unit for getting angles
#include "pid.h"        // PID Controller
#include "stepper.h"    // Stepper motor controller

#include <stdio.h>
#include <wiringPi.h>   // For interfacing whith the Raspberry Pi hardware
#include <thread>       // To run concurrent pocesses
#include <math.h>

#define DEADBAND 0.0    // Absolute amount of angle error that is exeptable

// function prototypes
void loop(pid_filter_t *pidAngle, pid_filter_t *pidPos, int devAccel, int devGyro, stepper *stepper);


int main()
{

    // Angle PID controller setup
    pid_filter_t pidAngle;
    pid_init(&pidAngle);

    // Position PID controller setup
    pid_filter_t pidPos;
    pid_init(&pidPos);

    // Set the pid frequency
    pid_set_frequency(&pidPos, 100);
    pid_set_frequency(&pidAngle, 100);

    // Set the maximum positinal PID limit
    pid_set_integral_limit(&pidPos,1428571.0); // 10 degrees max

    // Preset the integral
  //  pid_set_integral(&pidPos, 857142.8); // set to 6 degrees

    // Tune the PID controller
    pid_set_gains(&pidAngle, 0.15, 5.6500, 0.00000);
    pid_set_gains(&pidPos, 0.00005, 0.0000050, 0.00000);

    // Start Stepper Motor Thread
    stepper stepper;                    // Create stepper struture
    setSpeed(0.0, &stepper.period);     // Preset the period to 0.0

    std::thread t_stepper;              // Create the stepper thead
    t_stepper = std::thread(stepperControl, &stepper);

    //setup IMU
    int devGyro = gyroConfig();
    int devAccel = accConfig();

    // Balencing loop
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
    float p0,p1 = 0.0;

    while (1){
        // Simple avreraging
        p0 = pitch;
        getAngle(&pitch,devAccel,devGyro);
        p1 = pitch;
        getAngle(&pitch,devAccel,devGyro);
        pitch = (pitch + p0 + p1) / 3.0;
/*
        // Limit positinal range to prevent interator from overflowing too quikly
        if (500 < stepper->count)
        {
            stepper->count = 500;
        } else if (-500 > stepper->count) {
            stepper->count = -500;
        }
*/

        //////////// PID Controller ///////////

        // Error = Positional setpoint - actual position
        errorPos = setpointPos - stepper->count;
        setpointAngle =- 0.94+pid_process(pidPos, errorPos);
        // Outputs the setpint angle for the next PID

        // Errorr = Anguar setpoint - acutal angle
        errorAngle = setpointAngle - pitch;
        pidOutput = pid_process(pidAngle, errorAngle);
        // Outputs the motor velocity in m/s

        // Calculate and set the motor speed
        setSpeed(pidOutput, &stepper->period);
        //printf("\r Comp Angle: %0.2f", pitch);
        printf("\rerPos = %f, spAngle = %f, ActualA = %f, erAngle = %f, PID = %f",errorPos, setpointAngle, pitch, errorAngle, pidOutput);

    }
}
