#include <stdio.h>
#include <stdlib.h>
//�������� �Ҵ�� �迭�� ������ ������ ��� �� ū �迭�� �Ҵ��Ͽ� ����� �� �ִ�.
int main(void){
    int *array = (int *)malloc(4*sizeof(int));

    for(int i = 0; i < 4; i++){
        *(array + i) = i;
    }

    int *tmp = (int *)malloc(8*sizeof(int));

    for (int i = 0; i < 4; i++){
        tmp[i] = array[i];
    }

    array = tmp;

    for (int i = 0; i < 8; i++){
        printf("array�� %d��° �ּ�: %d, ��: %d\n", i, (array + i), *(array + i));
    }

    return 0;
}