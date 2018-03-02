#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
int puzzleArray[9][9];
int main(void){
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

