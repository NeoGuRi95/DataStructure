#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 4     /* 배열 재할당을 테스트하기 위해서 일부러 아주 작은 값으로 */
#define BUFFER_SIZE 50

char ** names;     // char * 타입의 배열의 이름이므로 char ** 타입의 변수이다.
char ** numbers;

int capacity = INIT_CAPACITY;     /* size of arrays */
int n = 0;                        /* number of people in phone directory */

char delim[] = " ";
char path[50] = "C:\\Users\\jea5158\\Desktop\\DataStructure\\ch2\\";

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

void reallocate() {
    int i;

    char ** tmp1 = (char)
}

void add(char *name, char number) {
    if (n >= capacity) {
        reaallocate();
    }
    
    int i = n-1;

    while (i >= 0 && strcmp(names[i], name) > 0) {
        names[i + 1] = names[i];
        numbers[i + 1] = numbers[i];
        i--;
    }

    names[i] = strdup(name);
    numbers[i] = strdup(number);

    n++;
}

void load(char *filename){
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    char *full_filename = strcat(path, filename);
    FILE *fp = fopen(full_filename, "r");

    if (fp == NULL) {
        printf("Open failed.\n");
        return;
    }

    while (fscanf(fp, "%s", buf1) != EOF) {
        fscanf(fp, "%s", buf2);
        add(buf1, buf2);
    }

    fclose(fp);
}

void process_command() {
    char command_line[BUFFER_SIZE];
    char *command, *argument1, *argument2;

    while (1) {
        printf("$ ");

        if (read_line(command_line, BUFFER_SIZE) <= 0) 
            continue;

        command = strtok(command_line, " ");

        if (strcmp(command, "read") == 0) {             // 기능1: read
            argument1 = strtok(NULL, " ");

            if (argument1 == NULL) {
                printf("File name required.\n");
                continue;
            }

            load(argument1);
        }
    }
}

int main() {

    init_directory();
    process_command();

    return 0;
}