#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

void add();
void find();
void status();
void remove();

int main()
{
    char command[BUFFER_SIZE];
 
    while (1) {
        printf("$ ");
        scanf("%s", command);
;
        if (strcmp(command, "add") == 0)
            add();
        else if (strcmp(command, "find") == 0)
            find();
        else if (strcmp(command, "status") == 0)
            status();
        else if (strcmp(command, "remove") == 0)
            remove();
        else if (strcmp(command, "exit") == 0)
            break;
    }
    return 0;
}

void add() {
    char name[BUFFER_SIZE];
    char number[BUFFER_SIZE];

    scanf("%s", name);
    scanf("%s", number);

    names[n] = strdup(name);
    numbers[n] = strdup(number);
    n++;

    printf("%s was added successfully.\n", name);
}

void find() {
    char buf[BUFFER_SIZE];

    scanf("%s", buf);

    for (int i = 0; i < n; i++){
        if (strcmp(buf, names[i]) == 0) {
            printf("%s\n", numbers[i]);
            return;
        } 
    }
    printf("No person named '%s' exists.\n", buf);
}

void status() {
    for (int i = 0; i < n; i++) {
        printf("%s ", names[i]);
        printf("%s\n", numbers[i]);
    }
    printf("Total %d persons.\n", &n);
}

void remove() {
    char buf[BUFFER_SIZE];

    scanf("%s", buf);

    for (int i = 0; i < n; i++) {
        if (strcmp(buf, names[i]) == 0){
            names[i] = names[n-1];
            numbers[i] = numbers[n-1];
            n--;
            printf("'%s' was deleted successfully.\n", buf);
            return;
        }
    }
    printf("No person named '%s' exists.\n", buf);
}