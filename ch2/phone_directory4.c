#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 100

typedef struct person
{
    char *name;
    char *number;
    char *email;
    char *group;
} Person;

Person directory[CAPACITY];
int n = 0;          /* number of people in phone directory */
char delim[] = " ";
char path[50] = "C:\\Users\\jea5158\\Desktop\\DataStructure\\ch2\\";

int read_line(FILE *fp, char str[], int limit) { //read_line을 수정하여 키보드만이 아니라 파일로부터도 읽을 수 있도록 하였다.
    int ch, i = 0;

    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        if (i < limit - 1)
            str[i++] = ch;
    }

    str[i] = '\0';
    return i;
}

int compose_name(char str[], int limit) {
    char *ptr;
    int length = 0;

    ptr = strtok(NULL, delim);
    if (ptr == NULL)
        return 0;

    strcpy(str, ptr);
    length += strlen(ptr);

    ptr = strtok(NULL, delim);
    while (ptr != NULL) {
        if (length + strlen(str) + 1 < limit) {
            str[length++] = ' ';
            str[length] = '\0';
            strcat(str, ptr);
            length += strlen(ptr);
        }
    }
    return length;
}

void add(char *name, char *number, char *email, char *group) { 
    int i = n-1;

    while (i >= 0 && strcmp(directory[i].name, name) > 0) {
        directory[i+1] = directory[i];
        i--;
    }

    directory[i+1].name = strdup(name);
    directory[i+1].number = strdup(number);
    directory[i+1].email = strdup(email);
    directory[i+1].group = strdup(group);

    n++;
}

void handle_add(char *name) {
    char number[BUFFER_SIZE], email[BUFFER_SIZE], group[BUFFER_SIZE];
    char empty[] = " ";

    printf("    Phone: ");
    read_line(stdin, number, BUFFER_SIZE);

    printf("    Email: ");
    read_line(stdin, email, BUFFER_SIZE);

    printf("    Group: ");
    read_line(stdin, group, BUFFER_SIZE); 

    add(name, (char *)strlen(number)>0? number : empty
            , (char *)strlen(email)>0? email : empty
            , (char *)strlen(group)>0? group : empty);
}

void load(char *filename){
    char buffer[BUFFER_SIZE];
    char *name, *number, *email, *group;
    char *full_filename = strcat(strdup(path), filename);
    FILE *fp = fopen(full_filename, "r");

    if (fp == NULL) {
        printf("Open failed.\n");
        return;
    }

    while (1) {
        if (read_line(fp, buffer, BUFFER_SIZE) <= 0)
            break;
        name = strtok(buffer, "#");
        number = strtok(NULL, "#");
        email = strtok(NULL, "#");
        group = strtok(NULL, "#");
        add(name, number, email, group);
    }
    fclose(fp);
}

void find(char *name) {
    for (int i = 0; i < n; i++){
        if (strcmp(directory[i].name, name) == 0) {
            printf("Number: %s\n", directory[i].number);
            printf("Email: %s\n", directory[i].email);
            printf("Group: %s\n", directory[i].group);
            return;
        } 
    }
    printf("No person named '%s' exists.\n", name);
}

// retuns -1 if not exists
int search(char *name) {
    for (int i = 0; i < n; i++){
        if (strcmp(directory[i].name, name) == 0)
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
            directory[index] = directory[index+1];
        }
        n--;
        printf("'%s' was deleted successfully.\n", name);
    }
}

void status() {
    for (int i = 0; i < n; i++) {
        printf("name: %s\n", directory[i].name);
        printf("number: %s\n", directory[i].number);
        printf("email: %s\n", directory[i].email);
        printf("group: %s\n", directory[i].group);
        printf("----------------\n");
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
        fprintf(fp, "%s#", directory[i].name);
        fprintf(fp, "%s#", directory[i].number);
        fprintf(fp, "%s#", directory[i].email);
        fprintf(fp, "%s#", directory[i].group);
    }

    fclose(fp);
}

void process_command() {
    char command_line[BUFFER_SIZE];
    char *command, *argument;
    char name_str[BUFFER_SIZE];

    while (1) {
        printf("$ ");

        if (read_line(stdin, command_line, BUFFER_SIZE) <= 0)
            continue;

        command = strtok(command_line, " ");

        if (strcmp(command, "read") == 0) {             // 기능1: read
            argument = strtok(NULL, delim);

            if (argument == NULL) {
                printf("File name required.\n");
                continue;
            }

            load(argument);
        }
        else if (strcmp(command, "add") == 0) {         // 기능2: add

            if (compose_name(name_str, BUFFER_SIZE) == 0) {
                printf("Invalid command format.\n");
                continue;
            }

            handle_add(name_str);
            printf("%s was added successfully.\n", name_str);
        }
        else if (strcmp(command, "find") == 0) {        // 기능3: find
            
            if (compose_name(name_str, BUFFER_SIZE) == 0) {
                printf("Invalid command format.\n");
                continue;
            }

            find(argument);
        }
        else if (strcmp(command, "status") == 0) {      // 기능4: status
            status();
        }
        else if (strcmp(command, "delete") == 0) {      // 기능5: delete
            if (compose_name(name_str, BUFFER_SIZE) == 0) {
                printf("Invalid command format.\n");
                continue;
            }

            remove(name_str);
        }
        else if (strcmp(command, "save") == 0) {        // 기능6: save
            argument = strtok(NULL, delim);
            if (strcmp(argument, "as") != 0) {
                printf("Invalid command format.\n");
                continue;
            }

            argument = strtok(NULL, delim);
            if (argument == NULL) {
                printf("Invalid command format.\n");
                continue;
            }

            save(argument);
        }
        else if (strcmp(command, "exit") == 0) {        // 기능7: exit
            break;
        }
    }
}

int main() {

    process_command();

    return 0;
}