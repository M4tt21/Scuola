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
    while (1)
    {
        sleep(1);
        printw("%f\n", clock()-t);
        refresh();
    }
    return 0;
}