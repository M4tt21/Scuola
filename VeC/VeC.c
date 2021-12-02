#include "VeC.h"

int main(){


    
    int filedes[2];
    int pid_vespa;
    int pid_contadino;
    

    //lncurses e rand setup
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    WINDOW *ui, *game, *input;
    int r,c;
    do{
        getmaxyx(stdscr,  r,c);
        mvprintw(0,0,"Ridimensionare la finestra ad almeno [%d|%d]",(MAXY+BORDER*2)+(UI_HEIGHT+BORDER*2) , MAXX+BORDER*2);
        mvprintw(1,0,"Dimensione corrente [%d|%d]",r,c);
        mvprintw(2,0,"Ridimensionamenti futuri potrebbero causare un malfunzionamento del programma.");
        mvprintw(3,0,"Premere invio per confermare!");
        refresh();
        usleep(100);
    }while((r<(MAXY+BORDER*2)+(UI_HEIGHT+BORDER*2) || c<MAXX+BORDER*2) || getch()!=10);
    clear();

    WINDOW *win=newwin(10,20,0,0);
    refresh();
    box(win,0,0);
    wprintw(win,"this is my box");
    wrefresh(win);

    int c=wgetch(win);

    sleep(100);

    /*input=newwin(0,0,MAXX*2,MAXY*2);
	ui = newwin(UI_HEIGHT+BORDER*2, MAXX+BORDER*2, 0, 0);
	box(ui, 0 , 0);
    game = newwin(MAXY+BORDER*2, MAXX+BORDER*2, UI_HEIGHT+BORDER*2, 0);
	box(game, 0 , 0);





    
    wrefresh(ui);
    wrefresh(game);
    nodelay(ui,true);
    nodelay(stdscr,true);
    nodelay(input,true);
    nodelay(game,true);

    do{
        wrefresh(ui);
        //refresh();
        char c=wgetch(input);
        mvwprintw(ui, 1,1,"Character: %c",c);
        wrefresh(ui);
        refresh();

        sleep(1);
    }while(1);



    sleep(10000);
    

    endwin();
  noecho();
    //start_color();
    keypad(stdscr, true);
    srand((int)time(0));
    curs_set(0);

  init_pair(1, COLOR_BLACK, COLOR_BLUE); //UI BORDER
    init_pair(2, COLOR_BLACK, COLOR_WHITE); //colori ui score
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); //colore vespa
    init_pair(4, COLOR_RED, COLOR_BLACK);//colore contadino

    w = newwin(10, 10, 0, 0);
    w = newwin(10, 10, 10, 10);
	box(w, 0 , 0);		
	wrefresh(w);
    box(w, 0 , 0);	
    box(w, 0 , 0);	
    wrefresh(w);
    box(w, 0 , 0);	
    wrefresh(w);
    box(w, 0 , 0);	
    box(w, 0 , 0);	
    wrefresh(w);
    getch();

    //w=newwin(10,10,0,0);
    //wattron(w, COLOR_PAIR(1));
    //wborder(w,'X','X','X','X','X','X','X','X');
    //box(w, 0, 0);
    wrefresh(w);
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

    kill_p(w, pid_vespa,pid_contadino);*/
    return 0; 
}

void kill_p(WINDOW *w, int p1,int p2){
    kill(p1,1);
    kill(p2,1);
    endwin();
    delwin(w);
}

void vespa(int pipeout){

}

void contadino(int pipeout){

}

void print_ui(){
    
}

void AreaGioco(int pipein){
    
}