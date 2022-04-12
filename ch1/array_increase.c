#include <stdio.h>
#include <stdlib.h>
//동적으로 할당된 배열은 공간이 부족할 경우 더 큰 배열을 할당하여 사용할 수 있다.
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
        printf("array의 %d번째 주소: %d, 값: %d\n", i, (array + i), *(array + i));
    }

    return 0;
}