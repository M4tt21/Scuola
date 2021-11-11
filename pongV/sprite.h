#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


#define BAR_DISTANCE 3
#define BAR_SPEED 2
#define FRAME_SPEED_MS 200


typedef struct{
    int x;
    int y;
}coords;

typedef struct{
    char s[10];  //sprite
    int l; //lunghezza
    coords c;
}sprite;

sprite bar = {"          ",10, 0, 0};

sprite ball = {"  ",2, 0, 0};


bool rngBool(){
    return rand()%2;
}