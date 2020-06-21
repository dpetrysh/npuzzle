#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heuristics.h"
#include "stuff.h"
#include "validity.h"
#include "queueprio.h"
#include "custom_error.h"
#include "parcer.h"

int *snail_solution(int n) //don't forget to free memory
{
    int nxn = n * n;
    int *solution = (int *)malloc(sizeof(int)*nxn);
    if (!solution)
        return custom_error("Sorry, I don't have enough memory for solution");

    memset(solution, 0, sizeof(int)*nxn);
    int col = 0, row = 0, minCol = 0, minRow = 0;
    int maxCol = n - 1, maxRow = n - 1;
    int val = 1;
    while (val < nxn)
    {
        for (; col < maxCol; col++)
            solution[n*row + col] = val++;
        for (; row < maxRow; row++)
            solution[n*row + col] = val++;
        for (; col > minCol; col--)
            solution[n*row + col] = val++;
        for (; row > minRow; row--)
            solution[n*row + col] = val++;
        maxCol--;
        maxRow--;
        minCol++;
        minRow++;
        col = minCol;
        row = minRow;
    }
    if (n % 2)
        solution[n*row + col] = val;

    return solution;
}

void description(t_desc *desc)
{
    desc->sol = snail_solution(desc->n);
    desc->hwc = count_worst_case(desc->n);
    desc->tcompl = 0;
    desc->scompl = 0;
}

int main(int ac, char **av)
{
    int *brasl;
    t_desc desc;
    brasl = parce_input(ac, av, &desc);
    if (!brasl)
        return 0;

    description(&desc);

    // printf("IS SOLVABLE=%d\n", puzzle_is_solvable(brasl, &desc));
    if (!puzzle_is_solvable(brasl, &desc))
    {
        printf("The puzlle is NOT solvable\n");
        free(desc.sol);
        free(brasl);
        return 0;
    }

    t_set *opened = (t_set *)malloc(sizeof(t_set));
    opened->front = NULL;
    enqueue(brasl, &desc, NULL, opened);

    t_clos *closed[desc.hwc + 1];
    set_closed_null(closed, desc.hwc);

    bool finish = false;
    t_list *e;
    while (opened->front && !finish)
    {
        e = dequeue_first(opened);
        // printf("%d", e->h);
        desc.tcompl++;
        if (e->h == 0)
            finish = true;
        else
        {
            enqueue_closed(e, closed, &desc);
            expand_state(e, opened, closed, &desc);
        }
    }

    print_pass(e, &desc);

    free_traces(e, opened, closed, &desc);

    return 0;
}

















    // printf("wc = %d", count_worst_case(3));
    // printf("wc = %d", count_worst_case(4));
    // printf("wc = %d", count_worst_case(5));
    // printf("wc = %d", count_worst_case(6));