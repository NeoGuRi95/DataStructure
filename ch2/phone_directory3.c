#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3     /* �迭 ���Ҵ��� �׽�Ʈ�ϱ� ���ؼ� �Ϻη� ���� ���� ������ */
#define BUFFER_SIZE 50

char ** names;     // char * Ÿ���� �迭�� �̸��̹Ƿ� char ** Ÿ���� �����̴�.
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