#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int flag = 0;

void checkDuplicate(int array[]){
	for(int i = 0; i < 9 && !flag; i++){
		for(int j = i+1; j < 9 && !flag; j++){
			if(array[i] == array[j]){
				flag = 1;
				break;
			}
		}
	}
}

void* checkColumns(void* arg){
	int *temp_ptr = (int*)arg;
	int temp = *temp_ptr;
	int testArray[9];

	testArray[0] = temp;
	for(int i = 1; i < 9; i++){
		temp = *((9*i)+temp_ptr);
		testArray[i] = temp;
	}
	
	checkDuplicate(testArray);
	pthread_exit(0);
}

void* checkRows(void* arg)
{
	int *temp_ptr = (int*)arg;
	int temp = *temp_ptr;
	int testArray[9];

	testArray[0] = temp;
	for(int j = 1; j < 9; j++){
		temp = *(++temp_ptr);
		testArray[j] = temp;
	}

	checkDuplicate(testArray);
	pthread_exit(0);
}

void* checkSubgrids(void* arg){
	int *temp_ptr = (int*)arg;
	int temp = *temp_ptr;
	int testArray[9];

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			temp = *(temp_ptr++);
			testArray[j + 3*i] = temp;
		}
		for(int k = 0; k < 6; k++){
			temp = *(++temp_ptr);
		}
	}

	checkDuplicate(testArray);
	pthread_exit(0);
}

int main(void){
	int sudoku[9][9];
	FILE *fp;
	int i, j;
	
	fp = fopen("puzzle2.txt", "r");
	if(fp == NULL){
		printf("Error opening file.\n");
		exit(1);
	}
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			fscanf(fp, "%d", &sudoku[i][j]);
		}
	}
	fclose(fp);
	
	printf("Here is your sudoku solution:\n");
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("Checking validity...\n");
	
	pthread_t rows[9];
	for(int i = 0; i < 9; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&rows[i], &attr, checkRows, sudoku[i]);
	}

	pthread_t columns[9];
	for(int i = 0; i < 9; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&columns[i], &attr, checkColumns, sudoku[0]+i);
	}
	
	pthread_t subgrids[9];
	int k = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_create(&subgrids[k], &attr, checkSubgrids, sudoku[3*i]+3*j);
			k++;
		}
	}

	for(int i = 0; i < 9; i++){
		pthread_join(rows[i], NULL);
		pthread_join(columns[i], NULL);
		pthread_join(subgrids[i], NULL);
	}
	
	if(flag){
		printf("Invalid Solution.\n");
	}
	else{
		printf("Valid Solution.\n");
	}
	return 0;
}
