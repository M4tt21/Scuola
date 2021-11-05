#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
main()
{
    pid_t pid;
    printf("Unico processo con PID %d.\n",(int)getpid());
    pid=fork();
    
    if(pid == 0)
        printf("Sono il processo figlio (PID: %d).\n",(int)getpid());
    else if(pid>0)
        printf("Sono il genitore del processo con PID %d.\n",pid);
    else
        printf("Si e' verificato un errore nella chiamata a fork.\n");
}