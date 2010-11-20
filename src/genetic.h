#ifndef __DEF_GENETIC__
#define __DEF_GENETIC__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

#define GENESIZE 20
#define POOLSIZE 100
#define POS_X 0
#define POS_Y 1

typedef struct {
	int x,y;
	int dna[GENESIZE][2];
	int mutation_rate; /* per 1000 */
	int val;
} gene;

typedef struct {
	gene elements[POOLSIZE];
} genepool;

gene * gene_new(void);

void gene_crossover(gene *ngene, gene *a, gene *b);

void gene_print(gene *g);

void gene_eval(gene *g, int ngen);

int gene_cmp(const void *a,const void *b);

genepool * genepool_new(void);

void genepool_reproduce(genepool *p);

void genetic_algorithm(int ngenerations);

#endif
