#include<stdio.h>
#include<stdbool.h>
#include "min.h"


int min(int a, int b){
    if (a<b)
    {
        return a;
    }
    return b;
}