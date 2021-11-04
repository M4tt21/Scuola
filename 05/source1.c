#include<stdio.h>

int max(int a, int b){
    if (a>b)
    {
        return a;
    }
    return b;
}

int main(){
    int n1,n2;
    printf("\nN.1:");
    scanf("%d",&n1);
    printf("\nN.2:");
    scanf("%d",&n1);

    printf("%d e` il maggiore!",max(n1,n2));

    return 0;
}