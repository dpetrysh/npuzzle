#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "stuff.h"

int heur_hamming(int *brasl, t_desc *desc);
int heur_manhatt(int *brasl, t_desc *desc);
int heur_petryshyn(int *brasl, t_desc *desc);
int heur_euclidean(int *brasl, t_desc *desc);

#endif