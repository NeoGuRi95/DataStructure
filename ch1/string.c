#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *words[4]; //string ������(�迭)�� 4�� ���� �� �ִ� �迭 
    int n = 0;
    char BUFFER[100]; //����100�� string ������(�迭)

    while(n < 4 && scanf("%s", BUFFER) != EOF){
        words[n] = strdup(BUFFER); //BUFFER string���� ������ ���ο� �޸𸮿����� �ּҰ��� ����
        n++;
    }

    for (int i=0; i<4; i++)
        printf("%s\n", words[i]);
}