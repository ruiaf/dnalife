#include "genetic.h"

gene * gene_new(void) {
	gene *g = (gene*) malloc(sizeof(gene));
	memset(g,0,sizeof(gene));
	return g;
}

void gene_crossover(gene *ngene,gene *a, gene *b) {
	int crosspoint,order;
	gene *temp;

	order = rand()%2;
	if (order) {
		temp = a;
		a = b;
		b = temp;
	}

	crosspoint = rand()%GENESIZE;
	/*
	//memcpy(ngene->dna,a->dna,crosspoint*sizeof(ngene->dna[0]));
	//memcpy(ngene->dna,&(a->dna[crosspoint]),(GENESIZE-crosspoint)*sizeof(ngene->dna[0]));

	//ngene->x=a->x;
	//ngene->y=a->y;
	//ngene->mutation_rate=20;*/
}

void gene_mutation(gene *g) {
	int i;

	if (g->mutation_rate>(random()%10000)) {
		g->mutation_rate=random()%10000;
	}

	if (g->mutation_rate>(random()%10000)) {
		g->x=random()%BOARDHEIGHT;
	}

	if (g->mutation_rate>(random()%10000)) {
		g->y=random()%BOARDWIDTH;
	}

	for (i=0;i<GENESIZE;i++) {
		if (g->mutation_rate>(random()%10000)) {
			g->dna[i][POS_X]=random()%BOARDHEIGHT;
		}
		if (g->mutation_rate>(random()%10000)) {
			g->dna[i][POS_Y]=random()%BOARDWIDTH;
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
		if (g->dna[i][POS_X]<BOARDHEIGHT && g->dna[i][POS_Y]<BOARDWIDTH)
			life->board[g->dna[i][POS_X]][g->dna[i][POS_Y]]=1;
	}

	g->val = lifegame_eval(life);
	/*printf("%d",g->val);
	lifegame_run(life,ngen);*/
}

int gene_cmp(const void *a,const void *b) {
	return ((gene *)a)->val-((gene *)b)->val;
}

genepool * genepool_new(void) {
	int i;
	genepool *g = (genepool*) malloc(sizeof(genepool));
	memset(g,0,sizeof(genepool));

	for (i=0;i<POOLSIZE;i++) {
		g->elements[i].mutation_rate=10000;
	}
	return g;
}

void genepool_reproduce(genepool * p) {

	int i,j;
	gene next_gen[POOLSIZE*POOLSIZE];
	memset(next_gen,0,sizeof(next_gen));

	for (i=0;i<POOLSIZE;i++)
		for (j=0;j<POOLSIZE;j++) {
			/*printf("%d %d\n",i,j);*/
			gene_crossover(&next_gen[i*POOLSIZE+j],&p->elements[i],&p->elements[j]);
			gene_mutation(&next_gen[i*POOLSIZE+j]);
			gene_eval(&next_gen[i*POOLSIZE+j],1);
		}

	qsort((void *)next_gen,POOLSIZE*POOLSIZE,sizeof(gene*),gene_cmp);
	memcpy(p->elements,next_gen,sizeof(p->elements));
}

void genetic_algorithm(int ngenerations) {
	int best_gene_eval=0;
	genepool *pool = genepool_new();

	while(ngenerations--) {
		printf("%d GENERATION:\n",ngenerations);
		genepool_reproduce(pool);
		puts("finished rep");
		/*if (pool->elements[0].val>best_gene_eval) {
			best_gene_eval = pool->elements[0].val;
			*/gene_print(&pool->elements[0]);
		//}
		getchar();
	}
}
