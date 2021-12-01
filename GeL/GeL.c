#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>

#define MAXX 80
#define MAXY 24
#define PASSO 1
#define VEL_LADRO 100000

typedef struct{
    char c;
    int x;
    int y;
}pos;

void ladro(int pipeout);
void guardia(int pipeout);
void controllo(int pipein);
long int RNG(){return rand();};

int main(){
    int filedes[2];
    int pid_guardia;
    int pid_ladro;

    //lncurses e rand setup
    initscr();
    noecho();
    keypad(stdscr, true);
    srand((int)time(0));
    curs_set(0);
    

    if(pipe(filedes)==-1){
        perror("pipe call");
        _exit(1);
    }
    pid_ladro=fork();

    switch (pid_ladro)
    {
    case -1:
        perror("Errore nell'esecuzione fork ladro");
        exit(1);
        break;

    case 0:
        close(filedes[0]);
        ladro(filedes[1]);
        break;
    
    default:
        pid_guardia=fork();

        switch (pid_guardia)
        {
        case -1:
            perror("Errore nell'esecuzione fork guardia");
            exit(1);
            break;

        case 0:
            close(filedes[0]);
            guardia(filedes[1]);
            break;

        default:
            close(filedes[1]);
            controllo(filedes[0]);
            break;
        }

        break;
    }

    kill(pid_guardia,1);
    kill(pid_ladro,1);
    endwin();
    return 0;
}

void ladro(int pipeout){
    //coordinate iniziali in alto a sinistra
    pos pos_ladro;
    int dx,dy;
    pos_ladro.y=1;
    pos_ladro.x=1;
    pos_ladro.c='$';

    do{
        write(pipeout, &pos_ladro, sizeof(pos_ladro));
        if(RAND_MAX/2>RNG())
            dx=PASSO;
        else
            dx=-PASSO;

        if(!(pos_ladro.x+dx>0 && pos_ladro.x+dx<MAXX)) dx=-dx;

        pos_ladro.x+=dx;

        if(RAND_MAX/2>RNG())
            dy=PASSO;
        else
            dy=-PASSO;

        if(!(pos_ladro.y+dy>0 && pos_ladro.y+dy<MAXY)) dy=-dy;

        pos_ladro.y+=dy;

        usleep(VEL_LADRO);
        
    }while(true);
}

void guardia(int pipeout){
    pos pos_guardia;
    pos_guardia.c='#';
    pos_guardia.x=MAXX-1;
    pos_guardia.y=MAXY-1;
    do{
        write(pipeout, &pos_guardia, sizeof(pos_guardia));

        switch (getch())
        {
        case KEY_UP:
            if (pos_guardia.y>0)
                pos_guardia.y-=1;            
            break;

        case KEY_DOWN:
            if (pos_guardia.y<MAXY-1)
                pos_guardia.y+=1;            
            break;

        case KEY_LEFT:
            if (pos_guardia.x>0)
                pos_guardia.x-=1;            
            break;
        
        case KEY_RIGHT:
            if (pos_guardia.x<MAXX-1)
                pos_guardia.x+=1;            
            break;
        }
    }while(true);
}

void controllo(int pipein){
    pos pos_ladro, pos_guardia, rbuffer;

    do{
        read(pipein, &rbuffer, sizeof(rbuffer));

        if(rbuffer.c=='$'){
            if(pos_ladro.x!=rbuffer.x || pos_ladro.y!=rbuffer.y)
                mvaddch(pos_ladro.y,pos_ladro.x,' ');
            pos_ladro=rbuffer;
        }
        else{
            if(pos_guardia.x!=rbuffer.x || pos_guardia.y!=rbuffer.y)
                mvaddch(pos_guardia.y,pos_guardia.x,' ');
            pos_guardia=rbuffer;
        }

        mvaddch(rbuffer.y,rbuffer.x,rbuffer.c);
        refresh();

    }while(pos_guardia.x!=pos_ladro.x || pos_guardia.y!=pos_ladro.y);
}