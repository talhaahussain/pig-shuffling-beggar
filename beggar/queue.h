#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __UTIL_H
#define __UTIL_H
#include "util.h"
#endif

/* Node structure, used for storing individual pieces of data. */
struct node
{
	int data;
	struct node *next;
};
typedef struct node NODE;

/* Queue structure, used for storing multiple nodes. */
struct queue
{
	NODE *head;
	NODE *tail;
};
typedef struct queue QUEUE;

NODE *new_node(int data);
QUEUE *new_queue();
BOOL is_empty(QUEUE *queue);
void enqueue(QUEUE *queue, int data);
int dequeue(QUEUE *queue);
void print_queue(NODE *node);
int get_length(QUEUE *queue);
void merge_queue(QUEUE *queue1, QUEUE *queue2);
void empty_queue(QUEUE *queue);
