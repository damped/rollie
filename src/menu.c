//menu
// libs
#include <ncurses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[4] = {
                        "POWER",
                        "CONTROL",
                        "TUNING",
                        "EXIT"
                  };

char *description[4] = {
                        "-           ",
                        "- movement",
                        "- change PID",
                        "- quit program"

                  };

char *tuning[7] = {
                  "POS - P",
                  "POS - I",
                  "POS - D",
                  "ANG - P",
                  "ANG - I",
                  "ANG - D",
                  "exit"
            };

typedef struct CONTROL{
            int power,control;
            float posP,posI,posD;
            float angP,angI,angD;
}CONTROL;

int rollie_menu(CONTROL *);


int main()
{
  CONTROL menu;
  rollie_menu(&menu);
  return 0;
}

int rollie_menu(CONTROL *menu)
{
  ITEM **my_items;
  ITEM **tuning_items;

	int c;
	MENU *my_menu;
  MENU *tuning_menu;

  int n_choices, i;
	ITEM *cur_item;

	/* Initialize curses */
	initscr();
  cbreak();
  noecho();
	keypad(stdscr, TRUE);

	/* Initialize items */
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)malloc((n_choices + 1)*sizeof(ITEM *));

  for(i = 0; i < n_choices; ++i)
  {
          my_items[i] = new_item(choices[i], description[i]);
  }

  my_items[n_choices] = (ITEM *)NULL;

  n_choices = ARRAY_SIZE(tuning);
  tuning_items = (ITEM **)malloc((n_choices + 1)*sizeof(ITEM *));

  for(i = 0; i < n_choices; ++i)
  {

          tuning_items[i] = new_item(tuning[i], "");
  }


  tuning_items[n_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);
  tuning_menu = new_menu((ITEM **)tuning_items);

	/* Make the menu multi valued */
	menu_opts_off(my_menu, O_ONEVALUE);

	mvprintw(LINES - 3, 0, "Use <SPACE> to select or unselect an item.");
	mvprintw(LINES - 2, 0, "<ENTER> to see presently selected items(F2 to Exit)");
	post_menu(my_menu);
	refresh();

	while((c = getch()) != KEY_F(2))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10:	/* Enter */
			{
        //menu_driver(my_menu, REQ_TOGGLE_ITEM);
        cur_item = current_item(my_menu);
        int sel = item_index(cur_item);

        switch(sel){

            case 0:
              move(20, 10);
      				clrtoeol();
              if (menu->power != 1)//(menu->power!=1)
              {
                menu->power = 1;
                mvprintw(20, 10, "ON");
              }
              else
              {
                menu->power = 0;
                mvprintw(20, 10, "OFF");
              }
              break;
            case 1:
              move(20, 0);
      				clrtoeol();

              break;
            case 2:
              unpost_menu(my_menu);
              post_menu(tuning_menu);
              refresh();

              while((c = getch()) != KEY_F(2))
              {       switch(c)
                      {	case KEY_DOWN:
                    menu_driver(tuning_menu, REQ_DOWN_ITEM);
                    break;
                  case KEY_UP:
                    menu_driver(tuning_menu, REQ_UP_ITEM);
                    break;
                  case 10:	/* Enter */

                  cur_item = current_item(tuning_menu);
                  int sel = item_index(cur_item);

                  unpost_menu(tuning_menu);

                  switch(sel)
                  {
                      case 0:
                          mvprintw(0,0,"current: %f, new = ",menu->posP);
                          break;
                      case 1:
                          mvprintw(0,0,"current: %f, new = ",menu->posI);
                          break;
                      case 2:
                          mvprintw(0,0,"current: %f, new = ",menu->posD);
                          break;
                      case 3:
                          mvprintw(0,0,"current: %f, new = ",menu->angP);
                          break;
                      case 4:
                          mvprintw(0,0,"current: %f, new = ",menu->angI);
                          break;
                      case 5:
                          mvprintw(0,0,"current: %f, new = ",menu->angD);
                          break;
                      case 6:
                          unpost_menu(tuning_menu);
                          post_menu(my_menu);
                          break;
                    }
                      refresh();
                  }
                    refresh();
                }

              break;
            case 3:
              move(20, 0);
              clrtoeol();
              mvprintw(20, 0, "EXIT");
              break;
        }
        break;
			}
		}
	}

	free_item(my_items[0]);
        free_item(my_items[1]);
	free_menu(my_menu);
	endwin();
}
