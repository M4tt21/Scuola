#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    execl("/bin/pwd", "pwd", (char *)0);
    execl("/bin/ls", "ls -l", (char *)0);
    return 0;
}