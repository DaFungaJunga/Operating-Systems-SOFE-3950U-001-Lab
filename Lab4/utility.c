/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "queue.h"
extern struct queue *root0;
extern struct queue *root1;
extern struct queue *root2;
extern struct queue *root3;
extern struct queue *conductor0;
extern struct queue *conductor1;
extern struct queue *conductor2;
extern struct queue *conductor3;
extern struct resources res;
// Define your utility functions here, you will likely need to add more...
int termination[4];
int alloc_mem(int memory,int priority,int resourceType[4]){
	int count=0;
	int index=0;
	for (int x = 0; x < MEMORY; x++){
		if (res.memory[x]==0){
			res.memory[x]=1;
			//printf("found one\n");
			count++;
		}
		else{
			for (int y = index; y < (index+count); y++){
				res.memory[y]=0;
				//printf("reset");
			}
			count=0;
			index=x+1;
		}
		if (count==memory){
			printf("found space\n");
			if(resourceType[0]<=res.res_avail[0]&&resourceType[1]<=res.res_avail[1]&&resourceType[2]<=res.res_avail[2]&&resourceType[3]<=res.res_avail[3]){
				res.res_avail[0]-=resourceType[0];
				res.res_avail[1]-=resourceType[1];
				res.res_avail[2]-=resourceType[2];
				res.res_avail[3]-=resourceType[3];
				return index;
			}
		}
	}
	printf("searching for process to delete\n");
	if (priority==0){
		int address=8080;
		conductor0 = root0;
		while (1){
			if (priority<=conductor0->process.priority &&conductor0->process.address!=8080 &&conductor0->process.memory >=memory){
				address=conductor0->process.address;
				if(conductor0->process.memory>memory){
					for (int y = (address+memory); y < (address+conductor0->process.memory); y++){
						resources.memory[y]=0;
					}		
				}

				conductor0->process.address=8080;
				printf("found address\n");
				if((resourceType[0]+conductor0->process.resourceType[0])<=res.res_avail[0]&&(resourceType[1]+conductor0->process.resourceType[1])<=res.res_avail[1]&&(resourceType[2]+conductor0->process.resourceType[2])<=res.res_avail[2]&&(resourceType[3]+conductor0->process.resourceType[3])<=res.res_avail[3]){
					res.res_avail[0]-=(resourceType[0]+conductor0->process.resourceType[0]);
					res.res_avail[1]-=(resourceType[1]+conductor0->process.resourceType[1]);
					res.res_avail[2]-=(resourceType[2]+conductor0->process.resourceType[2]);
					res.res_avail[3]-=(resourceType[3]+conductor0->process.resourceType[3]);
					return address;
				}
			}
			if(conductor0->next != 0){
				//printf("looping");
        		conductor0 = conductor0->next;
				continue;
			}
			else{
				//printf("could not find address\n");
				return address;
			}
		}
	}
	if (priority==1){
		int address=8080;
		conductor1 = root1;
		while (1){
			if (priority<=conductor1->process.priority &&conductor1->process.address!=8080 &&conductor1->process.memory >=memory){
				address=conductor1->process.address;
				if(conductor1->process.memory>memory){
					for (int y = (address+memory); y < (address+conductor1->process.memory); y++){
						resources.memory[y]=0;
					}		
				}
				if((resourceType[0]+conductor1->process.resourceType[0])<=res.res_avail[0]&&(resourceType[1]+conductor1->process.resourceType[1])<=res.res_avail[1]&&(resourceType[2]+conductor1->process.resourceType[2])<=res.res_avail[2]&&(resourceType[3]+conductor1->process.resourceType[3])<=res.res_avail[3]){
					res.res_avail[0]-=(resourceType[0]+conductor1->process.resourceType[0]);
					res.res_avail[1]-=(resourceType[1]+conductor1->process.resourceType[1]);
					res.res_avail[2]-=(resourceType[2]+conductor1->process.resourceType[2]);
					res.res_avail[3]-=(resourceType[3]+conductor1->process.resourceType[3]);
					conductor1->process.address=8080;
					printf("found address\n");
					return address;
				}
			}
			if(conductor1->next != 0){
        		conductor1 = conductor1->next;
				continue;
			}
			else{
				//printf("could not find address\n");
				return address;
			}
		}
	}
	if (priority==2){
		int address=8080;
		conductor2 = root2;
		while (1){
			if (priority<=conductor2->process.priority &&conductor2->process.address!=8080 &&conductor2->process.memory >=memory){
				address=conductor2->process.address;
				if(conductor2->process.memory>memory){
					for (int y = (address+memory); y < (address+conductor2->process.memory); y++){
						resources.memory[y]=0;
					}		
				}
				if((resourceType[0]+conductor2->process.resourceType[0])<=res.res_avail[0]&&(resourceType[1]+conductor2->process.resourceType[1])<=res.res_avail[1]&&(resourceType[2]+conductor2->process.resourceType[2])<=res.res_avail[2]&&(resourceType[3]+conductor2->process.resourceType[3])<=res.res_avail[3]){
					res.res_avail[0]-=(resourceType[0]+conductor2->process.resourceType[0]);
					res.res_avail[1]-=(resourceType[1]+conductor2->process.resourceType[1]);
					res.res_avail[2]-=(resourceType[2]+conductor2->process.resourceType[2]);
					res.res_avail[3]-=(resourceType[3]+conductor2->process.resourceType[3]);
					conductor2->process.address=8080;
					printf("found address\n");
					return address;
				}
			}
			if(conductor2->next != 0){
        		conductor2 = conductor2->next;
				continue;
			}
			else{
				//printf("could not find address\n");
				return address;
			}
		}
	}
	else{
		int address=8080;
		conductor3 = root3;
		while (1){
			if (priority<=conductor3->process.priority &&conductor3->process.address!=8080 &&conductor0->process.memory >=memory){
				address=conductor3->process.address;
				if(conductor3->process.memory>memory){
					for (int y = (address+memory); y < (address+conductor3->process.memory); y++){
						resources.memory[y]=0;
					}		
				}
				
				if((resourceType[0]+conductor3->process.resourceType[0])<=res.res_avail[0]&&(resourceType[1]+conductor3->process.resourceType[1])<=res.res_avail[1]&&(resourceType[2]+conductor3->process.resourceType[2])<=res.res_avail[2]&&(resourceType[3]+conductor3->process.resourceType[3])<=res.res_avail[3]){
					res.res_avail[0]-=(resourceType[0]+conductor3->process.resourceType[0]);
					res.res_avail[1]-=(resourceType[1]+conductor3->process.resourceType[1]);
					res.res_avail[2]-=(resourceType[2]+conductor3->process.resourceType[2]);
					res.res_avail[3]-=(resourceType[3]+conductor3->process.resourceType[3]);
					conductor3->process.address=8080;
					printf("found address\n");
					return address;
				}
			}
			if(conductor3->next != 0){
        		conductor3 = conductor3->next;
				continue;
			}
			else{
				//printf("could not find address\n");
				return address;
			}
		}
	}
}

