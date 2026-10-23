#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
int main() {
  char mesg[] = "please input the x and y which lables the char output";
  initscr();
  raw();
  noecho();

  int x, y, input;
  int maxx, maxy;

  char sentence[65];

  while (1) {
    erase();
    getmaxyx(stdscr, maxy, maxx);
    mvprintw(maxx / 2 - 1, maxy / 2 - 1, mesg);
    refresh();
    mvaddch(0, 0, ' ');
    mvaddch(0, 2, ' ');
    mvaddch(0, 1, ',');
    refresh();

    move(0, 0);
    x = getch();
    if (x == 'q') {
      endwin();
      return EXIT_SUCCESS;
    }
    if (x < '0' || x > '9') {
      mvprintw(maxx / 2, maxy / 2 - 1, "thats the illegal x.");
      refresh();
      getch();
      endwin();
      return EXIT_FAILURE;
    }
    addch(x);
    refresh();
    move(0, 2);
    y = getch();
    if (y < '0' || y > '9') {
      mvprintw(maxx / 2, maxy / 2 - 1, "thats the illegal y.");
      refresh();
      getch();
      endwin();
      return EXIT_FAILURE;
    }
    addch(y);
    refresh(); /* the process to get the cord  */

    move(19, 5);
    printw("debug");
    refresh();
    move(y - '0', x - '0');
    getnstr(sentence, 60);
    for (int i = 0; i <= 90; i++) {
      if (sentence[i] == '\0') {
        mvprintw(maxx / 2 - 2, maxy / 2 - 1, "there is a 0,in %d", i);
        refresh();
        break;
      }
    }
    move(y - '0', x - '0');
    printw("%s", sentence); // 现在才会打印在第 2 行第 1 列
    refresh();
    getch();
  }

  refresh();
  getch();
  endwin();
  return EXIT_SUCCESS;
}
