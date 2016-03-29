#include <pthread.h> 
#include <stdio.h>
#include <wiringPi.h>

const int motor1Step = ;
const int motor2Step = ;
const int motor1Dir = ;
const int motor2Dir = ;


void stepperControl(float *rate, bool *enable){
  motorSetup();
  while(enable){
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
    wait(&rate);
    digitalWrite(motor1Step, LOW);
    digitalWrite(motor2Step, LOW);
    wait(&rate);
    
  }
}

void motorSetup(){
  wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

  pinMode(motor1Step, OUTPUT);
  pinMode(motor2Step, OUTPUT);
  
  pinMode(motor1Dir, OUTPUT);
  pinMode(motor2Dir, OUTPUT);
  
  

}

void wait(float *rate){
  
  for (float i = 0; i <= (abs(*rate)/2); i = i + 500.0) // check how long we need to wait
  {
    delayMicroseconds(500);
  }
}