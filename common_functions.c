#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common_functions.h"

#define GridSize 10
#define ShipNumber 4

void gridInitialization(char **grid)
{
    for (int i = 0; i < 10; i++)
    {
        grid[i] = (char *)malloc(GridSize * sizeof(char));
    }
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < 10; k++)
        {

            grid[j][k] = '~';
        }
    }
}

void printgrid(char **grid)
{
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    printf("    ");
    for (int o = 0; o < 10; o++)
    {
        printf("%c ", letters[o]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%2d  ", i + 1);
        for (int j = 0; j < 10; j++)
        {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

int checkIndex(int row, int col)
{
    if (col >= GridSize || col < 0 || row >= GridSize || row < 0)
    {
        return 0;
    }
    return 1;
}

int matchingIndecies(char element)
{
    switch (element)
    {
    case 'C':
        return 0;
    case 'd':
        return 1;
    case 'B':
        return 2;
    case 's':
        return 3;

    default:
        return -1;
        break;
    }
}
void freegrids(char **p1, char **p2)
{
    for (int i = 0; i < GridSize; i++)
    {
        free(p1[i]);
        free(p2[i]);
    }
    free(p1);
    free(p2);
}
void freegridsInt(int **p1)
{
    for (int i = 0; i < GridSize; i++)
    {
        free(p1[i]);
    }
    free(p1);
}

void flagSetter(int *counter, int increment, int* flag, char **grid, int output)
{
    if (output == 1)
    {
        printf("\nThis is the updated grid\n");
        printgrid(grid);
        if (increment >= 1)
        {
            *flag=1;
        }
        else
        {
        *flag = 0;
        }
       (* counter )+= increment;
      
    }
    else
    {
        printf("You have lost your turn\n");
    }

    printf("press enter to pass the turn ");
    getchar();
    getchar();
    clearConsole();
}
void clearConsole()
{
    printf("\033[H\033[J");
}
