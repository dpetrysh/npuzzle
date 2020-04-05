#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_error.h"
#include "queueprio.h"
#include "heuristics.h"
#include "stuff.h"

void	enqueue(int *brasl, t_desc *desc, t_list *parent, t_set *set, int (*heur)(int *, t_desc *desc))
{
	t_list	*temp = (t_list *)malloc(sizeof(t_list));    
    if (!temp)
    {
        custom_error("malloc've crushed while enqueing");
        return;
    }

    temp->g = 0;
    if (parent)
    {
        temp->parent = parent;
        temp->g = parent->g + 1;
    }
    temp->h = heur(brasl, desc);
    temp->fval = temp->h + temp->g;
	temp->brasl = brasl;
	temp->next = NULL;
	if (!set->front/* && !set->rear*/)
	{
		set->front = temp;
		// set->rear = temp;
		return;
	}
    /* This is special case when we need to paste new element at the beginning of the list */
    t_list *prev = set->front;
    if (temp->fval < prev->fval)
    {
        temp->next = prev;
        set->front = temp;
        return;
    }
    else if (!prev->next) /* if we have only 1 element with fval < temp->fval */
    {
        prev->next = temp;
        return;
    }
    /* More commmon case when we need to put new element somewhere between edjes of the list */
    t_list *curr = prev->next;
    while (curr)
    {
        if (temp->fval < curr->fval)
        {
            prev->next = temp;
            temp->next = curr;
            return;
        }
        prev = prev->next;
        curr=curr->next;
    }
    prev->next = temp;
}

// void	enqueue_closed(t_list *list, t_set *set)
// {
// 	if (!set->front && !set->rear)
// 	{
//         list->prev = NULL;
// 		set->front = list;
// 		set->rear = list;
// 		return;
// 	}
//     list->prev = set->rear;
// 	set->rear->next = list;
// 	set->rear = list;
// }

// t_list	*dequeue(t_set *set) //ready
// {
// 	if (!set->front)
// 		return NULL;
// 	t_list *curr = set->front;
//     curr->prev = NULL;

// 	if (set->front == set->rear)
// 	{
// 		set->front = NULL;
// 		set->rear = NULL;
//         return curr;
// 	}
// 	else
//     {
//         t_list *selected = curr;
//         t_list *tmp;
//         int fval = curr->fval;
//         while (curr)
//         {
//             if (curr->fval < fval)
//             {
//                 fval = curr->fval;
//                 selected = curr;
//             }
//             tmp = curr;
//             curr = curr->next;
//             if (curr)
//                 curr->prev = tmp;
//         }
//         if (selected == set->front)
//         {
//             set->front = set->front->next;
//         }
//         else if (selected == set->rear)
//         {
//             set->rear = set->rear->prev;
//         }
//         else
//         {
//             t_list *prev = selected->prev;
//             t_list *next = selected->next;
//             prev->next = next;
//             next->prev = prev;
//         }
//         return selected;
//     }
// }

// static void trade_nodes(int *brasl, int from, int to)
// {
//     int tmp = brasl[from];
//     brasl[from] = brasl[to];
//     brasl[to] = tmp;
// }

// static int braslets_is_equal(int *first, int *second, int n)
// {
//     for (int i = 0; i < n * n; i++)
//     {
//         if (first[i] != second[i])
//             return 0;
//     }

//     return 1;
// }

// static int brasl_already_inside(int *brasl, t_set *set, int n) // 0 if not inside
// {
//     t_list *tmp = set->front;
//     while (tmp)
//     {
//         if (braslets_is_equal(brasl, tmp->brasl,  n))
//             return 1;
//         tmp = tmp->next;
//     }

//     return 0;
// }

// void add_if_nice(int *tmp_br, t_list *list, t_set *opened, t_set *closed, int (*heur)(int *, int))
// {
//     if (!brasl_already_inside(tmp_br, opened, list->n) && !brasl_already_inside(tmp_br, closed, list->n))
//     {
//         int *new_brasl = (int *)malloc(sizeof(int) * list->n * list->n);
//         for (int i = 0; i < list->n * list->n; i++)
//             new_brasl[i] = tmp_br[i];
//         enqueue(new_brasl, list->n, list, opened, heur);
//     }
// }

// void copy_brasl(int *to, int *from, int nxn)
// {
//     for (int i = 0; i < nxn; i++)
//         to[i] = from[i];
// }

// void expand_state(t_list *list, t_set *opened, t_set *closed, int (*heur)(int *, int))
// {
//     int nxn = list->n * list->n;
//     int npos = 0; // index of null node
//     for (int i = 0; i < nxn; i++)
//     {
//         if (list->brasl[i] == nxn)
//             npos = i;
//     }
//     // printf("%d\n", npos);

//     int tmp_br[nxn];
//     memset(tmp_br, 0, nxn * sizeof(int));
//     copy_brasl(tmp_br, list->brasl, nxn);
//     if (npos + list->n < nxn)
//     {
//         trade_nodes(tmp_br, npos, npos + list->n);
//         add_if_nice(tmp_br, list, opened, closed, heur);
//     }

//     copy_brasl(tmp_br, list->brasl, nxn);
//     if (npos - list->n >= 0)
//     {
//         trade_nodes(tmp_br, npos, npos - list->n);
//         add_if_nice(tmp_br, list, opened, closed, heur);
//     }

//     copy_brasl(tmp_br, list->brasl, nxn);
//     if ((npos + 1) % list->n)
//     {
//         trade_nodes(tmp_br, npos, npos + 1);
//         add_if_nice(tmp_br, list, opened, closed, heur);
//     }

//     copy_brasl(tmp_br, list->brasl, nxn);
//     if (npos % list->n)
//     {
//         trade_nodes(tmp_br, npos, npos - 1);
//         add_if_nice(tmp_br, list, opened, closed, heur);
//     }
// }