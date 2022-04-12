#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *p;
    p = (int *)malloc(4*sizeof(int));

    p[0] = 12;
    p[1] = 24;
    *(p+2) = 36;
}