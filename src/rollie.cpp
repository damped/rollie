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
#include <thread>
//#include <wiringPi.h>

int main()
{
  using namespace std;
  unsigned int n = thread::hardware_concurrency();
  cout << n << " concurrent threads are supported.\n";
  
  
  return 0;
}
