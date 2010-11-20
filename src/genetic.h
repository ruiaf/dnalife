#ifndef __DEF_GENETIC__
#define __DEF_GENETIC__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

#define GENESIZE 20
#define POOLSIZE 200
#define POS_X 0
#define POS_Y 1

/*	Gene structure that represents the initial
	object that we are trying to optimize */
typedef struct {
	/* referential origin */
	int x,y;

	/* coordinates of the initial living cells, up to GENESIZE of them*/
	int dna[GENESIZE][2];

	/* the mutation rate is also coded in the gene so it can find the optimal one */
	int mutation_rate; /* per 1000 */

	/* the fitness value*/
	int val;
} gene;


/* The pool of genes that is keept in memory
   with each generation */
typedef struct {
	gene elements[POOLSIZE];
} genepool;

/*	Initialize and allocate a gene */
gene * gene_new(void);

/*	Crossover two genes */
void gene_crossover(gene *ngene, gene *a, gene *b);

/*	Output a gene */
void gene_print(gene *g);

/* Evaluate how good a gene is. This consists of running the game of life
   for ngenerations and counting how many cells are occupied */
void gene_eval(gene *g, int ngen);

/* Compare the fitness of two genes */
int gene_cmp(const void *a,const void *b);

/* Random mutation of a gene */
void gene_mutation(gene *g);

/* Initialize and allocate a gene pool */
genepool * genepool_new(void);

/* Do the whole cycle of reproduction. Crossover + Mutation */
void genepool_reproduce(genepool *p);

/* The complete logic of the genetic algorithm */
void genetic_algorithm(int ngenerations);

#endif
