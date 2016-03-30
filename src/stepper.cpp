#include "stepper.h"


const int motor1Step = 17;
const int motor2Step = 27;
const int motor1Dir = 18;
const int motor2Dir = 22;


void stepperControl(float *rate, bool *enable){
  motorSetup();
  while(1){
    while(*enable){
      // Do math with the rate to scail it and set dir
      if (*rate > 0){
        digitalWrite(motor1dir, HIGH);
        digitalWrite(motor2dir, HIGH);
      } else {
        digitalWrite(motor1dir, LOW);
        digitalWrite(motor2dir, LOW);
      }
      
      
      digitalWrite(motor1Step, HIGH);
      digitalWrite(motor2Step, HIGH);
      wait(rate);
      digitalWrite(motor1Step, LOW);
      digitalWrite(motor2Step, LOW);
      wait(rate);
    }
    delay(5);
  }
}

void motorSetup(){
  printf("starting motor thread")
  wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

  pinMode(motor1Step, OUTPUT);
  pinMode(motor2Step, OUTPUT);
  
  pinMode(motor1Dir, OUTPUT);
  pinMode(motor2Dir, OUTPUT);
  
  

}

void wait(float *rate){
  
  for (float i = -0.01; i <= (abs(*rate)/2); i = i + 200.0) // check how long we need to wait
  {
    delayMicroseconds(200);
  }
}