#ifndef STUFF_H
#define STUFF_H

#include "queueprio.h"

int abs(int num);
void print_puzzle(int *brasl, int n);
void print_listway(t_list *list, int n);
void print_pass(t_list *list, t_desc *desc);
void set_closed_null(t_clos **closed, int hwc);
int count_worst_case(int n);
void free_opened(t_set *opened);
void free_closed(t_clos **closed, t_desc *desc);
void free_traces(t_list *e, t_set *opened, t_clos **closed, t_desc *desc);

#endif