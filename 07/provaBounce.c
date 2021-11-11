#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
int main() {
    int maxy = 0, maxx = 0;
    int newx = 0;
    int direzione = 1;
    initscr();
    noecho();
    curs_set(false);
    getmaxyx(stdscr, maxy, maxx);  /* Ottiene dimensioni schermo */
    int x = maxx/2, y = maxy/2;  /* Centro dello schermo */
    while(true) {
        clear();
        mvprintw(y, x, "\51");
        refresh();
        usleep(40000);
        newx = x + direzione;
        /* Inverte la direzione del movimento toccando il bordo */
        if(newx >= maxx || newx < 0) direzione*= -1;
        else x+= direzione;
        timeout(1); /* Non attende il tasto invio */
        if(getch() == 113) break; /* Esce alla pressione del tasto 'q' */
    }
    endwin();
}