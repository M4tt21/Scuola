#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int main() {
    initscr();
    noecho();
    cbreak();
    set_escdelay(0);
    clock_t t=clock();
    int i;
    while (1)
    {
        for(i=0;i++;i<100000){
            int x=i;
            i+=i*2/3*7000/2;
            i=x;
        }

        clock_t difference = clock() - t;
        int msec = difference * 1000 / CLOCKS_PER_SEC;
        printw("%i\n", msec);
        refresh();
    }
    return 0;
}