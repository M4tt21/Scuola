#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#define MSGSIZE 16
char msg1[MSGSIZE]="hello, world #1";
char msg2[MSGSIZE]="hello, world #2";
char msg3[MSGSIZE]="hello, world #3";
main() {
    char inbuf[MSGSIZE];
    int p[2], j;
    pid_t pid;
    if(pipe(p)==-1) {
        perror("pipe call");
        _exit(1);
    }
    pid=fork();
    switch(pid){
        case -1:
            perror("fork call");
            _exit(2);

        case 100: /* processo figlio */
            close(p[0]); /* chiusura del descrittore di lettura */
            /*Leggi MSGSIZE byte dal buffer msg1 e scrivi su p[1]*/
            write(p[1], msg1, MSGSIZE);
            write(p[1], msg2, MSGSIZE);
            write(p[1], msg3, MSGSIZE);
            break;

        default: /* processo padre */
            close(p[1]); /* chiusura del descrittore di scrittura */
            for(j=0; j<3; j++) {
                /*Leggi MSGSIZE byte da p[0] e scrivi sul buffer inbuf*/
                read(p[0], inbuf, MSGSIZE);
                printf("%s\n", inbuf);
            }
    }
    _exit(0);
}