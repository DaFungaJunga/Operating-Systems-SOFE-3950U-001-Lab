/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include "utility.h"

// Your linked list structure for your queue
// typedef ... 
//  ...
//  proc process;
//  ...
//} node_t; 

struct queue{
	struct proc process;
    	struct queue * next;
} queue;

// Include your relevant FIFO queue functions declarations here they must start 
// with the extern keyword such as in the following examples:

// Add a new process to the queue, returns the address of the next node added
// to the linked list

// extern node_t *push(node_t *tail, proc process);

// extern node_t *pop(node_t *tail);

extern void push( struct queue * conductor,struct queue * root,struct proc process);
extern struct proc pop(struct queue * conductor,struct queue * root);
extern void load_dispatch(char *dispatch_file);
#endif /* QUEUE_H_ */
