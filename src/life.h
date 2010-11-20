#ifndef __DEF_LIFE__
#define __DEF_LIFE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	The width and height of the board
	we don't expand infinitely but just
 	within the board margins
 */
#define BOARDWIDTH 50
#define BOARDHEIGHT 50

/*	Data structure that represents the board */
typedef struct {
	int board[BOARDWIDTH][BOARDHEIGHT];
} lifegame;

/*	Create a new board */
lifegame * lifegame_new(void);

/*	Prints the board */
void lifegame_print(lifegame *l);

/*	Run one step */
void lifegame_step(lifegame *p);

/*	Run for several generations */
void lifegame_run(lifegame *l,int nsteps);

/*	Count how many pos are occupied */
int lifegame_eval(lifegame *l);

#endif
