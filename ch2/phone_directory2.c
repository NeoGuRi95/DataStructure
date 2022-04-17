#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

void load() {
    //char filename[BUFFER_SIZE];
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    //scanf("%s", filename);

    //FILE *fp = fopen(filename, "r");
    FILE *fp = fopen("C:\\Users\\jea5158\\Desktop\\DataStructure\\ch2\\directory.txt", "r");
    if (fp == NULL) {
        printf("Open failed.\n");
        return;
    }

    while (fscanf(fp, "%s", buf1) != EOF) {
        fscanf(fp, "%s", buf2);
        names[n] = strdup(buf1);
        numbers[n] = strdup(buf2);
        n++;
    }
    fclose(fp);
}

void save() {
    char filename[BUFFER_SIZE];
    char tmp[BUFFER_SIZE];

    scanf("%s", tmp); //'as' is discarded
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Open failed.\n");
        return;
    }

    for (int i = 0; i < n; i++){
        fprintf(fp, "%s %s", names[i], numbers[i]);
    }

    fclose(fp);
}

void add() {
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    scanf("%s", buf1);
    scanf("%s", buf2);

    int i = n-1;
    while ((i >= 0) && (strcmp(names[i], buf1) > 0)) {
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;    
    }
    names[i+1] = strdup(buf1);
    numbers[i+1] = strdup(buf2);

    n++;
    printf("%s was added successfully.\n", buf1);
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
        printf("%s %s\n", names[i], numbers[i]);
    }
    printf("Total %d persons.\n", n);
}

// retuns -1 if not exists
int search(char *name) {
    for (int i = 0; i < n; i++){
        if (strcmp(names[i], name) == 0)
            return i;
    }
    return -1;
}

void remove() {
    char buf[BUFFER_SIZE];

    scanf("%s", buf);

    int index = search(buf);

    if (index != -1){
        while (index < n) {
            names[index] = names[index+1];
            numbers[index] = numbers[index+1];
            index++;
        }
        n--;
        printf("'%s' was deleted successfully.\n", buf);
    }
    else
        printf("No person named '%s' exists.\n", buf);
}

int main()
{
    char command[BUFFER_SIZE];
 
    while (1) {
        printf("$ ");
        scanf("%s", command);

        if (strcmp(command, "read") == 0)
            load();
        else if (strcmp(command, "save") == 0)
            save();
        else if (strcmp(command, "add") == 0)
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