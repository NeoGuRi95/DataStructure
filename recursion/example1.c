#include <stdio.h>

int sub(int n) {
    if (n < 0) return 0;
    return n + sub(n-3);
}

int sub_iter(int n) {
    int answer = 0;
    while (n >= 0) {
        answer += n;
        n -= 3;
    }
    return answer;
}

int main() {
    int answer = sub(50);
    int answer_inter = sub_iter(50);
    printf("%d\n", answer);
    printf("%d", answer_inter);
    return 0;
}