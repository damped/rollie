#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

//constants
#define MOTOR_STEPS 400.0   // Full steps per rotation of the motor
#define MICRO_STEPS 0.5     // Micro steps (half steps = 0.5)
#define DIA 0.085           // Daiameter in m

#define PI  3.14159265359 // Its pi day... need at least 11 decimals



// function prototypes
void motorSetup();      // Initialize motor pins
void wait(float time);  // Wait loop
void stepperControl(float *period);
void setSpeed(float velocity, float *pulseTimePtr);


#endif
