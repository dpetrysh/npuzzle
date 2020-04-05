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
    desc.n = 4;
    desc.sol = snail_solution(desc.n);
    int brasl1[] = {1, 12, 3, 14, 11, 8, 15, 9, 6, 16, 7, 5, 4, 2, 13, 10};
    int brasl2[] = {2, 3, 12, 14, 11, 8, 15, 9, 6, 10, 7, 5, 4, 1, 16, 13};
    int brasl3[] = {2, 3, 12, 14, 11, 8, 15, 9, 6, 10, 7, 5, 1, 4, 16, 13};
    int brasl4[] = {1, 3, 12, 11, 14, 8, 15, 9, 6, 10, 7, 5, 2, 4, 16, 13};
    // int brasl1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int brasl2[] = {1, 2, 3, 6, 5, 4, 7, 8, 9};
    // int brasl3[] = {1, 2, 3, 6, 9, 4, 7, 5, 8};

    
    // puzzle_is_solvable(desc.sol, desc.n);
    // print_puzzle(desc.sol, desc.n);

    // heur_manhatt(desc.sol, &desc);
    // heur_manhatt(brasl2, &desc);
    // heur_manhatt(brasl3, &desc);

    t_set *opened = (t_set *)malloc(sizeof(t_set));
    opened->front = NULL;
    enqueue(brasl2, &desc, NULL, opened, &heur_manhatt);
    enqueue(brasl4, &desc, NULL, opened, &heur_manhatt);
    enqueue(brasl3, &desc, NULL, opened, &heur_manhatt);
    enqueue(brasl1, &desc, NULL, opened, &heur_manhatt);
    enqueue(brasl3, &desc, NULL, opened, &heur_manhatt);



    // s_set *closed = (s_set *)malloc(sizeof(s_set));
    // closed->front = NULL;
    // closed->rear = NULL;

    // bool finish = false;
    // t_list *e;
    // while (opened->front && !finish)
    // {
    //     e = dequeue(opened);
    //     if (e->h == 0)
    //         finish = true;
    //     else
    //     {
    //         enqueue_closed(e, closed);
    //         // print_listway(closed->front, closed->front->n);
    //         // print_puzzle(e->brasl, e->n);
    //         expand_state(e, opened, closed, &heur_manhatt_x2);

    //     }
    // }
 
    // print_pass(e);

    return 0;
}
