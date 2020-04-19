#ifndef STUFF_H
#define STUFF_H

#include "queueprio.h"

int abs(int num);
void print_puzzle(int *brasl, int n);
void print_listway(t_list *list, int n);
void print_pass(t_list *list);
void set_closed_null(t_clos **closed, int hwc);
int count_worst_case(int n);

#endif