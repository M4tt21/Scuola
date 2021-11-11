#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#define MAXX     80 /* Numero di colonne dello schermo */
#define MAXY     24 /* Numero di righe dello schermo */
struct posizione {
  int x;        // coordinata x
  int y;        // coordinata y
};

int main()
{
    initscr();    /* Inizializza lo schermo */
    noecho();     /* Disabilita la visualizzazione dei tasti premuti */
    keypad(stdscr, true);  /* Abilita la gestione dei tasti freccia */
    curs_set(0);  /* Nasconde il cursore */

    struct posizione coordsObj = { MAXX/2, MAXY/2 };
    
    do{
        clear();
        mvaddch(coordsObj.y, coordsObj.x, '+');
        refresh();
        int c = getch();
        switch (c)
        {
        case KEY_UP:
            if (coordsObj.y>0)
            {
                coordsObj.y-=1;
            }
            break;

        case KEY_DOWN:
            if (coordsObj.y<MAXY-1)
            {
                coordsObj.y+=1;
            }
            break;

        case KEY_LEFT:
            if (coordsObj.x>0)
            {
                coordsObj.x-=1;
            }
            break;

        case KEY_RIGHT:
            if (coordsObj.x<MAXX-1)
            {
                coordsObj.x+=1;
            }
            break;
        
        case 113:
            endwin();
            exit(0);
        }
    }while(true);
}