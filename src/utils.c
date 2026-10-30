#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_int(int *value) {
    char buffer[100];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return 1;

    char *end;
    long number = strtol(buffer, &end, 10);

    while (isspace((unsigned char)*end))
        end++;

    if (end == buffer || *end != '\0')
        return 1;

    *value = (int)number;
    return 0;
}


int read_string(char *buffer, size_t size) {

    if (fgets(buffer, size, stdin) == NULL)
        return 1;

    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0')
        return 1;

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