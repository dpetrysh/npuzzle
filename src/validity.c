#include <stdio.h>
#include "validity.h"

static int count_inversions(int *brasl, int n)
{
    int count = 0;
    for (int i = 0; i < n * n; i++)
    {
        for (int j = i + 1; j < n * n; j++)
        {
            if (brasl[j] != n * n && brasl[i] != n * n && brasl[i] > brasl[j])
                count++;
        }
    }
    printf("inversions = %d\n", count);
    return count;
}

static int width_is_odd(int n)
{
    // printf("width is %s\n", n % 2 ? "odd" : "even");
    return n % 2;
}

static int inversions_is_odd(int *brasl, int n)
{
    // printf("width is %s\n", count_inversions(brasl, n) % 2 ? "odd" : "even");
    return count_inversions(brasl, n) % 2;
}

static int blank_on_odd_row(int *brasl, int n)
{
    for (int i = 0; i < n * n; i++)
    {
        if (brasl[i] == n * n)
            return (i / n) % 2;
    }
}

int puzzle_is_solvable(int *brasl, t_desc *desc)
{
    int res = 0;
    int start_oddity = inversions_is_odd(brasl, desc->n);
    int final_oddity = inversions_is_odd(desc->sol, desc->n);
    if (width_is_odd(desc->n))
    {
        if (start_oddity == final_oddity)
            res = 1;
    }
    else
    {
        int start_zero_pos = blank_on_odd_row(brasl, desc->n);
        int final_zero_pos = blank_on_odd_row(desc->sol, desc->n);
        if ((start_oddity == final_oddity && start_zero_pos == final_zero_pos) ||
            (start_oddity != final_oddity && start_zero_pos != final_zero_pos))
            res = 1;
    }
    return res;
}
