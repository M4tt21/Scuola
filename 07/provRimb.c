#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>

int main() {
int maxy = 0, maxx = 0;
int newx = 0, newy = 0;
int direzionex = 1, direzioney = 1;
initscr();
noecho();
curs_set(false);
getmaxyx(stdscr, maxy, maxx); /* Ottiene dimensioni schermo */
int x = maxx/2, y = maxy/2; /* Centro dello schermo */
while(true) {
        getmaxyx(stdscr, maxy, maxx); /* Ottiene dimensioni schermo */
        clear();
        mvprintw(y, x, "o");
        refresh();
        usleep(40000);
        newx = x + direzionex;
        newy = y + direzioney;
        /* Inverte la direzione del movimento toccando il bordo */
        if(newx >= maxx || newx < 0){ 
            direzionex*= -1;
            flash();
        }
        else x+= direzionex;
        if(newy >= maxy || newy < 0){ 
            direzioney*= -1;
            flash();
        }
        else y+= direzioney;
        timeout(1); /* Non attende il tasto invio */
        if(getch() == 113) break; /* Esce alla pressione del tasto 'q' */
    }
    endwin();
}