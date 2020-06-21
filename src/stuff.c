#include <stdio.h>
#include <stdlib.h>
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
    for (int i = 0; i < hwc + 1; i++)
        closed[i] = NULL;
}

int count_worst_case(int n)
{
    int count = 0;
    for (; n >= 2; n -= 2)
        count += 4 * n * (n - 1);
    return count;
}

void print_pass(t_list *list, t_desc *desc)
{
    int moves = -1;
    while (list)
    {
        printf("\n");
        print_puzzle(list->brasl, desc->n);
        list = list->parent;
        moves++;
    }
    printf("Complexity in time: %d\n", desc->tcompl);
    printf("Complexity in size: %d\n", desc->scompl);
    printf("Number of moves: %d\n", moves);
}

void free_opened(t_set *opened)
{
    if (!opened || !opened->front)
        return;

    t_list *temp = NULL;
    t_list *list = opened->front;
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->brasl);
        free(temp);
    }
    free(opened);
}

void free_closed(t_clos **closed, t_desc *desc)
{
    for (int i = 0; i <= desc->hwc; i++)
    {
        t_clos *clos = closed[i];
        t_clos *temp = NULL;
        while (clos)
        {
            temp = clos;
            clos = clos->next;
            if (temp->node->brasl)
                free(temp->node->brasl);
            if (temp->node)
                free(temp->node);
            if (temp)
                free(temp);
        }
    }
}

void free_traces(t_list *e, t_set *opened, t_clos **closed, t_desc *desc)
{
    free(e->brasl);
    free(e);
    free_opened(opened);
    free_closed(closed, desc);
    free(desc->sol);
}
