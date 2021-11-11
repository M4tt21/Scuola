#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>

int main() {
    while (true)
    {
        printf("%c", getch());
    }
    
}