#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid1, pid2;
    pid1 = fork();
    switch(pid1) {
        case -1: // ERRORE
            printf("Fork Failed\n");
            break;
        case 0: // FIGLIO 1
            execl("/bin/pwd", "pwd", (char *)0);
            printf("exec failed\n"); // DI NORMA NON ESEGUITO
            break;
        default: //Padre
            wait((int *)0);
            fflush(stdin);
            printf("pwd OK\n");
            pid2 = fork();
            switch (pid2)
            {
            case -1:
                printf("Fork Failed\n");
                break;

            case 0: // FIGLIO 2
                execl("/bin/ls", "ls", "-l", (char *)0);
                printf("exec failed\n"); // DI NORMA NON ESEGUITO
                break;
            
            default:
                wait((int *)0);
                fflush(stdin);
                printf("ls -l OK\n");

                break;
            }

            break;
    }
}