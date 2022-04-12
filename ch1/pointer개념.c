#include <stdio.h>

int main(void){
    int x=1, y=2;
    int *ip;
    ip = &x;

    printf("ip 포인터 변수에 들어가 있는 주소값: %d\n", ip);
    printf("x 변수의 주소값: %d\n", &x);
    printf("ip 포인터 변수 자체의 주소값: %d\n", &ip);
    printf("ip 포인터 변수가 가리키는 주소에 들어가 있는 값: %d\n", *ip);

    y = *ip;
    printf("y 변수값: %d\n", y);

    *ip = 0;
    printf("x 변수값: %d", x);
}