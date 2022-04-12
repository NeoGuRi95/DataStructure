#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *words[4]; //string 포인터(배열)를 4개 담을 수 있는 배열 
    int n = 0;
    char BUFFER[100]; //길이100의 string 포인터(배열)

    while(n < 4 && scanf("%s", BUFFER) != EOF){
        words[n] = strdup(BUFFER); //BUFFER string값을 복사한 새로운 메모리영역의 주소값을 리턴
        n++;
    }

    for (int i=0; i<4; i++)
        printf("%s\n", words[i]);
}