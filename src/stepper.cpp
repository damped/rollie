#include "stepper.h"


const int motor1Step = 17;
const int motor2Step = 27;
const int motor1Dir = 18;
const int motor2Dir = 22;


void stepperControl(float *rate){
while(1){
printf("%f\n",*rate);
}
/*  motorSetup();
  bool enable = 1;
  while(1){
    while(enable){
      // Do math with the rate to scail it and set dir
      if (*rate > 0){
        digitalWrite(motor1Dir, HIGH);
        digitalWrite(motor2Dir, HIGH);
      } else {
        digitalWrite(motor1Dir, LOW);
        digitalWrite(motor2Dir, LOW);
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
*/
}

void motorSetup(){
  printf("starting motor thread");
  wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

  pinMode(motor1Step, OUTPUT);
  pinMode(motor2Step, OUTPUT);
  
  pinMode(motor1Dir, OUTPUT);
  pinMode(motor2Dir, OUTPUT);
  
  

}

void wait(float *rate){
  
  for (float i = -0.01; i <= (*rate/2.0); i = i + 200.0) // check how long we need to wait
  {
    delayMicroseconds(200);
  }
}