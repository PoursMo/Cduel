#include "utils.h"

char *add_format_to_string(char *string, char *format)
{
    size_t string_len = strlen(string);
    size_t format_len = strlen(format);
    for (size_t i = 0; i < string_len; i++)
        string[i + format_len] = string[i];
    for (size_t i = 0; i < format_len; i++)
        string[i] = format[i];
    size_t reset_len = strlen(RESET);
    size_t i = string_len + format_len;
    for (size_t j = 0; j < reset_len; i++, j++)
        string[i] = RESET[j];
    string[i] = '\0';
    return string;
}

void flush_getchar()
{
    while(getchar() != '\n');
}