#ifndef UTILS
#define UTILS

#include <stddef.h>

/* Returns 0 on success, 1 on invalid size, overlong input, EOF, or read error.
 * Empty lines are valid; the terminating newline is removed. */
int read_line(char *buffer, size_t size);

int read_int(int *value);

int read_string(char *buffer, size_t size);

int get_file_path(char *path, size_t size);

#endif
