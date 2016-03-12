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
//#include <wiringPi.h>

int main()
{
  using namespace std;
  
  pid_filter_t pid;
  pid_init(&pid);

  /* PID controller. */
  pid_set_gains(&pid, 10., 0, 4.);
  
  loop(&pid);
  
  return 0;
}


void loop(pid_filter_t *pid)
{
  while (1) {
    error = setpoint - motor_position;
    motor_pwm = pid_process(&pid, error);
    
  }
}

