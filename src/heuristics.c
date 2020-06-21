#include <stdio.h>
#include <math.h>
#include "stuff.h"

int heur_hamming(int *brasl, t_desc *desc)
{
    // print_puzzle(desc->sol, desc->n);
    int dist = 0;
    for (int i = 0; i < desc->n * desc->n; i++)
    {
        if (brasl[i] != desc->sol[i])
            dist += 1;
    }
    // printf("dist by position is %d\n", dist);
    // print_puzzle(brasl, desc->n);
    return dist;
}

// count Manhattan distanse
int heur_manhatt(int *brasl, t_desc *desc)
{
    // print_puzzle(brasl, desc->n);
    // i - finish index
    int nxn = desc->n * desc->n;
    int dx = 0, dy = 0;
    int num = -1, dist = 0;
    for (int i = 0; i < nxn; i++)
    {
        num = desc->sol[i];
        int j = 0;
        for (; j < nxn; j++)
        {
            if (brasl[j] == num)
                break;
        }
        dx = abs(i % desc->n - j % desc->n);
        dy = abs(i / desc->n - j / desc->n);
        dist += dx + dy;
        // printf("dist for '%d' is %d(%d + %d)\n", num, dx + dy, dx, dy);
    }
    // printf("\n");
    return dist;
}

int heur_petryshyn(int *brasl, t_desc *desc) // needs to be implemented
{
    int nxn = desc->n * desc->n;
    int dx = 0, dy = 0;
    int num = -1, dist = 0;
    for (int i = 0; i < nxn; i++)
    {
        num = desc->sol[i];
        int j = 0;
        for (; j < nxn; j++)
        {
            if (brasl[j] == num)
                break;
        }
        dx = abs(i % desc->n - j % desc->n);
        dy = abs(i / desc->n - j / desc->n);
        dist += dx + dy;
        // printf("dist for '%d' is %d(%d + %d)\n", num, dx + dy, dx, dy);
    }

    return dist > 1 ? dist * 2 : dist;
}

int heur_euclidean(int *brasl, t_desc *desc)
{
    int nxn = desc->n * desc->n;
    int dx = 0, dy = 0;
    int num = -1, dist = 0;
    for (int i = 0; i < nxn; i++)
    {
        num = desc->sol[i];
        int j = 0;
        for (; j < nxn; j++)
        {
            if (brasl[j] == num)
                break;
        }
        dx = abs(i % desc->n - j % desc->n);
        dy = abs(i / desc->n - j / desc->n);
        dist += sqrt(dx * dx + dy * dy);
        // printf("dist for '%d' is %d(%d + %d)\n", num, dx + dy, dx, dy);
    }
    return dist;
}

