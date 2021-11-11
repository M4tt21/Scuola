#include "sprite.h"

int main() {
    //Inizializzazione Variabili
    coords screenMax;
    int dirX;
    int dirY=-1;
    int newX;
    int newY;

    //inizializzazioni ncurses
    initscr();
    noecho();
    curs_set(0);

    //inizializzazioni rand
    srand(time(NULL)); 

    //Gestione Schermo

    //Rilevamento Schermo
    getmaxyx(stdscr, screenMax.y, screenMax.x); 

    //Spawn palla
    ball.c.y=screenMax.y/2;
    ball.c.x= rand() % screenMax.x;

    if(rngBool())
        dirX=ball.l*(-1);
    else
        dirX=ball.l;

    //Spawn barra
    bar.c.y=screenMax.y-BAR_DISTANCE;
    bar.c.x=((screenMax.x-(bar.l/2))/2)-1;

    do{
        usleep(10000);

        clear();
        //Print palla
        mvprintw(ball.c.y, ball.c.x, ball.s);
        //Print barra
        mvprintw(bar.c.y, bar.c.x, bar.s);
        //Refresh per visualizzare
        refresh();


        //Incremento nuove coordinate palla
        newX=ball.c.x+dirX;
        newY=ball.c.y+dirY;
        
        //Gestione Rimbalzo palla
        if(newX<0 || (newX+ball.l)>=screenMax.x)    
            dirX*=-1;
        else
            ball.c.x+=dirX;

        if(newY<0)    
            dirX*=-1;
        else if(newY>=screenMax.y)
            break;
        else
            ball.c.y+=dirY;

        


        //Gestione movimento giocatore 
        timeout(0);
        switch (getch())
        {
        case KEY_RIGHT:
            if(bar.c.x<screenMax.x-bar.l)
                bar.c.x+=1;
            else
                beep();
            break;

        case KEY_LEFT:
            if(bar.c.x>0)
                bar.c.x-=1;
            else
                beep();
            break;
        
        case 113:
            endwin();
            exit(0);
        }
    }while(true);
}

