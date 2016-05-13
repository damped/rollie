
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

        default:
        break;
      }

    }

  }
  endwin();
}
