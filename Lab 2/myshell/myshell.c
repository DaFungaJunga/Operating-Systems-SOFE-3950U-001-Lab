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

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    unsigned long i;

    // Parse the commands provided using argc and argv
	
    // Perform an infinite loop getting command input from users

    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
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
		char cwd[1024];
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
    }
    return EXIT_SUCCESS;
}
