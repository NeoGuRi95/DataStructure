#include <stdio.h>

int main(void){
    int x=1, y=2;
    int *ip;
    ip = &x;

    printf("ip ������ ������ �� �ִ� �ּҰ�: %d\n", ip);
    printf("x ������ �ּҰ�: %d\n", &x);
    printf("ip ������ ���� ��ü�� �ּҰ�: %d\n", &ip);
    printf("ip ������ ������ ����Ű�� �ּҿ� �� �ִ� ��: %d\n", *ip);

    y = *ip;
    printf("y ������: %d\n", y);

    *ip = 0;
    printf("x ������: %d", x);
}