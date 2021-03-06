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

#define MAXX (80+(BORDER*2))
#define MAXY (24+UI_HEIGHT+BORDER)
#define PASSO 1
#define VEL_VESPA 70000
#define RAND_CHANGE 10
#define N_VITE 3
#define N_TRAP 3
#define TIMER_TRAP 10

typedef struct{
    char c;
    int x;
    int y;
}pos;

long int RNG(){return rand();};

bool isCollided(pos p1, pos p2);
void vespa(int pipeout);
void contadino(int pipeout);
void AreaGioco(int pipein, WINDOW *ui, WINDOW *game);
void kill_p(int p1,int p2);