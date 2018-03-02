#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
int puzzleArray[9][9];


int read(void){
	int c =0;
	int counter = 0;
	int row =0;
	int column = 0;
	FILE *file;
	file = fopen("puzzle.txt","r");
	if(file){
		while((c = getc(file))!= EOF){
			putchar(c);
			row = floor(counter/9);
			column=counter %9;
			puzzleArray[row][column]=c;
			counter++;
		}
		
	}
	return 0;
}


int search(int *arr)
{
   for(int i=0; i<9; i++)
   {
    for(int j=i+1;j<9;j++)
    {
    if(arr[i]==arr[j] &&arr[i]!=0)
    {
	printf("dup %d\n",arr[j]);
    	return 0;
	}
    
   }
   }
	return 1;
}
void *threeByThree(void *i){
	//0-8:TL,TM,TR,ML,MM,MR,BL,BM,BR
	int grid = *((int*)i);
	int presentNum[9]={0,0,0,0,0,0,0,0,0};

	int row = floor(grid/3);
	int column= 3*(grid%3);


	for (int x=0;x<9;x++){
		//printf("puzzleArray:%d\n",puzzleArray[row][column]);
			//printf("grid:%d row:%d column:%d\n",grid,row,column);
		if(puzzleArray[row][column]>=0 && puzzleArray[row][column]<10){
			presentNum[x]=puzzleArray[row][column];
			if(search(presentNum)){
				continue;
			}
			else{
				printf("false dup------\n");
				return 0;
			}
		}
		else{
			printf("false out of bounds--------\n");
			return 0;
		}		
		if (x%3){
			column++;
		}
		else{
			row++;
			column =(grid+1)%3;
		}
	}

	printf("true\n");
	return (void *)1;
}

int main(void){
	int rc;
	int i;
	pthread_t subgrids[9];
	//pthread_attr_t attr;
	int *arg = malloc(sizeof(int));
	*arg = 1;
	void *status;

//pthread_attr_init(&attr);
   	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for( i=0; i<9; i++){
		int j = i;
		*arg =j;
		rc = pthread_create(&subgrids[i], NULL, threeByThree, (void *)arg);
		if (rc) {
         		printf("Error:unable to create thread\n");
         		exit(-1);
      		}	
	}
		free(arg); arg = NULL;
	for( i=0; i<9; i++){
		rc = pthread_join(subgrids[i], NULL);
		if (rc) {
         		printf("Error:unable to create join\n");
         		exit(-1);
      		}	
	}
	pthread_exit(NULL);
}


