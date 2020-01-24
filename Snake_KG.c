/* Kod powstal z pomoca Alicja Pegiel  */

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

#define WIDTH 50
#define HEIGHT 25

/* CREATING PLAYABLE AREA WHERE SNAKE WILL MOVE  */

WINDOW *create_area(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);

	wrefresh(local_win);

	return local_win;
}

/* CREATING HEADLINE WITH THE GAME'S NAME  */

void *create_headline() {
        char hl1[] = " _____ _____ _____ _____ _____ \n";
        char hl2[] = "|   __|   | |  _  |  |  |   __|\n";
        char hl3[] = "|__   | | | |     |    -|   __|\n";
        char hl4[] = "|_____|_|___|__|__|__|__|_____|\n";
        mvprintw(0, 10, hl1);
        mvprintw(1, 10, hl2);
        mvprintw(2, 10, hl3);
        mvprintw(3, 10, hl4);
        refresh();
}

/* CREATING AN APPLE ON AREA  */

void create_apple(int *applex, int *appley, int *eaten, int startx, int starty, int width, int height) {
	time_t tt;
	int t = time(&tt);

	if(*eaten) {
		srand(t);
		*applex = (rand() % ((width - 1) - (startx + 2)) + (startx + 1));
		*appley = (rand() % ((height - 1) - (starty + 2)) + (starty + 1));
		*eaten = 0;
	}
	mvprintw(*appley, *applex, "@");
}

/* IF SNAKE EATS AN APPLE HE GETS A POINT  */

void eat_apple(int *snake, int applex, int appley, int *eaten, int *len, int *score) {
	int x = *snake;
	int y = *(snake + 1);

	if (x == applex && y == appley) {
		*eaten = 1;
		*len += 1;
		*score += 1;
	}
}

/* CHECK IF SNAKE TOUCH THE BORDERS OR YOURSELF  */

bool collision(int *snake, int len, int startx, int starty, int width, int height) {
	int x = *snake;
	int y = *(snake + 1);

	if (x <= startx || x > (width-1) || y <= starty || y > (height+2)) {return true;}

	for (int i = 2; i < len * 2; i += 2) {
		if (x == *(snake + i) && y == *(snake + i + 1)) {
			return true;
		}
	}
	return false;
}

/* MOVING SNAKE  */

void move_snake(int *snake, int dir_x, int dir_y, int len, int startx, int starty) {
	int x = 0, y = 0;
	int cur_x = *snake, cur_y = *(snake + 1);
	int next_x = cur_x + dir_x, next_y = cur_y + dir_y;

	*snake = next_x;
	*(snake + 1) = next_y;
	mvprintw(next_y, next_x, "O");

	for (int i = 2; i < len * 2; i += 2) {
		x = cur_x;
		y = cur_y;

		cur_x = *(snake + i);
		cur_y = *(snake + i + 1);

		next_x = x;
		next_y = y;

		*(snake + i) = next_x;
		*(snake + i + 1) = next_y;
		mvprintw(next_y, next_x, "o");
	}
}

int main(void)
{
  WINDOW * mainwin;
  int startx = 1, starty = 4;
  int height = HEIGHT, width = WIDTH;
  int len = 4;
  int score = 0;
  int eaten = 1;
  int dir_x = 1, dir_y = 0;
  int applex = 0, appley = 0;
  char dir = 'R';

  // Initializacja ncurses
  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  noecho();         // nie pokazuj wpisywanych danych
  cbreak();         // disables line buffering and erase/kill character-processing
  timeout(500);     // wait 500ms for key press
  keypad(mainwin, TRUE);
  curs_set(FALSE);

  // Tak można dac X we wskazanym miejscu lub uzyc mvaddstr jak nizej
  //move(0, 0);
  //addch('X');

  int snake[999][2];
  for (int i = 0; i < 999; i++) {
    for (int j = 0; j < 2; j++) {
      snake[i][j] = 0;
    }
  }

  snake[0][0] = startx + 1;
  snake[0][1] = starty + 1;

  //int i = 0;
  bool quit = false, flag = false;
  do {
    if(!flag) {
      clear();
      create_headline();
      mainwin = create_area(height, width, starty, startx);

      mvprintw(29, 2, "SCORE: ");
      printw("%i", score);

      create_apple(&applex, &appley, &eaten, startx, starty, width, height);
      move_snake(&snake[0][0], dir_x, dir_y, len, startx, starty);
      eat_apple(&snake[0][0], applex, appley, &eaten, &len, &score);

      refresh();
    }

    if(collision(&snake[0][0], len, startx, starty, width, height)) {
      flag = true;
      clear();
      create_headline();
      mainwin = create_area(height, width, starty, startx);
      mvprintw(17, 8, "Game Over! Your score: %d", score);
      refresh();
    }
    int c = getch();
    switch (c) 
    {
      case KEY_RIGHT:
        if (dir != 'L') {
          dir_y = 0;
          dir_x = 1;
          dir = 'R';
        }
        break;
      case KEY_LEFT:
        if (dir != 'R') {
          dir_y = 0;
          dir_x = -1;
          dir = 'L';
        }
        break;
      case KEY_UP:
        if (dir != 'D') {
          dir_y = -1;
          dir_x = 0;
          dir = 'U';
        }
        break;
      case KEY_DOWN:
        if (dir != 'U') {
          dir_y = 1;
          dir_x = 0;
          dir = 'D';
        }
        break;
      case 'q':
        quit = true;
        break;
      default:
        break;
    }

    //clear();
    //mvaddstr(10, i, "Tu pelznie waz (nacisnij 'q' by zakonczyc)");
    //refresh();
    //i++;
  } while( ! quit );


  // Czyszczenie
  nocbreak();
  echo();
  refresh();
  delwin(mainwin);
  endwin();
  return EXIT_SUCCESS;
}
