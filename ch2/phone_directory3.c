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

    capacity *= 2;
    char ** tmp1 = (char **)malloc(capacity * sizeof(char *));
    char ** tmp2 = (char **)malloc(capacity * sizeof(char *));

    for (i = 0; i < n; i++) {
        tmp1[i] = names[i];
        tmp2[i] = numbers[i];
    }

    free(names);
    free(numbers);

    names = tmp1;
    numbers = tmp2;
}

void add(char *name, char *number) {
    if (n >= capacity) {
        reallocate();
    }
    
    int i = n-1;

    while (i >= 0 && strcmp(names[i], name) > 0) {
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;
    }

    names[i+1] = strdup(name);
    numbers[i+1] = strdup(number);

    n++;
}

void load(char *filename){
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    char *full_filename = strcat(strdup(path), filename);
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

void find(char *name) {
    for (int i = 0; i < n; i++){
        if (strcmp(name, names[i]) == 0) {
            printf("%s\n", numbers[i]);
            return;
        } 
    }
    printf("No person named '%s' exists.\n", name);
}

// retuns -1 if not exists
int search(char *name) {
    for (int i = 0; i < n; i++){
        if (strcmp(names[i], name) == 0)
            return i;
    }
    return -1;
}

void remove(char *name) {
    int index = search(name);

    if (index == -1) {
        printf("No person named '%s' exists.\n", name);
        return;
    }
    else {
        for (; index < n; index++) {
            names[index] = names[index+1];
            numbers[index] = numbers[index+1];
        }
        n--;
        printf("'%s' was deleted successfully.\n", name);
    }
}

void status() {
    for (int i = 0; i < n; i++) {
        printf("%s %s\n", names[i], numbers[i]);
    }
    printf("Total %d persons.\n", n);
}

void save(char *filename) {
    char *full_filename = strcat(strdup(path), filename);
    FILE *fp = fopen(full_filename, "w");

    if (fp == NULL) {
        printf("Open failed.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s %s\n", names[i], numbers[i]);
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
            argument1 = strtok(NULL, delim);

            if (argument1 == NULL) {
                printf("File name required.\n");
                continue;
            }

            load(argument1);
        }
        else if (strcmp(command, "add") == 0) {         // 기능2: add
            argument1 = strtok(NULL, delim);
            argument2 = strtok(NULL, delim);

            if (argument1 == NULL || argument2 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }

            add(argument1, argument2);

            printf("%s was added successfully.\n", argument1);
        }
        else if (strcmp(command, "find") == 0) {        // 기능3: find
            argument1 = strtok(NULL, delim);

            if (argument1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }

            find(argument1);
        }
        else if (strcmp(command, "status") == 0) {      // 기능4: status
            status();
        }
        else if (strcmp(command, "delete") == 0) {      // 기능5: delete
            argument1 = strtok(NULL, delim);

            if (argument1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }

            remove(argument1);
        }
        else if (strcmp(command, "save") == 0) {        // 기능6: save
            argument1 = strtok(NULL, delim);
            argument2 = strtok(NULL, delim);

            if (argument1 == NULL || strcmp(argument1, "as") != 0) {
                printf("Invalid command format.\n");
                continue;
            }

            save(argument2);
        }
        else if (strcmp(command, "exit") == 0) {        // 기능7: exit
            break;
        }
    }
}

int main() {

    init_directory();
    process_command();

    return 0;
}