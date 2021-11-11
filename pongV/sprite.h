#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define BAR_DISTANCE 2

typedef struct{
    int x;
    int y;
}coords;

typedef struct{
    char s[10];  //sprite
    int l; //lunghezza
    coords c;
}sprite;

sprite bar = {"\223\223\223\223\223",5, 0, 0};

sprite ball = {"\u2588\u2588",2, 0, 0};


bool rngBool(){
    return rand()%2;
}