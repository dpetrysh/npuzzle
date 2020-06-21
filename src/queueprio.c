#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "custom_error.h"
#include "queueprio.h"
#include "heuristics.h"
#include "stuff.h"

t_list *get_new_node(int *brasl, t_desc *desc, t_list *parent, t_set *set)
{
    t_list *new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return custom_error("malloc've crushed while enqueing");
    memset(new, 0, sizeof(t_list));
    desc->scompl++;

    new->g = 0;
    if (parent)
    {
        new->parent = parent;
        new->g = parent->g + 1;
    }
    new->h = desc->heur(brasl, desc);
    new->fval = new->h + new->g;
    new->brasl = brasl;
    new->next = NULL;
    return new;
}

void	enqueue(int *brasl, t_desc *desc, t_list *parent, t_set *set)
{
    static int u = 0;
    int sho = (++u == 100) ? write(1, "\n", 1) : write(1, ".", 1);
    if (u == 100)
        u = 0;

    t_list *new = get_new_node(brasl, desc, parent, set);

    if (!set->front)
    {
        set->front = new;
        return;
    }
    /* This is special case when we need to paste new element at the beginning of the list */
    t_list *prev = set->front;
    if (new->fval < prev->fval)
    {
        new->next = prev;
        set->front = new;
        return;
    }
    /* if we have only 1 element with fval < new->fval */
    else if (!prev->next)
    {
        prev->next = new;
        return;
    }
    /* More commmon case when we need to put new element somewhere between edjes of the list */
    t_list *curr = prev->next;
    while (curr)
    {
        if (new->fval < curr->fval)
        {
            prev->next = new;
            new->next = curr;
            return;
        }
        prev = prev->next;
        curr=curr->next;
    }
    prev->next = new;
}

t_list *dequeue_first(t_set *set)
{
    t_list *ret;
    ret = set->front;
    if (ret)
        set->front = ret->next;
    return ret;
}

t_clos *get_closed_node(t_list *list)
{
    t_clos *clos = (t_clos *)malloc(sizeof(t_clos));
    if (!clos)
        return custom_error("No enought memory for malloc in get_closed_node()\n");
    memset(clos, 0, sizeof(t_clos));

    clos->node  = list;
    clos->next = NULL;

    return clos;
}

void enqueue_closed(t_list *list, t_clos **clset, t_desc *desc)
{
    t_clos *clos = get_closed_node(list);

    int h = heur_manhatt(list->brasl, desc);

    if (clset[h])
    {
        clos->next = clset[h];
        clset[h] = clos;
    }
    else
    {
        clset[h] = clos;
    }
}

static void trade_nodes(int *brasl, int from, int to)
{
    int tmp = brasl[from];
    brasl[from] = brasl[to];
    brasl[to] = tmp;
}

static int braslets_is_equal(int *first, int *second, int n)
{
    for (int i = 0; i < n * n; i++)
    {
        if (first[i] != second[i])
            return 0;
    }

    return 1;
}

static int brasl_already_inside_open(int *brasl, t_set *set, t_desc *desc) // 0 if not inside
{
    t_list *tmp = set->front;
    int brasl_heur = desc->heur(brasl, desc);
    while (tmp)
    {
        if (brasl_heur == tmp->h)
        {
            if (braslets_is_equal(brasl, tmp->brasl, desc->n))
                return 1;
        }
        tmp = tmp->next;
    }

    return 0;
}

static int brasl_already_inside_clos(int *brasl, t_clos **clos, t_desc *desc) // 0 if not inside
{
    int ind = heur_manhatt(brasl, desc);
    int brasl_heur = desc->heur(brasl, desc);
    t_clos *tmp = clos[ind];
    while (tmp)
    {
        if (brasl_heur == tmp->node->h)
        {
            if (braslets_is_equal(tmp->node->brasl, brasl, desc->n))
                return 1;
        }
        tmp = tmp->next;
    }

    return 0;
}

static void add_if_nice(int *tmp_br, t_list *list, t_set *opened, t_clos **closed, t_desc *desc)
{
    if (!brasl_already_inside_open(tmp_br, opened, desc) &&
        !brasl_already_inside_clos(tmp_br, closed, desc))
    {
        int *new_brasl = (int *)malloc(sizeof(int) * desc->n * desc->n);
        for (int i = 0; i < desc->n * desc->n; i++)
            new_brasl[i] = tmp_br[i];
        enqueue(new_brasl, desc, list, opened);
    }
}

static void copy_brasl(int *to, int *from, int nxn)
{
    for (int i = 0; i < nxn; i++)
        to[i] = from[i];
}

void expand_state(t_list *list, t_set *opened, t_clos **closed, t_desc *desc)
{
    int nxn = desc->n * desc->n;
    int npos = 0; // index of null node
    for (int i = 0; i < nxn; i++)
    {
        if (list->brasl[i] == nxn)
            npos = i;
    }

    int tmp_br[nxn];
    memset(tmp_br, 0, nxn * sizeof(int));
    copy_brasl(tmp_br, list->brasl, nxn);
    if (npos + desc->n < nxn)
    {
        trade_nodes(tmp_br, npos, npos + desc->n);
        add_if_nice(tmp_br, list, opened, closed, desc);
    }

    copy_brasl(tmp_br, list->brasl, nxn);
    if (npos - desc->n >= 0)
    {
        trade_nodes(tmp_br, npos, npos - desc->n);
        add_if_nice(tmp_br, list, opened, closed, desc);
    }

    copy_brasl(tmp_br, list->brasl, nxn);
    if ((npos + 1) % desc->n)
    {
        trade_nodes(tmp_br, npos, npos + 1);
        add_if_nice(tmp_br, list, opened, closed, desc);
    }

    copy_brasl(tmp_br, list->brasl, nxn);
    if (npos % desc->n)
    {
        trade_nodes(tmp_br, npos, npos - 1);
        add_if_nice(tmp_br, list, opened, closed, desc);
    }
}