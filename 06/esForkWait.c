#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

main(){
    pid_t pid;
    int status ; // conterrà lo stato
    pid = fork();
    if (pid) { // siamo nel padre (0=figlio, >0=padre, -1=errore)
        sleep(20); // attendiamo 20 secondi
        pid = wait(&status); // restituisce il PID del processo completato
        if (WIFEXITED(status)) { // !=0 se il figlio termina normalmente (exit o return), cioè non terminato da signal
            printf("stato %d\n", WEXITSTATUS(status));
        }
    }
    else { // siamo nel figlio
        printf("Processo %d, figlio.\n", getpid());
        _exit(17); // terminiamo con un valore di ritorno (exit status) di 17
    }
}
