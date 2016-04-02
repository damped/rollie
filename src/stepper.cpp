#include "stepper.h"
#define RAMP 0.02


const int motor1Step = 17;
const int motor2Step = 27;
const int motor1Dir = 18;
const int motor2Dir = 22;


void stepperControl(float *period){
  motorSetup();
  bool enable = 1;
  float time = 1000.0;
  while(1){
    while(enable){
      // Do math with the rate to scail it and set dir
      //printf("rate = %f\n",*rate);
      if (*period > 0){
        digitalWrite(motor1Dir, HIGH);
        digitalWrite(motor2Dir, HIGH);
      } else {
        digitalWrite(motor1Dir, LOW);
        digitalWrite(motor2Dir, LOW);
      }


      if (*period > time) {
	time = time + RAMP;
      } else if (*period < time) {
	time = time - RAMP;
      }

      digitalWrite(motor1Step, HIGH);
      digitalWrite(motor2Step, HIGH);
      wait(time);
      digitalWrite(motor1Step, LOW);
      digitalWrite(motor2Step, LOW);
      wait(time);
    }
    delay(5);
  }
}

void motorSetup(){
  printf("starting motor thread");
  wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

  pinMode(motor1Step, OUTPUT);
  pinMode(motor2Step, OUTPUT);

  pinMode(motor1Dir, OUTPUT);
  pinMode(motor2Dir, OUTPUT);



}

void wait(float time){

  for (float i = -0.01; i <= (time/2.0); i = i + 10.0) // check how long we need to wait
  {
    delayMicroseconds(10);
  }
}

void setSpeed(float velocity, float *pulseTimePtr) {
    pulseTimePtr = 1.0 / ((MOTOR_STEPS / (MICRO_STEPS * DIA * PI)) * velocity);
}
