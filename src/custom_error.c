#include <stdio.h>

void *custom_error(char *str)
{
    perror(str);
    return NULL;
}