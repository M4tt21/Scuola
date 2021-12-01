#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>

#define UI_HEIGHT 3
#define BORDER 1

#define MAXX 80
#define MAXY (24+UI_HEIGHT)
#define PASSO 1
#define VEL_VESPA 100000

typedef struct{
    char c;
    int x;
    int y;
}pos;

long int RNG(){return rand();};
