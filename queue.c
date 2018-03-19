/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

// node_t *push(node_t *tail, proc process);
// {
//      ...
// }

// node_t *pop(node_t *tail);
// {
//      ...
// }
extern struct queue *root0;
extern struct queue *root1;
extern struct queue *root2;
extern struct queue *root3;
extern struct queue *conductor0;
extern struct queue *conductor1;
extern struct queue *conductor2;
extern struct queue *conductor3;
extern int termination[4];
extern struct proc zeroRuntimeProcess0;
extern struct proc zeroRuntimeProcess1;
extern struct proc zeroRuntimeProcess2;
extern struct proc zeroRuntimeProcess3;
void push(struct queue * root,struct queue * conductor,struct proc process){
	conductor = root;
	if ( conductor != 0 ) { /* Makes sure there is a place to start */
    	while ( conductor->next != 0 ) {
        	//printf( "%s\n", conductor->process.name );
        	conductor = conductor->next;
   	 	}
    	//printf( "%s\n", conductor->process.name );
	}
	conductor->next = malloc( sizeof(struct queue) );  

    conductor = conductor->next; 

    if ( conductor == 0 )
    {
        printf( "Out of memory" );
        //return root,conductor;
    }
    /* initialize the new memory */
    conductor->next = 0;         
    conductor->process = process;

    //return root,conductor;
}
struct proc pop(struct queue * root,struct queue * conductor){
		struct proc zeroRuntimeProcess;
		zeroRuntimeProcess.runtime=0;
		zeroRuntimeProcess.address=8080;
		zeroRuntimeProcess.pid=34404;
		struct proc r;
		//printf("00here");
		if(root->process.priority==0){
			conductor0 = root0;
			r= root0->process;
			//printf("0here");
			/*if(root0->next==0){
				printf("next is zero");
				root0->process = zeroRuntimeProcess;
				terminate=0;
				root0=root0->next;
			return r;
			}*/
			if (root0->process.runtime==0){
				printf("0runtime was zero\n");
				root0=root0->next;
				r=root0->process;
			}
			/*if(root0->next==0){
				printf("0next is zero");
				root0->process = zeroRuntimeProcess;
				terminate=0;
				root0=root0->next;
				return r;
			}*/
			root0=root0->next;
				return r;
		}
		if(root->process.priority==1){
			conductor1 = root1;
			r=root1->process;
			/*if(root1->next==0){
				root0->process = zeroRuntimeProcess;
			}*/
			if (root1->process.runtime==0){
				printf("1runtime was zero\n");
				root1=root1->next;
				r=root1->process;
				//root1=root1->next;
				//termination[1]-=1;
				//return r;
			}
			//root1=root1->next;
			if(root1->next==0){
				printf("1next was zero\n");
				conductor1 = root1;
				conductor1->process = zeroRuntimeProcess1;
				//root1=root1->next;
				//termination[1]-=1;
				return r;
			}
			root1=root1->next;
			return r;
		}
		if(root->process.priority==2){
			conductor2 = root2;
			r=root2->process;
			/*if(root2->next==0){
				terminate=0;
			}*/
			if (root2->process.runtime==0){
				printf("2runtime was zero\n");
				root2=root2->next;
				r=root2->process;
			}
			if(root2->next==0){
				printf("2next was zero\n");
				conductor2 = root2;
				conductor2->process = zeroRuntimeProcess2;
				//root1=root1->next;
				//termination[1]-=1;
				return r;
			}
			root2=root2->next;
			return r;
		}
		else{
			conductor3 = root3;
			r=root3->process;
			/*if(root3->next==0){
				terminate=0;
			}*/
			if (root3->process.runtime==0){
				printf("3runtime was zero\n");
				root3=root3->next;
				r=root3->process;
			}
			if(root3->next==0){
				printf("3next was zero\n");
				conductor3 = root3;
				conductor3->process = zeroRuntimeProcess3;
				//root1=root1->next;
				//termination[1]-=1;
				return r;
			}
			root3=root3->next;
			return r;
		}
}
void load_dispatch(char *dispatch_file)
{
    int arrival;
	int priority;
	int runtime;
	int memory;
	int resourceType[4];
    int size=10;
    freopen(dispatch_file,"r",stdin);
    for(int x=0;x<size;x++){
        scanf("%i,",&arrival);
        scanf("%i,",&priority);
	scanf("%i,",&runtime);
        scanf("%i,",&memory);
		scanf("%i,",&resourceType[0]);
		scanf("%i,",&resourceType[1]);
		scanf("%i,",&resourceType[2]);
		scanf("%i",&resourceType[3]);
        struct proc process;
		printf("%i\n",priority);
		process.arrival=arrival;
        process.priority=priority;
        process.memory=memory;
        process.runtime=runtime;
		process.resourceType[0]=resourceType[0];
		process.resourceType[1]=resourceType[1];
		process.resourceType[2]=resourceType[2];
		process.resourceType[3]=resourceType[3];
		process.pid=0;
		process.address=0;

		if (priority==0){
			push(root0,conductor0,process);
		}
		if (priority==1){
			push(root1,conductor1,process);
		}
		if (priority==2){
			push(root2,conductor2,process);
		}
		if (priority==3){
			push(root3,conductor3,process);
		}
    }
    printf("done pushing\n");  
}
