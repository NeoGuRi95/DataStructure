#include <stdio.h>

int main(void){
    int sum, average;
    int num[10];

    for (int i = 0; i < 10; i++){
        scanf("%d", &num[i]);
    }

    sum = calculate_sum(num); 
    average = sum/10;

    printf("평균: %d\n", average);

    return 0;
}
// 배열을 매개변수로 받을 댸 int array[] 대신 이렇게 포인터로 받을 수도 있다.
int calculate_sum(int *array){
    int sum = 0;

    for (int i = 0; i < 10; i++){
        sum = sum + array[i];
    }

    return sum;
}