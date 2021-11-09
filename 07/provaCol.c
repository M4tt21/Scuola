#include <stdio.h>
#include <ncurses.h>
int main() { 
    initscr(); 
    start_color();
    init_pair(1,COLOR_YELLOW,COLOR_BLUE); 
    init_pair(2,COLOR_BLACK,COLOR_WHITE);
    init_pair(3,COLOR_BLACK,COLOR_RED);
    printw("Coppia di colori predefinita\n"); 
    attron(COLOR_PAIR(1)); 
    printw("Coppia di colori giallo su blu\n"); 
    attron(COLOR_PAIR(2)); 
    printw("Coppia di colori nero su bianco\n\n"); 
    printw("Premi un tasto\n");
    refresh(); 
    getch(); 
    printw("Cambiato il colore dello sfondo in rosso... Premi un tasto per uscire");
    bkgd(COLOR_PAIR(3));
    refresh(); 
    getch(); 
    endwin();
    return 0; 
}