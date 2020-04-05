#include <stdio.h>

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

int puzzle_is_solvable(int *brasl, int n)
{
    printf("width is even: %d\n inversions_is_odd: %d\n blank_on_odd_row: %d\n",
            !width_is_odd(n), inversions_is_odd(brasl, n), blank_on_odd_row(brasl, n));
    
    return ((width_is_odd(n)) && !inversions_is_odd(brasl, n)) ||
            (!width_is_odd(n) && (blank_on_odd_row(brasl, n) == !inversions_is_odd(brasl, n)));
}
