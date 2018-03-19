/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here
struct queue *root0;
struct queue *root1;
struct queue *root2;
struct queue *root3;
struct queue *conductor0;
struct queue *conductor1;
struct queue *conductor2;
struct queue *conductor3;
struct resources res;
extern int termination[4];
struct proc zeroRuntimeProcess0;
struct proc zeroRuntimeProcess1;
struct proc zeroRuntimeProcess2;
struct proc zeroRuntimeProcess3;
// Define functions declared in hostd.h here
void print(int priority){
	if(priority==0){
		conductor0 = root0;
		if ( conductor0 != 0 ) { /* Makes sure there is a place to start */
    		while ( conductor0->next != 0 ) {
        		printf( "\t%i\t%i\t%i\t%i\n",conductor0->process.pid,conductor0->process.priority,conductor0->process.memory,conductor0->process.runtime);
        		conductor0 = conductor0->next;
   		 	}
    		printf( "\t%i\t%i\t%i\t%i\n",conductor0->process.pid,conductor0->process.priority,conductor0->process.memory,conductor0->process.runtime);
		}
	}
	if(priority==1){
		conductor1 = root1;
		if ( conductor1 != 0 ) { /* Makes sure there is a place to start */
    		while ( conductor1->next != 0 ) {
        		printf( "\t%i\t%i\t%i\t%i\n",conductor1->process.pid,conductor1->process.priority,conductor1->process.memory,conductor1->process.runtime);
        		conductor1 = conductor1->next;
   		 	}
    		printf( "\t%i\t%i\t%i\t%i\n",conductor1->process.pid,conductor1->process.priority,conductor1->process.memory,conductor1->process.runtime);
		}
	}
	if(priority==2){
		conductor2 = root2;
		if ( conductor2 != 0 ) { /* Makes sure there is a place to start */
    		while ( conductor2->next != 0 ) {
        		printf( "\t%i\t%i\t%i\t%i\n",conductor2->process.pid,conductor2->process.priority,conductor2->process.memory,conductor2->process.runtime);
        		conductor2 = conductor2->next;
   		 	}
    		printf( "\t%i\t%i\t%i\t%i\n",conductor2->process.pid,conductor2->process.priority,conductor2->process.memory,conductor2->process.runtime);
		}
	}
	if(priority==3){
		conductor3 = root3;
		if ( conductor3 != 0 ) { /* Makes sure there is a place to start */
    		while ( conductor3->next != 0 ) {
        		printf( "\t%i\t%i\t%i\t%i\n",conductor3->process.pid,conductor3->process.priority,conductor3->process.memory,conductor3->process.runtime);
        		conductor3 = conductor3->next;
   		 	}
    		printf( "\t%i\t%i\t%i\t%i\n",conductor3->process.pid,conductor3->process.priority,conductor3->process.memory,conductor3->process.runtime);
		}
	}
	printf("done printing\n");
}
void initializeQueues(){
	zeroRuntimeProcess0.runtime=0;
	zeroRuntimeProcess0.priority=0;
	zeroRuntimeProcess0.address=8080;
	zeroRuntimeProcess0.pid=34404;
	zeroRuntimeProcess1.runtime=0;
	zeroRuntimeProcess1.priority=1;
	zeroRuntimeProcess1.address=8080;
	zeroRuntimeProcess1.pid=34404;
	zeroRuntimeProcess2.runtime=0;
	zeroRuntimeProcess2.priority=2;
	zeroRuntimeProcess2.address=8080;
	zeroRuntimeProcess2.pid=34404;
	zeroRuntimeProcess3.runtime=0;
	zeroRuntimeProcess3.priority=3;
	zeroRuntimeProcess3.address=8080;
	zeroRuntimeProcess3.pid=34404;
	root0 = malloc( sizeof(struct queue) ); 
	root1 = malloc( sizeof(struct queue) );
	root2 = malloc( sizeof(struct queue) ); 
	root3 = malloc( sizeof(struct queue) );    
	root0->process=zeroRuntimeProcess0;
	root1->process=zeroRuntimeProcess1;
	root2->process=zeroRuntimeProcess2;
	root3->process=zeroRuntimeProcess3;
		root0->next = 0;   
		root0->process = zeroRuntimeProcess0;
		conductor0 = root0; 
		if ( conductor0 != 0 ) {
		    while ( conductor0->next != 0)
		    {
		        conductor0 = conductor0->next;
		    }
		}
		root1->next = 0;   
		root1->process = zeroRuntimeProcess1;
		conductor1= root1; 
		if ( conductor1 != 0 ) {
		    while ( conductor1->next != 0)
		    {
		        conductor1 = conductor1->next;
		    }
		}
		root2->next = 0;   
		root2->process = zeroRuntimeProcess2;
		conductor2= root2; 
		if ( conductor2 != 0 ) {
		    while ( conductor2->next != 0)
		    {
		        conductor2 = conductor2->next;
		    }
		}
		root3->next = 0;   
		root3->process = zeroRuntimeProcess3;
		conductor3= root3; 
		if ( conductor3 != 0 ) {
		    while ( conductor3->next != 0)
		    {
		        conductor3 = conductor3->next;
		    }
		}
	printf("done initializing\n");
}
int main(int argc, char *argv[])
{
    initializeQueues();	
    load_dispatch("dispatchlist");
	res.res_avail[0]=2;
	res.res_avail[1]=1;
	res.res_avail[2]=1;
	res.res_avail[3]=2;
	for(int x=0;x<1024;x++){
		res.memory[x]=0;
	}
	print(0);
	print(1);
	print(2);
	print(3);
	makeT();	
	struct proc n;
	n=pop(root0,conductor0);
	n.address= alloc_mem(n.memory,n.priority);
	if (n.address==8080){
		printf("no memory\n");
		exit(0);
	}
	while(n.runtime>0){
		int status;
			printf("current:\t%i\t%i\t%i\t%i\n",n.priority,n.memory,n.runtime,n.address);
  		pid_t pid;
		pid = fork();
    	if (pid==0){
			//printf("Hello from child!\n"); 
			execl("/home/dafungajunga/Documents/oslab4/process","process",NULL);
		    perror("execl() failure!\n\n");
		}
    	else{ 
			sleep(n.runtime);
			n.pid=pid;
			//printf("Hello from Parent! %d\n",pid); 
			kill(pid,SIGINT);
			waitpid (pid, &status, 0);
			n.runtime=0;
			free_mem(n.address,n.memory);
			if (conductor0->next==0){
				break;
			}
			n=pop(root0,conductor0);
			printf("current:\t%i\t%i\t%i\t%i\n",n.priority,n.memory,n.runtime,n.address);
			n.address= alloc_mem(n.memory,n.priority);
			if (n.address==8080){
				printf("no memory\n");
				exit(0);
			}
		}
	}
	//return EXIT_SUCCESS;
	printf("priority 0 finished\n");
	struct proc m;
	while(termination[1]>0){
		int status;
  		pid_t pid;
		m=pop(root1,conductor1);
		printf("current:\t%i\t%i\t%i\t%i\n",m.priority,m.memory,m.runtime,m.address);	
			print(1);	
		printf("current termination:%d\n",termination[1]);		
		if (m.runtime<=0){
			printf("runtime <=0\n");
			termination[1]-=1;
			//continue;
		}
		m.address= alloc_mem(m.memory,m.priority);
		if (m.address==8080){
			printf("no memory, pushing back\n");
			push(root1,conductor1,m);
			continue;
		}
		while(m.pid==34404){
			//printf("PIDlooping\n");
			m=pop(root1,conductor1);
		}
		/*m.address= alloc_mem(m.memory,m.priority);
		if (m.address==8080){
			printf("no memory, pushing back\n");
			push(root1,conductor1,m);
			continue;
		}*/
		if(m.pid==0){
			pid = fork();
		}
		if (pid==0){
			execl("/home/dafungajunga/Documents/ostut8/process","process",NULL);
		    	perror("execl() failure!\n\n");
		}
    	else{
				conductor1 = root1;
				/*if(m.pid==0){
					m.pid=pid;
				}*/
				if (m.runtime==1){
					kill(m.pid,SIGCONT);
					waitpid (m.pid, &status, WCONTINUED);
					sleep(1);
					kill(m.pid,SIGINT);
					m.runtime-=1;
					waitpid (m.pid, &status, 0);
					free_mem(m.address,m.memory);
					termination[1]-=1;
					printf("done\n");
					continue;
				}
				if(m.pid==0){
					m.pid=pid;
					sleep(1);
					kill(m.pid,SIGTSTP);
					waitpid (m.pid, &status, WUNTRACED);
					m.runtime-=1;
					printf("1suspended\n");
					if(m.runtime>0){
						printf("pushing\n");
						m.priority=2;
						push(root2,conductor2,m);
						free_mem(m.address,m.memory);
						printf("done pushing\n");
						termination[1]-=1;
						continue;
					}
					/*else{
						kill(m.pid,SIGINT);
						//m.runtime-=1;
						waitpid (m.pid, &status, 0);
						free_mem(m.address,m.memory);
						printf("done\n");
						termination[1]-=1;
						continue;
					}*/
				}
				if (m.runtime>0){
					kill(m.pid,SIGCONT);
					waitpid (m.pid, &status, WCONTINUED);
					sleep(1);
					m.runtime-=1;
					kill(m.pid,SIGTSTP);
					waitpid (m.pid, &status, WUNTRACED);
					printf("suspended\n");
					if(m.runtime>0){
						printf("pushing\n");
						m.priority=2;
						push(root2,conductor2,m);
						free_mem(m.address,m.memory);
						printf("done pushing\n");
						termination[1]-=1;
						continue;	
					}
					else{
						kill(m.pid,SIGCONT);
						waitpid (m.pid, &status, WCONTINUED);
						kill(m.pid,SIGINT);
						m.runtime-=1;
						waitpid (m.pid, &status, 0);
						free_mem(m.address,m.memory);
						termination[1]-=1;
						printf("done\n");
						continue;
					}	
				}
				
			}		
		}
		printf("priority 1 finished\n");
		makeT();
	while(termination[2]>0){
		int status;
  		pid_t pid;
		m=pop(root2,conductor2);
		printf("current:\t%i\t%i\t%i\t%i\n",m.priority,m.memory,m.runtime,m.address);	
			print(2);	
		printf("current termination:%d\n",termination[2]);		
		if (m.runtime<=0){
			printf("runtime <=0\n");
			termination[2]-=1;
			//continue;
		}
		m.address= alloc_mem(m.memory,m.priority);
		if (m.address==8080){
			printf("no memory, pushing back\n");
			m.priority=3;
			push(root3,conductor3,m);
			continue;
		}
		while(m.pid==34404){
			//printf("PIDlooping\n");
			m=pop(root2,conductor2);
		}
		/*m.address= alloc_mem(m.memory,m.priority);
		if (m.address==8080){
			printf("no memory, pushing back\n");
			push(root1,conductor1,m);
			continue;
		}*/
		if(m.pid==0){
			pid = fork();
		}
		if (pid==0){
			execl("/home/dafungajunga/Documents/ostut8/process","process",NULL);
		    	perror("execl() failure!\n\n");
		}
    	else{
				conductor2 = root2;
				/*if(m.pid==0){
					m.pid=pid;
				}*/
				if (m.runtime==1){
					kill(m.pid,SIGCONT);
					waitpid (m.pid, &status, WCONTINUED);
					sleep(1);
					kill(m.pid,SIGINT);
					m.runtime-=1;
					waitpid (m.pid, &status, 0);
					free_mem(m.address,m.memory);
					termination[2]-=1;
					printf("done\n");
					continue;
				}
				if(m.pid==0){
					m.pid=pid;
					sleep(1);
					kill(m.pid,SIGTSTP);
					waitpid (m.pid, &status, WUNTRACED);
					m.runtime-=1;
					printf("1suspended\n");
					if(m.runtime>0){
						printf("pushing\n");
						m.priority=3;
						push(root3,conductor3,m);
						free_mem(m.address,m.memory);
						printf("done pushing\n");
						termination[2]-=1;
						continue;
					}
					/*else{
						kill(m.pid,SIGINT);
						//m.runtime-=1;
						waitpid (m.pid, &status, 0);
						free_mem(m.address,m.memory);
						printf("done\n");
						termination[2]-=1;
						continue;
					}*/
				}
				if (m.runtime>0){
					kill(m.pid,SIGCONT);
					waitpid (m.pid, &status, WCONTINUED);
					sleep(1);
					m.runtime-=1;
					kill(m.pid,SIGTSTP);
					waitpid (m.pid, &status, WUNTRACED);
					printf("suspended\n");
					if(m.runtime>0){
						printf("pushing\n");
						m.priority=3;
						push(root3,conductor3,m);
						free_mem(m.address,m.memory);
						printf("done pushing\n");
						termination[2]-=1;
						continue;	
					}
					else{
						kill(m.pid,SIGCONT);
						waitpid (m.pid, &status, WCONTINUED);
						kill(m.pid,SIGINT);
						m.runtime-=1;
						waitpid (m.pid, &status, 0);
						free_mem(m.address,m.memory);
						termination[2]-=1;
						printf("done\n");
						continue;
					}	
				}
				
			}		
		}
		printf("priority 2 finished\n");
		makeT();
	while(termination[3]>0){
		int status;
  		pid_t pid;
		m=pop(root3,conductor3);
		printf("current:\t%i\t%i\t%i\t%i\n",m.priority,m.memory,m.runtime,m.address);	
			print(3);	
		printf("current termination:%d\n",termination[3]);		
		if (m.runtime<=0){
			printf("runtime <=0\n");
			termination[3]-=1;
			//continue;
		}
		m.address= alloc_mem(m.memory,m.priority);
		if (m.address==8080){
			printf("no memory, pushing back\n");
			push(root3,conductor3,m);
			continue;
		}
		while(m.pid==34404){
			//printf("PIDlooping\n");
			m=pop(root3,conductor3);
		}
		/*m.address= alloc_mem(m.memory,m.priority);
		if (m.address==8080){
			printf("no memory, pushing back\n");
			push(root1,conductor1,m);
			continue;
		}*/
		if(m.pid==0){
			pid = fork();
		}
		if (pid==0){
			execl("/home/dafungajunga/Documents/ostut8/process","process",NULL);
		    	perror("execl() failure!\n\n");
		}
    	else{
				conductor3 = root3;
				/*if(m.pid==0){
					m.pid=pid;
				}*/
				if (m.runtime==1){
					kill(m.pid,SIGCONT);
					waitpid (m.pid, &status, WCONTINUED);
					sleep(1);
					kill(m.pid,SIGINT);
					m.runtime-=1;
					waitpid (m.pid, &status, 0);
					free_mem(m.address,m.memory);
					termination[3]-=1;
					printf("done\n");
					continue;
				}
				if(m.pid==0){
					m.pid=pid;
					sleep(1);
					kill(m.pid,SIGTSTP);
					waitpid (m.pid, &status, WUNTRACED);
					m.runtime-=1;
					printf("1suspended\n");
					if(m.runtime>0){
						printf("pushing\n");
						push(root3,conductor3,m);
						free_mem(m.address,m.memory);
						printf("done pushing\n");
						//termination[3]-=1;
						continue;
					}
					else{
						kill(m.pid,SIGINT);
						//m.runtime-=1;
						waitpid (m.pid, &status, 0);
						free_mem(m.address,m.memory);
						printf("done\n");
						termination[3]-=1;
						continue;
					}
				}
				if (m.runtime>0){
					kill(m.pid,SIGCONT);
					waitpid (m.pid, &status, WCONTINUED);
					sleep(1);
					m.runtime-=1;
					kill(m.pid,SIGTSTP);
					waitpid (m.pid, &status, WUNTRACED);
					printf("suspended\n");
					if(m.runtime>0){
						printf("pushing\n");
						push(root3,conductor3,m);
						free_mem(m.address,m.memory);
						printf("done pushing\n");
						//termination[3]-=1;
						continue;	
					}
					else{
						kill(m.pid,SIGCONT);
						waitpid (m.pid, &status, WCONTINUED);
						kill(m.pid,SIGINT);
						m.runtime-=1;
						waitpid (m.pid, &status, 0);
						free_mem(m.address,m.memory);
						termination[3]-=1;
						printf("done\n");
						continue;
					}	
				}
				
			}		
		}
}
