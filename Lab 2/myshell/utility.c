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

// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

extern void changeDir(char args[10][256], int numTok){
    char *path = args[1];
    if(numTok == 1){
        printf("%s\n", getenv("PWD"));
    }
    else if(numTok > 2){
        printf("Invalid input. See help file.\n");
    }
    else{
        printf("Current working dir:%s\n", getenv(path));
        int r = chdir(path);
        setenv("PWD", path, 2);
        if(r != 0){
            printf("Couldn't change directory.\n");
        }
    }
}

extern void showDir(char args[10][256], int numTok){
    if (numTok != 2){
        struct dirent *dptr;
        DIR *dp;
        dp = opendir(getenv("PWD"));
        if (dp == NULL){
            printf("Cannot open dir '%s'\n", args[1]);
        }
        while ((dptr = readdir(dp)) != NULL){
            printf("[%s]\n", dptr->d_name);
        }
        closedir(dp);
    }
    else{
        struct dirent *dptr;
        DIR *dp;
        dp = opendir(args[1]);
        if (dp == NULL){
            printf("Cannot open dir '%s'\n", args[1]);
        }
        while ((dptr = readdir(dp)) != NULL){
            printf("[%s]\n", dptr->d_name);
        }
        closedir(dp);
    }
}

extern void environment(){
    extern char **environ;
    int i = 0;
    while (environ[i]){
        printf("%s\n", environ[i++]);
    }
}

extern void echo(char args[10][256], int numTok){
    int i = 1;
    while (i < numTok){
        printf("%s\n", args[i]);
        ++i;
    }
}

extern void help(){
    int c;
    FILE *file;
    file = fopen("README.md", "r");
    if (file){
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
}

extern void pauseOps(){
    printf("Paused. Press 'Enter' to resume...\n");
    char c;
    while (c != '\r' && c != '\n'){
        c = getchar();
    }
    printf("Resuming\n");
}

extern void exec(char args[10][256], int numTok){
    if(numTok != 2){
        printf("Usage: myshell [batchfile] \n");
    }
    else{
        FILE *fp;
        char line[256], command[256];
        char arguements[5][256];
        char *token;
        fp = fopen(args[1], "r");

        while(fgets(line, 256, fp) != 0){
            numTok = 0;
            for(token = strtok(line, " \n\0\r"); NULL != token; token = strtok(NULL, " \n\0\r")){
                if(numTok == 0){
                    strcpy(command, token);
                    printf("Command:%s\n", command);
                }
                else{
                    strcpy(arguements[numTok], token);
                    printf("Arguement:%s\n", arguements[numTok]);
                }
                ++numTok;
            }
            commands(command, arguements, numTok);
        }
        fclose(fp);
        free(token);
    }
}

int outputCommand(char command[256], char args[10][256], int numTok){
    // cd command -- change directory
    if(strcmp(command, "cd") == 0){
        changeDir(args, numTok);
    }
    // clr command -- clear the screen
    else if(strcmp(command, "clr") == 0){
        system("clear||clr");
    }
    // dir command -- lists content of the directory <directory>
    else if(strcmp(command, "dir") == 0){
        showDir(args, numTok);
    }
    // environ command -- lists all environment strings
    else if(strcmp(command, "environ") == 0){
        environment();
    }
    // echo command -- displays user entered comment
    else if(strcmp(command, "echo") == 0){
        echo(args, numTok);
    }
    // help command -- displays user manual
    else if(strcmp(command, "help") == 0){
        help();
    }
    // pause command -- pauses operation unitl 'Enter' is pressed
    else if(strcmp(command, "pause") == 0){
        pauseOps();
    }
    // quit command -- exit the shell
    else if(strcmp(command, "quit") == 0){
        return 1;
    }
     // exec - executes the commands
    else if(strcmp(command, "exec") == 0){
        exec(args, numTok);
    }
    // Unsupported command
    else{
        fputs("Unsupported command, use help to display the manual.\n", stderr);
    }
    //printf("returns");
    return 0;
}

extern int commands(char command[256], char args[10][256], int numTok){
    // Check the command and execute the operations for each command
    // cd command -- change the current directory


    for (int i = 0; i < numTok; i++){
        if (strcmp(args[i], "<") == 0){
            freopen(args[i+1], "r", stdin);
            fclose(stdin);
            return 0;
        }
        else if (strcmp(args[i], ">") == 0){
            freopen(args[i+1], "w", stdout);
            outputCommand(command, args, numTok);
            fclose(stdout);
            return 0;
        }
        else if (strcmp(args[i], ">>") == 0){
            freopen(args[i+1], "a", stdout);
            outputCommand(command, args, numTok);
            fclose(stdout);
            return 0;
        }

    }

    int out = outputCommand(command, args, numTok);
    return out;
}
