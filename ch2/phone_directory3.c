#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3     /* 배열 재할당을 테스트하기 위해서 일부러 아주 작은 값으로 */
#define BUFFER_SIZE 50

char ** names;     // char * 타입의 배열의 이름이므로 char ** 타입의 변수이다.
char ** numbers;

int capacity = INIT_CAPACITY;     /* size of arrays */
int n = 0;                        /* number of people in phone directory */

char delim[] = " ";

void init_directory() {
    names = (char **)malloc(INIT_CAPACITY * sizeof(char *));
    numbers = (char **)malloc(INIT_CAPACITY * sizeof(char *));
}

int read_line(char str[], int limit) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (i < limit - 1)
            str[i++] = ch;
    }

    str[i] = '\0';

    return i;
}

int main() {

    init_directory();
    process_command();

    return 0;
}