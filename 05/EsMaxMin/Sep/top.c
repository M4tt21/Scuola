#include<stdio.h>
#include<stdbool.h>
#include "max.h"
#include "min.h"

int main(){
    int n1,n2,opt;
    bool err=false;
    printf("\nN.1:");
    scanf("%d",&n1);
    printf("\nN.2:");
    scanf("%d",&n2);

    do{
        err=false;
        printf("\nTrovare il Maggiore[0] o il Minore[1]:");
        scanf("%d",&opt);
        switch (opt)
        {
        case 0:
            printf("%d e` il maggiore!\n",max(n1,n2));
            break;

        case 1:
            printf("%d e` il minore!\n",min(n1,n2));
            break;
        
        default:
            err=true;
            break;
        }

    }while(err);

    return 0;
}