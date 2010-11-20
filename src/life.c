#include "life.h"

lifegame * lifegame_new(void) {
	lifegame * l;
	l=(lifegame*)malloc(sizeof(lifegame));
	memset(l,0,sizeof(lifegame));

	return l;
}

void lifegame_print(lifegame *l) {
	int i,j;

	for (i=0;i<BOARDWIDTH;i++) {
		for (j=0;j<BOARDHEIGHT;j++)
			if (l->board[i][j])
				putchar('x');
			else putchar('.');
		putchar('\n');
	}
}

void lifegame_step(lifegame *p) {
	lifegame *n;
	int i,j,count=0;

	n = lifegame_new();
	for (i=1;i<BOARDWIDTH-1;i++)
		for (j=1;j<BOARDHEIGHT-1;j++) {
			count = 0;
			count+= (p->board[i-1][j-1]!=0);
			count+= (p->board[i-1][j]!=0);
			count+= (p->board[i-1][j+1]!=0);
			count+= (p->board[i][j-1]!=0);
			count+= (p->board[i][j+1]!=0);
			count+= (p->board[i+1][j-1]!=0);
			count+= (p->board[i+1][j]!=0);
			count+= (p->board[i+1][j+1]!=0);
			if (p->board[i][j]) {
				if (count>1 &&  count<4)
					n->board[i][j]=1;
			} else if (count==3) {
				n->board[i][j]=1;
			}
		}
	memcpy(p,n,sizeof(lifegame));
	free(n);
}

int lifegame_eval(lifegame *l) {
	int i,j;
	int count = 0;

	for (i=0;i<BOARDWIDTH;i++)
		for (j=0;j<BOARDHEIGHT;j++)
			if (l->board[i][j]) {
				count++;
			}

	return count;
}

void lifegame_run(lifegame *l,int nsteps) {
	int i;

	for (i=0;i<nsteps;i++) {
		lifegame_step(l);
	}
}
