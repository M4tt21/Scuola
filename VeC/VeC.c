#include "VeC.h"

void vespa(int pipeout);
void contadino(int pipeout);
void AreaGioco(int pipein);
void print_ui(void);
void kill_p(int p1,int p2);

int main(){
    int filedes[2];
    int pid_vespa;
    int pid_contadino;

    //lncurses e rand setup
    initscr();
    noecho();
    start_color();
    keypad(stdscr, true);
    srand((int)time(0));
    curs_set(0);

    init_pair(1, COLOR_BLACK, COLOR_BLUE); //UI BORDER
    init_pair(2, COLOR_BLACK, COLOR_WHITE); //colori ui score
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); //colore vespa
    init_pair(4, COLOR_RED, COLOR_BLACK);//colore contadino

    attron(COLOR_PAIR(1));
    border('  ','  ',' ',' ',' ',' ',' ',' ');
    refresh();
    print_ui();

    if(pipe(filedes)==-1){
        perror("pipe call");
        _exit(1);
    }

    pid_vespa=fork();

    switch(pid_vespa)
    {
    case -1:
        perror("Errore nell'esecuzione fork vespa");
        exit(1);
        break;

    case 0:
        close(filedes[0]);
        vespa(filedes[1]);
        break;
    
    default:
        pid_contadino=fork();

        switch (pid_contadino)
        {
        case -1:
            perror("Errore nell'esecuzione fork contadino");
            exit(1);
            break;

        case 0:
            close(filedes[0]);
            contadino(filedes[1]);
            break;

        default:
            close(filedes[1]);
            AreaGioco(filedes[0]);
            break;
        }

        break;
    }


    getch();

    kill_p(pid_vespa,pid_contadino);
    return 0;
}

void kill_p(int p1,int p2){
    kill(p1,1);
    kill(p2,1);
    endwin();
}

void vespa(int pipeout){

}

void contadino(int pipeout){

}

void print_ui(){
    
}

void AreaGioco(int pipein){

}