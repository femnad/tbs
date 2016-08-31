#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define OUGHT_TO_BE_ENOUGH 256

char*
cave_truncate_string(char *wasteful_string, int string_length) {
    char *new_string = malloc(sizeof(char) * string_length);
    char *string_start = new_string;
    for (int i = 0; i < string_length; i++) {
        *new_string = wasteful_string[i];
        new_string++;
    }
    *new_string = '\0';
    return string_start;
}

char*
cave_get_string(char *format_string, ...) {
    char buffer[OUGHT_TO_BE_ENOUGH];
    va_list argp;
    va_start(argp, format_string);
    int string_length = vsprintf(buffer, format_string, argp);
    va_end(argp);
    return cave_truncate_string(buffer, string_length);
}
