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
#include <sys/stat.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here
char args[10][256];

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    int errorCode;

	// Parse the commands provided using argc and argv
    int i;
	char *myshell = getenv("PWD");
	setenv("PWD", myshell, 2);
	strcat(myshell, "/myshell");
	setenv("SHELL", myshell, 1);

	for (i = 0; i < argc; ++i){
		printf("\n");
		strcpy(command, argv[i]);
	}
	
    // Perform an infinite loop getting command input from users
    while (printf("%s: ", getenv("PWD")), fgets(buffer, BUFFER_LEN, stdin) != NULL){
        // Perform string tokenization to get the command and argument
		strcpy(arg, buffer);
		int numTok = 0;
		char *token = NULL;

		for (token = strtok(buffer, " \n\0\r"); NULL != token; token = strtok(NULL, " \n\0\r")){
			if (numTok == 0){
				strcpy(command, token);
				printf("Command:%s\n", command);
			}
			else{
				strcpy(args[numTok], token);
				printf("Arguement:%s\n", args[numTok]);
			}
			++numTok;
		}

		// Send commands to be executed
		errorCode = commands(command, args, numTok);
		if (errorCode == 1){
			break;
		}
		if (errorCode == -1){
			printf("Error");
			exit(1);
		}
	}
	return EXIT_SUCCESS;
}
