#include "sprite.h"

int main() {
    //Inizializzazione Variabili
    coords screenMax;
    int dirX;
    int dirY=-1;
    int newX;
    int newY;
    int msTimer;
    clock_t start, tDiff;

    //inizializzazioni ncurses
    initscr();
    noecho();
    cbreak();
    start_color();
    keypad(stdscr, true);
    curs_set(0);

    //inizializzazioni rand
    srand(time(NULL)); 

    //Rilevamento Schermo
    getmaxyx(stdscr, screenMax.y, screenMax.x); 
    
    //Gestione Schermo
    
    //Spawn palla
    ball.c.y=(screenMax.y/2);
    ball.c.x= rand() % screenMax.x;

    if(rngBool())
        dirX=ball.l*(-1);
    else
        dirX=ball.l;

    //Spawn barra
    bar.c.y=screenMax.y-BAR_DISTANCE;
    bar.c.x=((screenMax.x-(bar.l/2))/2) & ~1;

    //Set Colori
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    
    do{
        //usleep(100000);

        clear();
        //Print palla
        attron(COLOR_PAIR(2));
        mvprintw(ball.c.y, ball.c.x, ball.s);
        //Print barra
        attron(COLOR_PAIR(1));
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
            dirY*=-1;
        else if(newY>=screenMax.y){
            clear();
            endwin();
            break;
        }
        else
            ball.c.y+=dirY;

        //Gestione Collisione Palla Barra
        if((newY==bar.c.y-1) && (newX>=bar.c.x && newX<=bar.c.x+bar.l))
            dirY*=-1;


        
        //timer per il frame
        fflush(stdin);
        start=clock();
        do{
            //Gestione movimento giocatore 
            timeout(0);
            switch (getch())
            {
            case KEY_RIGHT:
                attron(COLOR_PAIR(3));
                mvprintw(bar.c.y, bar.c.x, bar.s);
                if(bar.c.x<=screenMax.x-bar.l-BAR_SPEED)
                    bar.c.x+=BAR_SPEED; 
                else
                    beep();
                break;

            case KEY_LEFT:
                attron(COLOR_PAIR(3));
                mvprintw(bar.c.y, bar.c.x, bar.s);
                if(bar.c.x>=0+BAR_SPEED)
                    bar.c.x-=BAR_SPEED;
                else
                    beep();
                break;
            
            case 113:
                clear();
                endwin();
                exit(0);
            }
            tDiff=clock()-start;
            msTimer=tDiff * 1000 / CLOCKS_PER_SEC;
            attron(COLOR_PAIR(1));
            mvprintw(bar.c.y, bar.c.x, bar.s);
            //Refresh per visualizzare
            refresh();
        }while(msTimer<FRAME_SPEED_MS);
    }while(true);
}

