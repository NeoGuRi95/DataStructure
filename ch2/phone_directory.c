#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

void add();
void find();


int main()
{
    char command[BUFFER_SIZE];
 
    while (1) {
        printf("test$ ");
        scanf("%s", command);
;
        if (strcmp(command, "add") == 0)
            add();
        else if (strcmp(command, "find") == 0)
            find();
        // else if (strcmp(command, "status") == 0)
        //     status();
        // else if (strcmp(command, "remove") == 0)
        //     remove();
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
    char name[BUFFER_SIZE];

    scanf("%s", name);
    printf("test");

    for (int i = 0; i < n; i++){
        if (strcmp(name, names[i]) == 0) {
            printf("%s", numbers[i]);
            return;
        } 
    }
    printf("No person named \'%s\' exists", name);
}