#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

/** Funkcja tworzy okno do grania w weza*/

WINDOW *gamewindow(int endy, int endx, int starty, int startx) {

  WINDOW *game;

  game = newwin(endy, endx, starty, startx);
  box(game, 0, 0);
  wrefresh(game);

  return game;
}

/** Funkcja tworzy tytul gry z wykorzysaniem ascii art*/

void *title(int startx, int endx) {

  int delta = (endx-startx);

  char part1[] = "                 _       \n";
  char part2[] = "                | |      \n";
  char part3[] = " ___ _ __   __ _| | _____                    __   \n";
  char part4[] = "/ __| '_ \\ / _` | |/ / _ \\       _______    / *_>-<\n";
  char part5[] = "\\__ \\ | | | (_| |   <  __/   ___/ _____ \\__/ /    \n";
  char part6[] = "|___/_| |_|\\__,_|_|\\_\\___|  <____/     \\____/     \n";
  mvprintw(0, delta/3, part1);
  mvprintw(1, delta/3, part2);
  mvprintw(2, delta/3, part3);
  mvprintw(3, delta/3, part4);
  mvprintw(4, delta/3, part5);
  mvprintw(5, delta/3, part6);

  refresh();
}

/** Funkcja dodaje nowa lokalizacje jedzonka, jesli zostalo zjedzone.
  * Jesli nie jest zjedzone, zostaje w tym samym miejscu.
*/

void make_food(int *foodX, int *foodY, int *eaten, int *startx, int *endx, int *starty, int *endy) {

  time_t tt;
  int s = time(&tt);

  if (*eaten) {
    srand(s);
    *foodX = (rand() % (*endx - *startx) + *startx);
    *foodY = (rand() % (*endy - *starty) + *starty);
    *eaten = 0;
  }

  mvprintw(*foodY, *foodX, "@");
}

/** Jesli waz zje jedzonko, zdobywa punkt */

void eat_food(int *snake, int foodX, int foodY, int *eaten, int *len, int *score) {

  int x = *snake;
  int y = *(snake+1);
  if (x == foodX && y == foodY) {
    *eaten = 1;
    *len += 1;
    *score += 1;
    int slen = *len;
    int lastX = *(snake + slen*2-2);
    int lastY = *(snake + slen*2-2+1);
    *(snake + slen*2) = lastX;
    *(snake + slen*2+1) = lastY;
  }
}

 /** Przesuwa weza o jeden punkt w jakims kierunku. */

void move_snake(int *snake, int dirX, int dirY, int len, int startx, int starty) {

  int oldX = startx+1, oldY = starty+1;
  int curX = *snake, curY = *(snake+1);
  int nextX = curX + dirX, nextY = curY + dirY;

  *snake = nextX;
  *(snake+1) = nextY;
  mvprintw(nextY, nextX, "Q");

  for (int i=2; i<len*2; i+=2) {
    oldX = curX;
    oldY = curY;
    curX = *(snake+i);
    curY = *(snake+i+1);
    nextX = oldX;
    nextY = oldY;
    *(snake+i) = nextX;
    *(snake+i+1) = nextY;

    mvprintw(nextY, nextX, "o");
  }
}

int collide(int *snake, int len, int *startx, int *endx,int *starty, int *endy) {

  int x = *snake;
  int y = *(snake+1);

  if (x<=*startx || x>=*endx || y<*starty || y>=*endy) {
    return 1;
  }


  for (int i = 2; i < len*2+2; i+=2) {
    if (x == *(snake+i) && y == *(snake+i+1)) {
      return 1;
    }
  }
  return 0;
}

int main(void)
{
  WINDOW *mainwin, *gamewin;

  // Initializacja ncurses
  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  noecho();         // nie pokazuj wpisywanych danych
  cbreak();         // disables line buffering and erase/kill character-processing
  timeout(500);     // wait 500ms for key press

  keypad(mainwin, TRUE);
  curs_set(0);

  // Tak można dac X we wskazanym miejscu lub uzyc mvaddstr jak nizej
  //move(0, 0);
  //addch('X');

  // Zmienne

  int dirX = 1, dirY = 0;        // kierunek po osi X i Y
  int foodX = 0, foodY = 0;      // pozycja jedzonka
  int eaten = 1;                 // zjedzone jedzonko 1, nie zjedzone 0
  int len = 3;                   // dlugosc weza

  int startx = 2, starty = 7, endy = 45, endx = 90;
  int score = 0;

 // Inicjalizacja weza

  int snake[100][2];

  for (int el=0; el<100; el++) {
    for (int c=0; c<2; c++) {
      snake[el][c] = 0;
    }
  }

  snake[0][0] = startx+1;
  snake[0][1] = starty+1;

  //  int i = 0;
  bool quit = false;
  do {

    clear();

    title(startx, endx);
    mainwin = gamewindow(endy, endx, starty, startx);

    mvprintw(6, 2, "Score: %d", score);

    make_food(&foodX, &foodY, &eaten, &startx, &endx, &starty, &endy);
    move_snake(&snake[0][0], dirX, dirY, len, startx, starty);
    eat_food(&snake[0][0], foodX, foodY, &eaten, &len, &score);

    refresh();

    if (collide(&snake[0][0], len, &startx, &endx, &starty, &endy)) {
      clear();
      title(startx, endx);
      mainwin = gamewindow(endy, endx, starty, startx);
      mvprintw(endy/5, endx/(2.5), "GAME OVER - SCORE: %d", score);
      refresh();
    }

    unsigned int c = getch();
    switch (c)
    {
      case KEY_RIGHT:
        dirY = 0;
        dirX = 1;
        break;
      case KEY_LEFT:
        dirY = 0;
        dirX = -1;
        break;
      case KEY_UP:
        dirY = -1;
        dirX = 0;
        break;
      case KEY_DOWN:
        dirY = 1;
        dirX = 0;
        break;
      case 'q':
        quit = true;
        break;
      default:
        break;
    }

   //   clear();
   //   mvaddstr(10, i, "Tu pelznie waz (nacisnij 'q' by zakonczyc)");
   //   refresh();
   //   i++;
  } while( !quit );


  // Czyszczenie
  nocbreak();
  echo();
  refresh();
  delwin(mainwin);
  endwin();
  return EXIT_SUCCESS;
}
