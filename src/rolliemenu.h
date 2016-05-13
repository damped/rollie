#ifndef ROLLIEMENU_H_
#define  ROLLIEMENU_H_


#include <ncurses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct control
{
    bool  power,
          motors;

    float position,
          angle,

          setPos;

}control;

//function prototypes
void initialize(void);           //function to initialize terminal
void rollieControl(control *);   //function to read control inputs

#endif
