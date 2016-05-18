#include "rolliemenu.h"

//initializes curses and enables keyboard
void initialize(void)
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}


//prints information and controls pos
void rollieControl(control *control)
{
  int key = 0;     //preset key

  initialize();       //start curses

  mvprintw(2, 0, "press F2 to exit");
  refresh();


  while((key = getch())!= KEY_F(2))
  {

    while ((key = getch()) != 'q')
    {
      //clear old junk
      move(10,10);
      clrtoeol();
      move(12,10);
      clrtoeol();

      //print new junk
      mvprintw( 10, 10 , "position: %.2f",(control->setPos)*0.00033);
      mvprintw( 12, 10 , "angle:    %.2f", control->angle);

      refresh();


      switch (key)
      {
        case KEY_UP:
            control->setPos += 10;
            break;

        case KEY_DOWN:
            control->setPos -= 10;
            break;

        case 'p':
            if(control->power == 0)
            control->power = 1;
            else control->power = 0;

        case 'f': // Angle P down
            control->angleKp -= 0.001;
            break;

        case 'r': // Angle P up
            control->angleKp += 0.001;
            break;

        case 'g': // Angle I down
            control->angleKi -= 0.001;
            break;

        case 't': // Angle I up
            control->angleKi += 0.001;
            break;

        case 'h': // Angle D down
            control->angleKd -= 0.00001;
            break;

        case 'y': // Angle D up
            control->angleKd += 0.00001;
            break;

        case 'j': // Pos P down
            control->posKp -= 0.0000001;
            break;

        case 'u': // Pos P up
            control->posKp += 0.0000001;
            break;

        case 'k': // Pos I down
            control->posKi -= 0.000000001;
            break;

        case 'i': // Pos I up
            control->posKi += 0.000000001;
            break;

        case 'l': // Pos D down
            control->posKd -= 0.000000001;
            break;

        case 'o': // Pos D up
            control->posKd += 0.000000001;
            break;

        default:
            break;
      }

    }

  }
  endwin();
}
