#include "genetic.h"

gene * gene_new(void) {
	gene *g = (gene*) malloc(sizeof(gene));
	memset(g,0,sizeof(gene));
	g->mutation_rate=1000;
	return g;
}

void gene_crossover(gene *ngene,gene *a, gene *b) {
	int crosspoint;
	gene *temp;

	if (rand()%2) {
		temp = a;
		a = b;
		b = temp;
	}

	crosspoint = rand()%GENESIZE;

	memcpy(ngene->dna,a->dna,crosspoint*sizeof(ngene->dna[0]));
	memcpy(&(ngene->dna[crosspoint]),&(b->dna[crosspoint]),(GENESIZE-crosspoint)*sizeof(ngene->dna[0]));

	ngene->x=a->x;
	ngene->y=a->y;
	ngene->mutation_rate=a->mutation_rate;
}

void gene_mutation(gene *g) {
	int i;

	/* the best mutation_rate is also found through the genetic algorithm*/
	if (g->mutation_rate>(rand()%10000)) {
		g->mutation_rate=rand()%10000;
	}

	/*
	if (g->mutation_rate>(rand()%10000)) {
		g->x=rand()%BOARDWIDTH;
	}

	if (g->mutation_rate>(rand()%10000)) {
		g->y=rand()%BOARDHEIGHT;
	}
	*/

	for (i=0;i<GENESIZE;i++) {
		if (g->mutation_rate>(rand()%10000)) {
			g->dna[i][POS_X]=rand()%BOARDWIDTH;
		}
		if (g->mutation_rate>(rand()%10000)) {
			g->dna[i][POS_Y]=rand()%BOARDHEIGHT;
		}
	}
}

void gene_print(gene *g) {
	int i;

	printf("MUTATION RATE %d/10000\n",g->mutation_rate);
	printf("ORIGIN X:%d Y:%d\n",g->x,g->y);
	printf("EVOLUTION VAL: %d\n",g->val);
	for (i=0;i<GENESIZE;i++)
		printf("%d %d\n",g->dna[i][POS_X],g->dna[i][POS_Y]);
}

void gene_eval(gene *g,int ngen) {
	int i;
	lifegame *life;

	life = lifegame_new();

	for (i=0;i<GENESIZE;i++) {
		if (g->dna[i][POS_X]<BOARDWIDTH&& g->dna[i][POS_Y]<BOARDHEIGHT)
			life->board[g->dna[i][POS_X]][g->dna[i][POS_Y]]=1;
	}

	lifegame_run(life,ngen);
	g->val = lifegame_eval(life);

	free(life);
}

int gene_cmp(const void *a,const void *b) {
	return ((gene *)b)->val-((gene *)a)->val;
}

genepool * genepool_new(void) {
	int i;
	genepool *g = (genepool*) malloc(sizeof(genepool));
	memset(g,0,sizeof(genepool));

	for (i=0;i<POOLSIZE;i++) {
		g->elements[i].mutation_rate=1000;
	}
	return g;
}

void genepool_reproduce(genepool * p) {

	int i,j;
	gene next_gen[POOLSIZE*POOLSIZE];
	memset(next_gen,-1,sizeof(next_gen));

	for (i=0;i<POOLSIZE;i++)
		for (j=0;j<POOLSIZE;j++) {
			gene_crossover(&next_gen[i*POOLSIZE+j],&p->elements[i],&p->elements[j]);
			gene_mutation(&next_gen[i*POOLSIZE+j]);
			gene_eval(&next_gen[i*POOLSIZE+j],5);
		}

	qsort((void *)next_gen,POOLSIZE*POOLSIZE,sizeof(gene),gene_cmp);
	memcpy(p->elements,next_gen,sizeof(p->elements));
}

void genetic_algorithm(int ngenerations) {
	int i,best_gene_eval=0;
	genepool *pool = genepool_new();
	gene_print(&pool->elements[0]);

	for (i=0;i<ngenerations;i++) {
		printf("GENERATION #%d:\n",i);
		genepool_reproduce(pool);
		puts("FINISHED REPRODUCTION");
		if (pool->elements[0].val>best_gene_eval) {
			best_gene_eval = pool->elements[0].val;
			gene_print(&pool->elements[0]);
		}
	}

	free(pool);
}
