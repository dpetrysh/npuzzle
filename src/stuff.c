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

void set_closed_null(t_clos **closed, int hwc)
{
    for (int i = 0; i < hwc; i++)
        closed[i] = NULL;
}

int count_worst_case(int n)
{
    int count = 0;
    for (; n >= 2; n -= 2)
        count += 4 * n * (n - 1);
    return count;
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
