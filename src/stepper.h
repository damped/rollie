#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

// function prototypes
void motorSetup();
void wait(float time);
void stepperControl(float *rate);



#endif
