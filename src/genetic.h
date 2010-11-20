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
	/* referential origin */
	int x,y;

	/* coordinates of the initial living cells*/
	int dna[GENESIZE][2];

	/* the mutation rate is also coded in the gene so it can find the optimal one */
	int mutation_rate; /* per 1000 */

	/* the fitness value*/
	int val;
} gene;

typedef struct {
	/* a pool of genes */
	gene elements[POOLSIZE];
} genepool;

gene * gene_new(void);

void gene_crossover(gene *ngene, gene *a, gene *b);

void gene_print(gene *g);

void gene_eval(gene *g, int ngen);

int gene_cmp(const void *a,const void *b);

void gene_mutation(gene *g);

genepool * genepool_new(void);

void genepool_reproduce(genepool *p);

void genetic_algorithm(int ngenerations);

#endif
