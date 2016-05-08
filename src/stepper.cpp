/*  stepper.cpp
*  Written by Jonas Menge and Michael Jones
*
*  Accepts the period between steps
*
*  Returns curren step count
*/

#include "stepper.h"
#define RAMP 0.02


const int motor1Step = 17;
const int motor2Step = 27;
const int motor1Dir = 18;
const int motor2Dir = 22;


void stepperControl(stepper *stepper){
    motorSetup();

    while(1){
        if (stepper->period != 0.0){
            // Do math with the rate to scail it and set dir
            //printf("period = %f",*period);
            if (stepper->period > 0){
                digitalWrite(motor1Dir, HIGH);
                digitalWrite(motor2Dir, LOW);
                stepper->count--;
            } else {
                digitalWrite(motor1Dir, LOW);
                digitalWrite(motor2Dir, HIGH);
                stepper->count++;
            }

            // Do the step
            digitalWrite(motor1Step, HIGH);
            digitalWrite(motor2Step, LOW);
            wait(&stepper->period);
            digitalWrite(motor1Step, LOW);
            digitalWrite(motor2Step, HIGH);
            wait(&stepper->period);

        } else {
            delay(5);
        }
    }
}


// Initialize output pins
void motorSetup(){
    printf("starting motor thread");
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

    pinMode(motor1Step, OUTPUT);
    pinMode(motor2Step, OUTPUT);

    pinMode(motor1Dir, OUTPUT);
    pinMode(motor2Dir, OUTPUT);


}


// Alow updating the time while waiting
void wait(float *time){
    //printf("wait: %f",*time);
    for (float i = -0.01; i <= abs(*time/2.0); i = i + 10.0) // check how long we need to wait
    {
        delayMicroseconds(10);
    }
}

// Calculate the new motor speed and store it
void setSpeed(float velocity, float *pulseTimePtr) {
    *pulseTimePtr = 1000000.0*(1.0 / (MOTOR_STEPS / (MICRO_STEPS * DIA * PI))) / velocity;
    //printf("Period: %f, velocity: %f\n", *pulseTimePtr,velocity);
}
