/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"
#include <unistd.h>
//#include <curses.h> need to install

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here
extern char **environ;

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    unsigned long i;
    char path[1024];
    // Parse the commands provided using argc and argv
    if (getcwd(path, sizeof(path)) != NULL){
	char com[1024]= {"shell="};
	char str[2048]= {};
	char myshell[1024] ={"/myshell"};	
	strcat(str,com);
	strcat(str,path);
	strcat(str,myshell);
 	putenv(str);
	}
    // Perform an infinite loop getting command input from users
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
       	//fprintf(stdout, "%s\n", cwd);
	printf("%s:$ ", cwd);
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
       	//fprintf(stdout, "%s\n", cwd);
	printf("%s\n", cwd);
        // Perform string tokenization to get the command and argument
	char* token = strtok(buffer, " \n");
	for (i=0; i < sizeof(buffer);i++){
		command[i] = token[i];
	}
	token = strtok(NULL," \n");
	if (token != NULL){
		for (i=0; i < sizeof(buffer);i++){
		arg[i] = token[i];
		}
	}
	printf("command = %s\n",command);
	printf("arg = %s\n",arg);
	
        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
		if(strcmp(arg, "") == 0){
			if (getcwd(cwd, sizeof(cwd)) != NULL)
       				fprintf(stdout, "Current working dir: %s\n", cwd);
				
		}
		
		else{
			int result = 0;
			result = chdir(arg);
  			if(result == 0){
    				if (getcwd(cwd, sizeof(cwd)) != NULL)
       					fprintf(stdout, "Current working dir: %s\n", cwd);

			}
  
  			else{
    				 printf("Couldn't change directory to %s\n", arg ); 
    			}
  		}	
        }
	else if (strcmp(command,"clr") == 0){
		/*initscr(); 
		clear();
		refresh();
		endwin();*/
		//above not working proper and uses curses
		int n;
    		for (n = 0; n < 10; n++)
      			printf( "\n\n\n\n\n\n\n\n\n\n" );
	}
	else if (strcmp(command,"environ") == 0){
		int i = 1;
  		char *s = *environ;
  		for (; s; i++) {
    			printf("%s\n", s);
    			s = *(environ+i);
  		}
	}
	else if (strcmp(command,"echo") == 0){
		char* string = strtok(NULL, "\n");
		printf("%s %s\n",arg,string);
	}
	
	else if (strcmp(command,"help") == 0)
	{
		int c;
		FILE *file;
		file = fopen("README","r");
		if (file){
			while((c=getc(file)) !=EOF)
				putchar(c);
			fclose(file);		
		}
	}

        // other commands here...
        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
	memset(command,0,255);
	memset(arg,0,255);
	getcwd(cwd, sizeof(cwd));
       	//fprintf(stdout, "%s\n", cwd);
	printf("%s$ ", cwd);
    }
    return EXIT_SUCCESS;
}
