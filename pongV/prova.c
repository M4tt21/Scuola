#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int main() {
    while (1)
    {
        printf("%c", getch());
    }
    return 0;
}