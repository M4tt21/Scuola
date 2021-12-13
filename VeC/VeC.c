#include "VeC.h"

int main(){
    int filedes[2];
    int pid_vespa;
    int pid_contadino;
    
    //lncurses e rand setup
    srand((int)time(0));
    initscr();
    cbreak();
    noecho();
    start_color();
    curs_set(0);
    keypad(stdscr, true);
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


    //input=newwin(0,0,MAXX*2,MAXY*2);
    //refresh();
	ui = newwin(UI_HEIGHT+BORDER*2, MAXX+BORDER*2, 0, 0);
    refresh();	
    game = newwin(MAXY+BORDER*2, MAXX+BORDER*2, UI_HEIGHT+BORDER*2, 0);
    refresh();

    box(ui, 0, 0);
    box(game, 0, 0);
    refresh();

    wrefresh(ui);
    wrefresh(game);
    
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); //colore vespa
    init_pair(2, COLOR_RED, COLOR_BLACK);//colore contadino

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
            AreaGioco(filedes[0],ui,game);
            break;
        }
        break;
    }
    kill_p(pid_vespa,pid_contadino);
    return 0; 
}

void kill_p(int p1,int p2){
    kill(p1,1);
    kill(p2,1);
    endwin();
}

void vespa(int pipeout){
    pos pos_vespa;
    pos_vespa.c='^';
    pos_vespa.x=2;
    pos_vespa.y=2;
    int dx,dy;
    dx=dy=-2;
    do
    {
        write(pipeout, &pos_vespa, sizeof(pos_vespa));
        if((pos_vespa.x+dx<0 || pos_vespa.x+dx>MAXX-1) || (pos_vespa.y+dy<0 || pos_vespa.y+dy>MAXY-1) || (dx==-2) || (RNG()%RAND_CHANGE==0)){    //cambiamento direzione
            switch (RNG()%3) //direzione x
            {
            case 0: 
                dx=0-PASSO;
                break;
            
            case 1: 
                dx=0;
                break;

            case 2: 
                dx=PASSO;
                break;
            }
            switch (RNG()%3) //direzione y
            {
            case 0: 
                dy=0-PASSO;
                break;
            
            case 1: 
                dy=0;
                break;

            case 2: 
                dy=PASSO;
                break;
            }
            if(dx==0 && dy==0)
                dx=-2;
        }
        else{   //Movimento
            pos_vespa.x+=dx;
            pos_vespa.y+=dy;
        }
        if(dy==0)
            usleep(VEL_VESPA/2);
        else
            usleep(VEL_VESPA);
    } while (true);
}

void contadino(int pipeout){
    pos pos_con;
    pos_con.c='#';
    pos_con.x=MAXX/2;
    pos_con.y=MAXY/2;
    do{
        write(pipeout, &pos_con, sizeof(pos_con));
        switch (getch())
        {
        case KEY_UP:
            if(pos_con.y>0)
                pos_con.y-=1;
            break;
        
        case KEY_DOWN:
            if(pos_con.y<MAXY-1)
                pos_con.y+=1;
            break;

        case KEY_LEFT:
            if(pos_con.x>0)
                pos_con.x-=1;
            break;

        case KEY_RIGHT:
            if(pos_con.x<MAXX-1)
                pos_con.x+=1;
            break;
        }
    }while(true);
}

void AreaGioco(int pipein, WINDOW *ui, WINDOW *game){
    int vite=N_VITE,i,j;
    pos pos_vespa, pos_con, rbuffer, pos_trap[N_TRAP];
    pos_vespa.x=-BORDER*2;
    pos_vespa.y=-BORDER*2;
    pos_con.x=-BORDER*2;
    pos_con.y=-BORDER*2;
    for(i=0; i<N_TRAP; i++){
        pos_trap[i].x=-BORDER*2;
        pos_trap[i].c='X';

    }
    time_t start=time(NULL);

    do{
        read(pipein, &rbuffer, sizeof(rbuffer));
        if(rbuffer.c=='#'){
            if(pos_con.x!=rbuffer.x || pos_con.y!=rbuffer.y)
                mvwaddch(game, pos_con.y+BORDER, pos_con.x+BORDER, ' ');
            pos_con=rbuffer;
        }
        else{
            if(pos_vespa.x!=rbuffer.x || pos_vespa.y!=rbuffer.y)
                mvwaddch(game, pos_vespa.y+BORDER, pos_vespa.x+BORDER, ' ');
            pos_vespa=rbuffer;
        }
        
        //Generazione Trappole
        if(time(NULL)-start>=TIMER_TRAP){

            for(i=0; i<N_TRAP; i++)//Elimina posizioni precedenti
                mvwaddch(game, pos_trap[i].y+BORDER, pos_trap[i].x+BORDER, ' ');
            
            for(i=0; i<N_TRAP; i++){
                bool rigenera;
                do{
                    rigenera=false;
                    pos_trap[i].x=RNG()%MAXX;
                    pos_trap[i].y=RNG()%MAXY;
                    for(j=0; j<N_TRAP; j++){
                        if((i!=j) && (isCollided(pos_trap[i],pos_trap[j])))
                            rigenera=true;
                    }
                }while(rigenera);
            }

            start=time(NULL);
        }

        //cpllisione con trap
        for(i=0; i<N_TRAP; i++){
            if(isCollided(pos_vespa,pos_trap[i])){
                vite++;
                pos_trap[i].x=MAXX*2;//butto la trappola fuori
            }
        }

        //collisione con vespa
        if(isCollided(pos_con, pos_vespa))
            vite--;
        
        for(i=0; i<N_TRAP; i++)
            mvwaddch(game,pos_trap[i].y+BORDER,pos_trap[i].x+BORDER,pos_trap[i].c);
        mvwaddch(game,rbuffer.y+BORDER,rbuffer.x+BORDER,rbuffer.c);
        wrefresh(game);
    } while (vite>0);
}

bool isCollided(pos p1, pos p2){
    return ((p1.x==p2.x) && (p1.y==p2.y));
}