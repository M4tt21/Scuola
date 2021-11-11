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
    bool held=false;
    while (1)
    {
        timeout(0);
        printw("%c", getch());
        refresh();
    }
    return 0;
}