#include <stdio.h>
#include "stuff.h"

int abs(int num)
{
    return num > 0 ? num : -num;
}

void print_puzzle(int *brasl, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", brasl[i * n + j] == n * n ? 0 : brasl[i * n + j]);
        
        printf("\n");
    }
}

void print_listway(t_list *list, int n)
{
    printf("______\n");
    while (list)
    {
        print_puzzle(list->brasl, n);
        printf("\n");
        list = list->next;
    }
    printf("------\n");
}

// void print_pass(t_list *list)
// {
//     while (list)
//     {
//         print_puzzle(list->brasl, list->n);
//         printf("\n");
//         list = list->parent;
//     }
// }
