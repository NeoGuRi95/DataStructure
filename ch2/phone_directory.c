#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

void add();

int main()
{
    char command[BUFFER_SIZE];
 
    while (1) {
        printf("$ ");
        scanf("%s", command);
;
        if (strcmp(command, "add") == 0)
            add();
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
    ++n;

    printf("%s was added successfully.\n", name);
}