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

#include <stdio.h>
//#include <thread>
#include <wiringPi.h>

#include "pid.c"
//#include "pidconfig.c"


// function prototypes
void loop(pid_filter_t *pid);


int main()
{
  using namespace std;
  
  pid_filter_t pid;
  pid_init(&pid);

  /* PID controller. */
  pid_set_gains(&pid, 10.0, 0.1, 4.0);
  
  loop(&pid);
  
  return 0;
}


void loop(pid_filter_t *pid)
{
  float error;
  float setpoint = 9.5;
  float motor_position = 10.0;
  while (1) {
    error = setpoint - motor_position;
    float motor_pwm = pid_process(pid, error);
    printf("SetPnt = %f, Current = %f, Error = %f, PIDout = %f\n", setpoint, motor_position, error, motor_pwm);
  }
}

