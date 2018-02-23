/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_

// Include your relevant functions declarations here they must start with the 
// extern keyword such as in the following example:
// extern void display_help(void);

extern void changeDir(char args[10][256], int numTok);
extern void showDir(char args[10][256], int numTok);
extern void environment();
extern void echo(char args[10][256], int numTok);
extern void help();
extern void pauseOps();
extern void exec(char args[10][256], int numTok);
extern int commands(char command[256], char args[10][256], int numTok);
extern int setenv(const char *envname, const char *envval, int overwrite);

#endif /* UTILITY_H_ */
