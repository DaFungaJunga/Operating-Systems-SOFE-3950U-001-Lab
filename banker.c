/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "banker.h"
#include <time.h>

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3
pthread_mutex_t mutex;

// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];
void *customer(void *id){
    int customer = *(int*)id;
    bool acquiredResources = false;
    int request [NUM_RESOURCES];
    while(1){
        for(int i = 0; i < NUM_RESOURCES; i++){
            request[i] = rand() % (maximum[customer][i] + 1); 
        }
        pthread_mutex_lock(&mutex);
        acquiredResources = request_res(customer,request);
        pthread_mutex_unlock(&mutex);
        if(acquiredResources){
            sleep((int)rand() % 5 + 1);
            acquiredResources = false;
            pthread_mutex_lock(&mutex);
            release_res(customer,request);
            pthread_mutex_unlock(&mutex);
            if(rand() % 2 == 0){
                printf("\nCustomer : %d is finished\n", customer);
                for(int i = 0; i < NUM_RESOURCES; i++){
                    need[customer][i] = 0;
                    maximum[customer][i] = 0;
                }
                printf("Maximum Needs After for Customer: \n",id);
                for(int i = 0; i < NUM_CUSTOMERS; i++){
                    for(int j = 0; j < NUM_RESOURCES; j++){
                        printf("%3d ",maximum[i][j]);
                    }
                    puts("");
                }
                sleep(2);
                break;
            }
        }
        sleep(1);
    }
return 0;
}
bool isSafe(){
    int work[NUM_RESOURCES];
    for(int i = 0; i < NUM_RESOURCES; i++){
        work[i] = available[i];
    }
    bool finish [NUM_CUSTOMERS];
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        finish[i] = false;
    }

    int count = 0;
    int indexFinish = -1;
    int prevFinishIndex = -1;
    bool finishCustomer = true;

    while (count < NUM_CUSTOMERS){
        prevFinishIndex = indexFinish; 
        for(int i = 0; i < NUM_CUSTOMERS; i++){
            if(!finish[i]){
                for(int j = 0; j < NUM_RESOURCES; j++){
                    if (need[i][j] > work[j])
                        finishCustomer = false;
                }
                if(finishCustomer){
                    indexFinish = i;
                    for(int j = 0; j < NUM_RESOURCES; j++){
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    count++;
                    finishCustomer = true;
                    break; 
                }
            }
        }
        for(int i = 0; i < NUM_CUSTOMERS; i++){
            if(!finish[i])
                break;
        }
        if(prevFinishIndex == indexFinish)
            return false;
    }
    return true;
}
// Define functions declared in banker.h here
bool request_res(int n_customer, int request[]){
	
    printf("\nCustomer: %d Requesting Resources\n",n_customer);
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",request[i]);
    }
    puts("");

    printf("Current Resources\n");
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",available[i]);
    }
    puts("");
     for(int i = 0; i < NUM_RESOURCES; i++){
        if(request[i] <= need[n_customer][i]){
            if(request[i] > available[i]){
                printf("UNSAFE: EXITING\n\n");
                sleep(1);
                return false;
            }
            else{
                printf("ATTEMPTING TO TAKE RESOURCES\n");
                for(int j = 0; j < NUM_RESOURCES; j++){
                    allocation[n_customer][j] += request[j];
                    available[j] -= request[j];
                    need[n_customer][j] -= request[j];
                }
                if(isSafe()){
                    printf("SAFE:REQUEST ACCEPTED\n");
                    printf("Available Resources After\n");
                    for(int i = 0; i < NUM_RESOURCES; i++){
                        printf("%d ",available[i]);
                    }
                    puts("\n");
                    sleep(2);
                    return true;
                }
                else{
                    printf("UNSAFE:REQUEST DENIED\n");
                    for(int j = 0; j < NUM_RESOURCES; j++){
                        available[j] += request[j]; 
                        need[n_customer][j] += request[j]; 
                        allocation[n_customer][j] -= request[j];
                    }
                    return false;
                }
            }
        } else{
            printf("CUSTOMER: %d REQUEST DENIED\n",n_customer);
            sleep(1);
            return false;
        }
    } 
return true;
}
// Release resources, returns true if successful
bool release_res(int n_customer, int release[]){
	printf("\nCustomer: %d Releasing Resources\n", n_customer);
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",release[i]);
        available[i] += release[i]; 
        need[n_customer][i] += release[i]; 
        allocation[n_customer][i] -= release[i];
    }
    puts("");
    printf("Available Resources After\n");
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",available[i]);
    }
    puts("");
    sleep(2);
return true;
}
int main(int argc, char *argv[]){
	pthread_mutex_init(&mutex,NULL);
	pthread_t threads[NUM_CUSTOMERS];
	for (int x =0; x < NUM_RESOURCES; x++) {
		available[x]=atoi(argv[x+1]); 
		for(int y=0;y<NUM_CUSTOMERS;y++){
			maximum[y][x]=rand() % (available[x]+1);
			need[y][x] = maximum[y][x];
			allocation[y][x] = 0;
		}
	}
	for(int i=0;i<NUM_CUSTOMERS;i++){
		int *id = malloc(sizeof(int));
		*id=i;
		pthread_create(&threads[i],NULL,&customer, id);
	}
	for(int i = 0; i < NUM_CUSTOMERS; i++){
        pthread_join(threads[i],NULL);
	}
	 pthread_mutex_destroy(&mutex);

	// Read in arguments from CLI, NUM_RESOURCES is the number of arguments   
    // Initialize the pthreads, locks, mutexes, etc.
    // Run the threads and continually loop
    // The threads will request and then release random numbers of resources
    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly  
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
