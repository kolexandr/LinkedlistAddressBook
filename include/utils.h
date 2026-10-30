#ifndef UTILS
#define UTILS

#include <stddef.h>

int read_int(int *value);

int read_string(char *buffer, size_t size);

int get_file_path(char *path, size_t size);

#endif