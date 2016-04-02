#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

// function prototypes
void motorSetup();      // Initialize motor pins
void wait(float time);  // Wait loop
void stepperControl(float *rate);
void setSpeed(float velocity, float *pulseTimePtr);

//constants
#define PI  3.14159265359 // Its pi day... need at least 11 decimals

#endif
