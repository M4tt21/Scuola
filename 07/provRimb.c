#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
struct pos{
int x;  /* Coordinata x */
int y; /* Coordinata y */
};
int main() {
int maxy = 0, maxx = 0;
int newx1 = 0, newy1 = 0;
int newx2 = 0, newy2 = 0;
int direzionex1 = 1, direzioney1 = 1;
int direzionex2 = 1, direzioney2 = 1;
initscr();
noecho();
curs_set(false);
getmaxyx(stdscr, maxy, maxx); 
struct pos palla1, palla2;
palla1.x=0; palla1.y=0;
palla2.x=0; palla2.y=0;
while(true) {
  clear();
  mvprintw(palla1.y, palla1.x, "o");
  mvprintw(palla2.y, palla2.x, "O");
  refresh();
  usleep(10000);
  newx1 = palla1.x + direzionex1; newy1 = palla1.y + direzioney1;
  newx2 = palla2.x + direzionex2; newy2 = palla2.y + direzioney2;
  /* Verifica collisione bordi ­ Oggetto 1 */
  if(newx1 >= maxx || newx1 < 0) direzionex1*=-1;
  else palla1.x += direzionex1;
  if(newy1 >= maxy || newy1 < 0) direzioney1*=-1;
  else palla1.y += direzioney1;
  /* Verifica collisione bordi ­ Oggetto 2 */
  if(newx2 >= maxx || newx2 < 0) direzionex2*=-1;
  else palla2.x += direzionex2;
  if(newy2 >= maxy || newy2 < 0) direzioney2*=-1;
  else palla2.y += direzioney2;
  /* Verifica collisione tra Oggetto 1 e 2 */
  if(palla1.x == palla2.x && palla1.y == palla2.y) {flash(); break;}
  timeout(0); 
  if(getch() == 113) break;
  }
endwin();
}