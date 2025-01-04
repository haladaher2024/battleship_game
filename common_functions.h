#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H
void gridInitialization(char **grid);
void printgrid(char **grid);
int checkIndex(int row, int col);
int matchingIndecies(char element);
void freegrids(int** p1,int** p2);
 #endif
