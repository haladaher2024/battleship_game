#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H
void gridInitialization(char **grid);
void printgrid(char **grid);
int checkIndex(int row, int col);
int matchingIndecies(char element);
void freegrids(char** p1,char** p2);
void freegridsInt(int** p1);
void flagSetter(int *counter, int increment, int *flag, char **grid, int output);
void clearConsole();
 #endif
