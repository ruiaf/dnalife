#ifndef __DEF_LIFE__
#define __DEF_LIFE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARDWIDTH 20
#define BOARDHEIGHT 20

typedef struct {
	int board[BOARDWIDTH][BOARDHEIGHT];
} lifegame;

/* create a new board */
lifegame * lifegame_new(void);

/* prints the board */
void lifegame_print(lifegame *l);

/* run one step */
void lifegame_step(lifegame *p);

/* run for several generations */
void lifegame_run(lifegame *l,int nsteps);

/* count how many pos are occupied */
int lifegame_eval(lifegame *l);

#endif
