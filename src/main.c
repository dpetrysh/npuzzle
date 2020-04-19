#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heuristics.h"
#include "stuff.h"
#include "validity.h"
#include "queueprio.h"
#include "custom_error.h"

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

int main(int ac, char **av)
{
    t_desc desc;
    desc.n = 3;
    desc.sol = snail_solution(desc.n);
    desc.hwc = count_worst_case(desc.n);
    desc.heur = heur_manhatt;
    int brasl[] = {1, 8, 9, 2, 6, 5, 4, 7, 3};
    // int brasl1[] = {1, 12, 3, 14, 11, 8, 15, 9, 6, 16, 7, 5, 4, 2, 13, 10};
    // int brasl2[] = {2, 3, 12, 14, 11, 8, 15, 9, 6, 10, 7, 5, 4, 1, 16, 13};
    // int brasl3[] = {2, 3, 12, 14, 11, 8, 15, 9, 6, 10, 7, 5, 1, 4, 16, 13};
    // int brasl4[] = {1, 3, 12, 11, 14, 8, 15, 9, 6, 10, 7, 5, 2, 4, 16, 13};
    // int brasl5[] = {1, 3, 12, 11, 2, 8, 15, 9, 6, 10, 7, 5, 14, 4, 16, 13};

    // int sol[] = {1, 2, 3, 8, 9, 4, 7, 6, 5};
    // int sol[] = {1, 2, 3, 4, 12, 13, 14, 5, 11, 16, 15, 6, 10, 9, 8, 7};
    printf("The puzlle is solvable = %d\n", puzzle_is_solvable(brasl, &desc));

    // int brasl1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int brasl2[] = {1, 2, 3, 6, 5, 4, 7, 8, 9};
    // int brasl3[] = {1, 2, 3, 6, 9, 4, 7, 5, 8};

    t_set *opened = (t_set *)malloc(sizeof(t_set));
    opened->front = NULL;
    // enqueue(desc.sol, &desc, NULL, opened, desc.heur);
    // enqueue(brasl4, &desc, NULL, opened, desc.heur);
    // enqueue(brasl3, &desc, NULL, opened, desc.heur);
    // enqueue(brasl1, &desc, NULL, opened, desc.heur);
    // enqueue(brasl5, &desc, NULL, opened, desc.heur);

    t_clos *closed[desc.hwc + 1];
    set_closed_null(closed, desc.hwc);

    // bool finish = false;
    // t_list *e;
    // while (opened->front && !finish)
    // {
    //     e = dequeue_first(opened);
    //     if (e->h == 0)
    //         finish = true;
    //     else
    //     {
    //         enqueue_closed(e, closed, &desc);
    //         // print_listway(closed->front, closed->front->n);
    //         // print_puzzle(e->brasl, e->n);
    //         expand_state(e, opened, closed, &heur_manhatt);

    //     }
    // }
 
    // print_pass(e);

    return 0;
}

















    // printf("wc = %d", count_worst_case(3));
    // printf("wc = %d", count_worst_case(4));
    // printf("wc = %d", count_worst_case(5));
    // printf("wc = %d", count_worst_case(6));