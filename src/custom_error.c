#include <stdio.h>

void *custom_error(char *str)
{
    printf("%s\n", str);
    return NULL;
}

int int_cust_error(char *str)
{
    printf("%s\n", str);
    return 0;
}