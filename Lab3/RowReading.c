
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define MAXCHAR 1000

void* CheckRow()
{
    char str[MAXCHAR];
    	int counter=0;
    FILE *ofile;
	  ofile = fopen("puzzle.txt","r");
      if(ofile == NULL)
      {
          printf("File is out of reach");
          exit(0);
      }// read line by lien
       while (fgets(str, MAXCHAR, ofile) != NULL)
            { // this is to test if each line has
            // the the full set of numbers
       // printf("%s", str);
	// checking the numbers.
	if (strstr(str, "1") != NULL) 
	   counter++;
	if (strstr(str, "2") != NULL) 
		   counter++;
	if (strstr(str, "3") != NULL) 
	   counter++;
	if (strstr(str, "4") != NULL) 
	   counter++;
	if (strstr(str, "5") != NULL) 
	   counter++;
	if (strstr(str, "6") != NULL) 
	   counter++;
	if (strstr(str, "7") != NULL) 
	   counter++;
	if (strstr(str, "8") != NULL) 
	   counter++;
	if (strstr(str, "9") != NULL) 
	   counter++;
	
	
            }
fclose(ofile);
if(counter== 81)
printf("all lines contain numbers from one to nine\n");
else
{
    printf("the given valus are invalid soloution");
}
pthread_exit(0);
}

int main(void)
{

// the method will test if the numbers from 1 to 9 are in all lines by counter the existence of the occurance in each line. A successsful soultion should have a count of 81. (9 numbers in each lines * 9 lines)
pthread_t tid[0];

    int createThreadTwo = pthread_create(&tid[0],NULL,CheckRow,NULL);
    pthread_join(tid[0],NULL);
//CheckRow();


}