void free_mem(int index, int memory,int resourceType[4]){
   int count=0;
	for (int x = index; count < memory; x++){
		res.memory[x]=0;
		count++;
	}
	res.res_avail[0]+=resourceType[0];
	res.res_avail[1]+=resourceType[1];
	res.res_avail[2]+=resourceType[2];
	res.res_avail[3]+=resourceType[3];
}
void makeT(){
	termination[0]=0;
	termination[1]=0;
	termination[2]=0;
	termination[3]=0;
	conductor0 = root0;
	conductor1 = root1;
	conductor2 = root2;
	conductor3 = root3;
	if ( conductor0 != 0 ) { /* Makes sure there is a place to start */
    	while ( conductor0->next != 0 ) {
			termination[0]+=1;
        	conductor0 = conductor0->next;
   	 	}
		//termination[0]+=1;
	}
	if ( conductor1 != 0 ) { /* Makes sure there is a place to start */
    	while ( conductor1->next != 0 ) {
			termination[1]+=1;
        	conductor1 = conductor1->next;
   	 	}
		//termination[1]+=1;
	}
	if ( conductor2 != 0 ) { /* Makes sure there is a place to start */
    	while ( conductor2->next != 0 ) {
			termination[2]+=1;
        	conductor2 = conductor2->next;
   	 	}
		//termination[2]+=1;
	}
	if ( conductor3 != 0 ) { /* Makes sure there is a place to start */
    	while ( conductor3->next != 0 ) {
			termination[3]+=1;
        	conductor3 = conductor3->next;
   	 	}
		//termination[3]+=1;
	}
}

