#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    char str[] = "now # is the time # to start preparing ### for the exam#";
    char delim[] = "#";
    char *token;

    token = strtok(str, delim);
    while (token != NULL) {
        printf("next token is: %s:%d\n", token, strlen(token));
        token = strtok(NULL, delim);
    }

    printf("------------------------\n");

    char str2[] = " study hard, or sleep. ";
    char delim2[] = " ";

    token = strtok(str2, delim2);
    while (token != NULL) {
        printf("next token is: %s:%d\n", token, strlen(token));
        token = strtok(NULL, delim2);
    }

    return 0;

}