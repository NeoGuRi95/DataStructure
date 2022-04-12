#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 20

int main()
{
    char buffer[BUFFER_SIZE];
    int k;
    while (1)
    {
        printf("$ ");
        k = read_line(buffer, BUFFER_SIZE);
        printf("%s¿« ±Ê¿Ã:%d\n", buffer, k);
        
        for (int i=0; i<k; i++){
            buffer[i++] = NULL;
        }
    }
    return 0;
}

int read_line(char str[], int limit){
    int ch, i = 0;
    while((ch = getchar()) != '\n'){
        if (i < limit)
            str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}