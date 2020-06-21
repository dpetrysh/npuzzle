#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "custom_error.h"
#include "queueprio.h"
#include "heuristics.h"

struct
{
    heur h;
    int (*heur)(int *, struct s_desc *desc);
} static const heuristics_table[] =
{
    {HAMMING, heur_hamming},
    {MANHATTAN, heur_manhatt},
    {EUCLIDEAN, heur_euclidean},
    {PETRYSHYN, heur_petryshyn}
};

static int is_puzzle_line(char *line)
{
    int i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    if (isdigit(line[i]))
        return 1;

    return 0;
}

static int is_comment(char *line)
{
    int i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    if (line[i] == '#')
        return 1;

    return 0;
}

static int is_dimension_line(char *line)
{
    int i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    while (isdigit(line[i]))
        i++;

    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
        i++;

    if (i == 0 || (line[i] != '\0' && line[i] != '#'))
        return 0;

    return 1;
}

static int is_number(char *str)
{
    int i = 0;
    while (str && str[i])
    {
        if (!isdigit(str[i]) && str[i] != '\n')
            return 0;
        i++;
    }
    return 1;
}

static int parce_line(char *line, int *brasl, int *id, t_desc *desc)
{
    char *token;
    int count = 0; // count must be equal to desc->n

    token = strtok(line, " \t\n");
    if (token == NULL)
        return 0;

    int num = 0;
    while (token != NULL)
    {
        num = atoi(token);
        if (!is_number(token) || num < 0 || num > desc->n * desc->n)
        {
            if (token[0] == '#')
                break;
            if (num > desc->n * desc->n)
                printf("Too big number to cope with for this puzzle\n");
            return 0;
        }
        brasl[*id] = (num != 0) ? num : desc->n * desc->n;
        (*id)++;
        count++;
        token = strtok(NULL, " \t\n");
    }

    if (count == desc->n)
        return 1;
    else
        return 0;
}

static int provide_heuristic(char **av, t_desc *desc)
{
    if (strcmp(av[1], "0") && strcmp(av[1], "1") && strcmp(av[1], "2") && strcmp(av[1], "3"))
            return int_cust_error("Please write valid heuristic.");
    int h = atoi(av[1]);
    desc->heur = heuristics_table[h].heur;
    return 1;
}

static int parce_args(int ac, char **av, FILE **stream, t_desc *desc)
{
    char *file_name = NULL;
    if (ac == 3)
    {
        file_name = av[2];
        *stream = fopen(file_name, "r");
        if (*stream == NULL || !provide_heuristic(av, desc))
            return int_cust_error(file_name);
    }
    else if (ac == 2)
    {
        if (!provide_heuristic(av, desc))
            return int_cust_error("Please write valid heuristic.");
        *stream = stdin;
        printf("Please, provide dimension and the puzzle.\n");
    }
    else
    {
        printf("Wrong number of arguments.\n"
        "Use: ./npuzzle  <heuristic>  (optional)<file_name>\n"
        "<heuristic>: 0 - Hamming, 1 - Manhattan, 2 - Euclidean, 3 - Petryshynian\n");
        return 0;
    }
    return 1;
}

static int bad_brasl(int *brasl, t_desc *desc)
{
    if (!brasl)
        return 1;

    int count;
    for (int i = 1; i <= desc->n * desc->n; i++)
    {
        count = 0;
        for (int j = 0; j < desc->n * desc->n; j++)
        {
            if (brasl[j] == i)
                count++;
        }
        if (count != 1)
        {
            if (count > 1)
                printf("You have duplicate of \"%d\"\n", i);
            else
                printf("You've missed \"%d\"\n", i);
            return 1;
        }
    }
    return 0;
}

int *parce_input(int ac, char **av, t_desc *desc)
{
    FILE *stream;

    if (!parce_args(ac, av, &stream, desc))
        return NULL;

    size_t len = 0;
    int lines_counter = 0;
    char *line = NULL;
    int *brasl = NULL;
    bool has_dimension = false;
    int id = 0;
    size_t read = 0;
    while ((read = getline(&line, &len, stream)) != -1)
    {
        if (line && !has_dimension && is_dimension_line(line))
        {
            desc->n = atoi(line);
            if (desc->n <= 2)
                return custom_error("Bad dimension. n should be >= 3.\n");
            brasl = (int *)malloc(sizeof(int) * desc->n * desc->n);
            memset(brasl, 0, sizeof(int) * desc->n * desc->n);
            has_dimension = true;
        }
        else if (line && has_dimension && is_puzzle_line(line))
        {
            if (!parce_line(line, brasl, &id, desc))
                goto Exit;
            lines_counter++;
            if (lines_counter == desc->n)
                goto Exit;
        }
        else if (line && is_comment(line))
        {
            // do nothing
        }
        else
        {
            /* this is bullshit */
            int_cust_error("Please, give nice input! \"n\" at first, then puzzle-lines\n");
            goto Exit;
        }
    }

Exit:
    if ((brasl && lines_counter != desc->n) || (bad_brasl(brasl, desc)))
    {
        int_cust_error("Bad puzzle line input!\n");
        free(brasl);
        brasl = NULL;
    }
    free(line);
    if (stream != stdin)
        fclose(stream);
    return brasl;
}