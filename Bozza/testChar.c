#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
int main() {
    int maxy = 0, maxx = 0;
    int newx = 0;
    int i=0;
    int direzione = 1;
    initscr();
    noecho();
    curs_set(false);
    getmaxyx(stdscr, maxy, maxx);  /* Ottiene dimensioni schermo */
    int x = maxx/2, y = maxy/2;  /* Centro dello schermo */
    while(i<300) {
        printw("%c : [%d] || ", i, i);
        refresh();
        i++;
        usleep(40000);
    }
    endwin();
}