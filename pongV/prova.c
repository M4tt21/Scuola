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
    while (1)
    {
        printw("%c", getch());
        refresh();
    }
    return 0;
}