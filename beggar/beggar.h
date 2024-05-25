#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"
#include "queue.h"

/* Player structure, for storing hands, status and adjacent players */
typedef struct player {
	QUEUE *hand;
	int playing;
	struct player *prev;
	struct player *next;
} PLAYER;

int finished(PLAYER **, int);
int beggar(int, int *, int);
