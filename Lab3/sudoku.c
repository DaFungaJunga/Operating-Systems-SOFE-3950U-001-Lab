#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int dup = 0;
// integer updates to 1 if there is a duplicate number in the col,row,subgrid.
// 0 if there is no duplicate.

// Checks for a duplicate number in the test array inserted. will update dup if there is one.
void checkDuplicate(int array[]){
	for(int i = 0; i < 9 && !dup; i++){
		for(int j = i+1; j < 9 && !dup; j++){
			if(array[i] == array[j]){
				dup = 1;
				break;
			}
		}
	}
}

// Creates a temporary arrays of the rows to be checked. Calls checkDuplicate and exits the thread.
void* checkRows(void* arg)
{
	int *temp_pointer = (int*)arg;
	int temp = *temp_pointer;
	int tempArray[9];

	tempArray[0] = temp;
	for(int j = 1; j < 9; j++){
		temp = *(++temp_pointer);
		tempArray[j] = temp;
	}

	checkDuplicate(tempArray);
	pthread_exit(0);
}

// Creates a temporary arrays of the columns to be checked. Calls checkDuplicate and exits the thread.
void* checkColumns(void* arg){
	int *temp_pointer = (int*)arg;
	int temp = *temp_pointer;
	int tempArray[9];

	tempArray[0] = temp;
	for(int i = 1; i < 9; i++){
		temp = *((9*i)+temp_pointer);
		tempArray[i] = temp;
	}
	
	checkDuplicate(tempArray);
	pthread_exit(0);
}

// Creates a temporary arrays of the subgrids to be checked. Calls checkDuplicate and exits the thread.
void* checkSubgrids(void* arg){
	int *temp_pointer = (int*)arg;
	int temp = *temp_pointer;
	int tempArray[9];

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			temp = *(temp_pointer++);
			tempArray[j + 3*i] = temp;
		}
		for(int k = 0; k < 6; k++){
			temp = *(++temp_pointer);
		}
	}

	checkDuplicate(tempArray);
	pthread_exit(0);
}

// main function
int main(void){
	int sudoku[9][9]; // creates a 2D array for the sudoku matrix
	FILE *fp;
	int i, j;
	
	// open txt file and store the matrix in the sudoku array. Error checks file open functions
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
	fclose(fp); // close file
	
	// print aquires sudoku matrix in the terminal
	printf("Here is your sudoku solution:\n");
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("Checking validity...\n");
	
	// Creates 9 threads to check each row in the sudoku array using checkRows function.
	pthread_t rows[9];
	for(int i = 0; i < 9; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&rows[i], &attr, checkRows, sudoku[i]);
	}

	// Creates 9 threads to check each column in the sudoku array using checkColumns function.
	pthread_t columns[9];
	for(int i = 0; i < 9; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&columns[i], &attr, checkColumns, sudoku[0]+i);
	}
	
	// Creates 9 threads to check each subgrid in the sudoku array using checkSubgrids function.
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

	// performs a join of all 27 row, column, and subgrid threads
	for(int i = 0; i < 9; i++){
		pthread_join(rows[i], NULL);
		pthread_join(columns[i], NULL);
		pthread_join(subgrids[i], NULL);
	}
	
	// prints invalid or valid depending on status of dup integer
	if(dup == 0){
		printf("Valid Solution.\n");
	}
	else{
		printf("Invalid Solution.\n");
	}
	return 0;
}
