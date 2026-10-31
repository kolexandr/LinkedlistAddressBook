#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

void discard_line(void){
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF);
}

int read_string(char *buffer, size_t size) {

    if (size < 2 || size > INT_MAX){
        return 1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL){
        return 1;
    }


    char *newline;
    newline = strchr(buffer, '\n');
    buffer[strcspn(buffer, "\n")] = '\0';
    if (buffer[0] == '\0') return 1;


    if (newline != NULL){
        *newline = '\0';
    } else {
        int next_char = getchar();
        if (next_char != '\n' && next_char != EOF){
            discard_line();
            return 1;
        }

        if (next_char == EOF && ferror(stdin)){
            return 1;
        }
    }

    for (int i = 0; buffer[i] != '\0'; i++){
        if (isspace((unsigned char) buffer[i])){
            return 1;
        }
    }


    return 0;
}

int read_int(int *value) {
    char buffer[100];


    if (fgets(buffer, sizeof(buffer), stdin) == NULL){
        return 1;
    }

    errno = 0;
    char *end;
    long number = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE){
        return 1;
    }
    while (isspace((unsigned char)*end)){
        end++;
    }
    if (*end != '\0' || number > INT_MAX || number < INT_MIN){
        return 1;
    }
    *value = (int)number;
    return 0;
}

int get_file_path(char *path, size_t size){
    char *home = getenv("HOME");

    if (home == NULL){
        printf("Unable to find home directory\n");
        return 1;
    }

    snprintf(path, size, "%s/addresses.csv", home);
    return 0;
}