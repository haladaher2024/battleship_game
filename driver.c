#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common_functions.c"
#include "player.c"
#include "bot.c"

#define ShipNumber 4
# define GridSize 10

int main()
{
    printf("Welcome,to battle ship");
    printf("Choose the number of players: 1 or 2.");
    int num ;
    scanf("%d",&num);
    if(num==1){
    
    srand(time(NULL));
    char **Player = (char **)malloc(sizeof(char *) * 10);
char **Bot = (char **)malloc(sizeof(char *) * 10);
     gridInitialization(Player);

    printgrid(Player);
    char mode[10];
    printf("Whaat difficulty level do you want to play(easy,hard)? ");
    scanf("%9s", mode);
    to_lowercase(mode);
    while (strcmp(mode, "easy") != 0 && strcmp(mode, "hard") != 0)
    {
        printf("Invalid input!\n");
        printf("What difficulty level do you want to play(easy,hard)? ");
        scanf("%9s", mode);
    }
    printf("please enter your name: ");
    char name1[20];
    scanf("%19s", name1);
    int randplayer = rand() % 2;
  
    char **PlayerDisplayedGrid = (char **)malloc(sizeof(char *) * 10);
    char **BotDisplayedGrid = (char **)malloc(sizeof(char *) * 10);
    gridInitialization(PlayerDisplayedGrid);
    gridInitialization(BotDisplayedGrid);


    if (randplayer == 0)
    {
        printf("%s will start the game\n", name1);
    }
    else
    {
        printf("The bot will start the game\n");
    }
//in the initialization process between bot and player there is no difference who starts first
           fillGrid(Player, name1);
    printgrid(Player);

    printf("press enter if you have finished placing your ships ");
    getchar();
    getchar();
    clearConsole(); // or system("clear");
     ShipPlacment(Bot);


    // the players' ships
    int shipPlayer[ShipNumber] = {5, 3, 4, 2};
    int shipBot[ShipNumber] = {5, 3, 4, 2};
    int *other = shipPlayer;
    int *Curr = shipBot;

    int counterSunkByPlayer = 0;


    int radarSweepsPlayer = 0;


    int flagPlayer = 0;
    //2d array to keep tarck of smoked coordinates
int **playerSmoke = (int **)malloc(GridSize * sizeof(int *));
int **BotSmoke = (int **)malloc(GridSize * sizeof(int *));
int ** RadarGrid=(int **)malloc(GridSize * sizeof(int *));
for (int i = 0; i < GridSize; i++) {
    playerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
    BotSmoke[i] = (int *)calloc(GridSize, sizeof(int));
    RadarGrid[i]=(int *)calloc(GridSize, sizeof(int));
}


int counterSunkByBot=0;

int smokeScreensUsedPlayer = 0;
int smokeScreensUsedBot = 0;


    printf("THE GAME WILL START!\n");
    int **heatmap = (int **)malloc(sizeof(int *) * 10);
    generateHeatmap(shipPlayer,heatmap,BotDisplayedGrid);

    if(randplayer==1){
        //will be changed shortly after
       botmove(Player,heatmap,BotDisplayedGrid,Curr,playerSmoke);
    }
   
    while (counterSunkByBot<4 && counterSunkByPlayer<4)
    {
        printf("\n%s this is  your opponent's current grid\n", name1);
        printgrid(PlayerDisplayedGrid);
        printf("The moves you can perform are:\n%4s\n%4s\n%4s\n%4s\n%4s", "1-Fire", "2-Radar", "3-Smoke", "4-Artillery", "5-Torpedo");
        printf("\nPlease %s , enter your command followed by the coordinate (e.g. Fire B3)\n", name1);

        char coordinate[4];
        char command[12];
        scanf("%s %s", command, coordinate);
        to_lowercase(command);

        int output;

        if (strcmp(command, "fire") == 0)
        {
            output = Fire(Bot, PlayerDisplayedGrid, coordinate, mode, other);
        }
        else if (strcmp(command, "radar") == 0)
        {       output = RadarSweep(Bot, PlayerDisplayedGrid, coordinate, radarSweepsPlayer, BotSmoke);
    if (output == 1) {
        radarSweepsPlayer++;
}}
        else if (strcmp(command, "smoke") == 0)
        {
               output = SmokeScreen(BotSmoke, coordinate, counterSunkByPlayer, smokeScreensUsedPlayer);
    if (output == 1) {
        smokeScreensUsedPlayer++;

        }}
        else if (strcmp(command, "artillery") == 0)
        {
             output = Artillery(Bot, PlayerDisplayedGrid, coordinate, mode,flagPlayer ,other);
        }
        else if (strcmp(command, "torpedo") == 0)
        {
             output=Torpedo(Bot,PlayerDisplayedGrid,coordinate,mode,other,flagPlayer,counterSunkByPlayer);
        }
        else
        {
            continue;
        }

        if (output == 1)
        {
            printf("\nThis is the updated grid\n");
            printgrid(PlayerDisplayedGrid);
            int increment = ShipsSunk(other);
            // flag to check if a ship was sunk within the current turn to unlock certain moves
            if (increment >= 1)
            {
                flagPlayer = 1;
            }
            else
            {
                flagPlayer = 0;
            }


            counterSunkByPlayer += increment;
        }
        else
        {
            printf("You have lost your turn\n");
        }

        printf("press enter to pass the turn ");
       getchar();
        getchar();
        clearConsole();

//call the bot function note will be chnaged shortly
counterSunkByBot=botmove(Player,heatmap,BotDisplayedGrid,Curr,playerSmoke);
 }
printf("The Game has ended\n");
if(counterSunkByPlayer>=4){
printf("Congratulations %s ! You have WON!!",name1);}
else{
printf("You LOST!");
}

    // Free the allocated memory 

    for (int i = 0; i < GridSize; i++)
    {
        free(Player[i]);
        free(Bot[i]);
    }
    free(Player);
    free(Bot);

    for (int i = 0; i < GridSize; i++) {
    free(playerSmoke[i]);
    free(BotSmoke[i]);
}

free(playerSmoke);
free(BotSmoke);


    }
 //start 
    else{                                                                                                                                                                   
 char **player1 = (char **)malloc(sizeof(char *) * 10);
    char **player2 = (char **)malloc(sizeof(char *) * 10);
    for (int i = 0; i < GridSize; i++)
    {
        player1[i] = (char *)malloc(sizeof(char) * GridSize);
        player2[i] = (char *)malloc(sizeof(char) * GridSize);
    }
    gridInitialization(player1);
    gridInitialization(player2);

    printgrid(player1);
    char mode[10];
    printf("What difficulty level do you want to play(easy,hard)? ");
    scanf("%9s", mode);
    to_lowercase(mode);
    while (strcmp(mode, "easy") != 0 && strcmp(mode, "hard") != 0)
    {
        printf("Invalid input!\n");
        printf("What difficulty level do you want to play(easy,hard)? ");
        scanf("%9s", mode);
    }
    printf("player 1, please enter your name: ");
    char name1[20];
    scanf("%19s", name1);
    printf("player 2, please enter your name: ");
    char name2[20];
    scanf("%19s", name2);

    srand(time(NULL));
    int randplayer = rand() % 2;
    // the names of each player
    char *currentplayerN;
    char *otherplayerN;
    // the grids of each player with their own ships
    char **currentplayerG;
    char **otherplayerG;
    // the grids that will track the moves
    // initialize the grids
    char **currentplayerD = (char **)malloc(sizeof(char *) * 10);
    char **otherplayerD = (char **)malloc(sizeof(char *) * 10);
    for (int i = 0; i < GridSize; i++)
    {
        currentplayerD[i] = (char *)malloc(sizeof(char) * GridSize);
        otherplayerD[i] = (char *)malloc(sizeof(char) * GridSize);
    }
    gridInitialization(currentplayerD);
    gridInitialization(otherplayerD);

    if (randplayer == 0)
    {
        printf("%s will start the game\n", name1);
        currentplayerN = name1;
        otherplayerN = name2;
        currentplayerG = player1;
        otherplayerG = player2;
    }
    else
    {
        printf("%s will start the game\n", name2);
        currentplayerN = name2;
        otherplayerN = name1;
        currentplayerG = player2;
        otherplayerG = player1;
    }

    fillGrid(currentplayerG, currentplayerN);
    printgrid(currentplayerG);

    printf("press enter if you have finished placing your ships ");
    getchar();
    getchar();
    clearConsole(); // or system("clear");
    printf("Now its %s turn \n ", otherplayerN);
    printgrid(otherplayerG);
    fillGrid(otherplayerG, otherplayerN);
    printgrid(otherplayerG);
   
    printf("press enter if you have finished placing your ships ");
    getchar();
    getchar();
    clearConsole();

    // the players' ships
    int shipOther[ShipNumber] = {5, 3, 4, 2};
    int shipCurr[ShipNumber] = {5, 3, 4, 2};
    int *other = shipOther;
    int *Curr = shipCurr;

    int counterSunkCurrent = 0;
    int counterSunkOther = 0;

    int radarSweepsCurrent = 0;
int radarSweepsOther = 0;

    int flagC = 0;
    int flagO = 0;
    //2d array to keep tarck of smoked coordinates
int **currentplayerSmoke = (int **)malloc(GridSize * sizeof(int *));
int **otherplayerSmoke = (int **)malloc(GridSize * sizeof(int *));
for (int i = 0; i < GridSize; i++) {
    currentplayerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
    otherplayerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
}

int shipsSunkCurrent = 0;
int shipsSunkOther = 0;

int smokeScreensUsedCurrent = 0;
int smokeScreensUsedOther = 0;


    printf("THE GAME WILL START!\n");
   
    while (counterSunkOther<4)
    {
        printf("\n%s this is  your opponent's current grid\n", currentplayerN);
        printgrid(currentplayerD);
        printf("The moves you can perform are:\n%4s\n%4s\n%4s\n%4s\n%4s", "1-Fire", "2-Radar", "3-Smoke", "4-Artillery", "5-Torpedo");
        printf("\nPlease %s , enter your command followed by the coordinate (e.g. Fire B3)\n", currentplayerN);

        char coordinate[4];
        char command[12];
        scanf("%s %s", command, coordinate);
        to_lowercase(command);

        int output;

        if (strcmp(command, "fire") == 0)
        {
            output = Fire(otherplayerG, currentplayerD, coordinate, mode, other);
        }
        else if (strcmp(command, "radar") == 0)
        {       output = RadarSweep(otherplayerG, currentplayerD, coordinate, radarSweepsCurrent, otherplayerSmoke);
    if (output == 1) {
        radarSweepsCurrent++;
}}
        else if (strcmp(command, "smoke") == 0)
        {
               output = SmokeScreen(otherplayerSmoke, coordinate, shipsSunkCurrent, smokeScreensUsedCurrent);
    if (output == 1) {
        smokeScreensUsedCurrent++;

        }}
        else if (strcmp(command, "artillery") == 0)
        {
             output = Artillery(otherplayerG, currentplayerD, coordinate, mode,flagC ,other);
        }
        else if (strcmp(command, "torpedo") == 0)
        {
             output=Torpedo(otherplayerG,currentplayerD,coordinate,mode,other,flagC,counterSunkCurrent);
        }
        else
        {
            continue;
        }

        if (output == 1)
        {
            printf("\nThis is the updated grid\n");
            printgrid(currentplayerD);
            int increment = ShipsSunk(other,&shipsSunkCurrent);
            // flag to check if a ship was sunk within the current turn to unlock certain moves
            if (increment == 1)
            {
                flagC = 1;
            }
            else
            {
                flagC = 0;
            }


            counterSunkCurrent += increment;
        }
        else
        {
            printf("You have lost your turn\n");
        }

        printf("press enter to pass the turn to the other player ");
        getchar();
        getchar();
        clearConsole();

        // switching grids
        char **tempGrid = otherplayerG;
        otherplayerG = currentplayerG;
        currentplayerG = tempGrid;

        // switching names
        char *tempName = currentplayerN;
        currentplayerN = otherplayerN;
        otherplayerN = tempName;

        // switching displayed grids
        char **tempDisplayed = currentplayerD;
        currentplayerD = otherplayerD;
        otherplayerD = tempDisplayed;
        // switching between ship Array

        int *tempS = other;
        other = Curr;
        Curr = tempS;
        // switching between counters
        int temp = counterSunkCurrent;
        counterSunkCurrent = counterSunkOther;
        counterSunkOther = temp;

        // switching bteween flags
        int FlagT = flagC;
        flagC = flagO;
        flagO = FlagT;

        // Switching radar sweeps counts
int tempRadar = radarSweepsCurrent;
radarSweepsCurrent = radarSweepsOther;
radarSweepsOther = tempRadar;

// Switching Sunksships counts
int tempShipsSunk = shipsSunkCurrent;
shipsSunkCurrent = shipsSunkOther;
shipsSunkOther = tempShipsSunk;

// Switching smoke screens 
int tempSmokeScreensUsed = smokeScreensUsedCurrent;
smokeScreensUsedCurrent = smokeScreensUsedOther;
smokeScreensUsedOther = tempSmokeScreensUsed;


    }
printf("The Game has ended\n");
printf("Congratulations %s ! You have WON!!",otherplayerN);

    // Free the allocated memory for the player grid

    for (int i = 0; i < GridSize; i++)
    {
        free(player1[i]);
        free(player2[i]);
    }
    free(player1);
    free(player2);

    for (int i = 0; i < GridSize; i++) {
    free(currentplayerSmoke[i]);
    free(otherplayerSmoke[i]);
}
free(currentplayerSmoke);
free(otherplayerSmoke);


   
}

 char **player1 = (char **)malloc(sizeof(char *) * 10);
    char **player2 = (char **)malloc(sizeof(char *) * 10);
    for (int i = 0; i < GridSize; i++)
    {
        player1[i] = (char *)malloc(sizeof(char) * GridSize);
        player2[i] = (char *)malloc(sizeof(char) * GridSize);
    }
    gridInitialization(player1);
    gridInitialization(player2);

    printgrid(player1);
    char mode[10];
    printf("What difficulty level do you want to play(easy,hard)? ");
    scanf("%9s", mode);
    to_lowercase(mode);
    while (strcmp(mode, "easy") != 0 && strcmp(mode, "hard") != 0)
    {
        printf("Invalid input!\n");
        printf("What difficulty level do you want to play(easy,hard)? ");
        scanf("%9s", mode);
    }
    printf("player 1, please enter your name: ");
    char name1[20];
    scanf("%19s", name1);
    printf("player 2, please enter your name: ");
    char name2[20];
    scanf("%19s", name2);

    srand(time(NULL));
    int randplayer = rand() % 2;
    // the names of each player
    char *currentplayerN;
    char *otherplayerN;
    // the grids of each player with their own ships
    char **currentplayerG;
    char **otherplayerG;
    // the grids that will track the moves
    // initialize the grids
    char **currentplayerD = (char **)malloc(sizeof(char *) * 10);
    char **otherplayerD = (char **)malloc(sizeof(char *) * 10);
    for (int i = 0; i < GridSize; i++)
    {
        currentplayerD[i] = (char *)malloc(sizeof(char) * GridSize);
        otherplayerD[i] = (char *)malloc(sizeof(char) * GridSize);
    }
    gridInitialization(currentplayerD);
    gridInitialization(otherplayerD);

    if (randplayer == 0)
    {
        printf("%s will start the game\n", name1);
        currentplayerN = name1;
        otherplayerN = name2;
        currentplayerG = player1;
        otherplayerG = player2;
    }
    else
    {
        printf("%s will start the game\n", name2);
        currentplayerN = name2;
        otherplayerN = name1;
        currentplayerG = player2;
        otherplayerG = player1;
    }

    fillGrid(currentplayerG, currentplayerN);
    printgrid(currentplayerG);

    printf("press enter if you have finished placing your ships ");
    getchar();
    getchar();
    clearConsole(); // or system("clear");
    printf("Now its %s turn \n ", otherplayerN);
    printgrid(otherplayerG);
    fillGrid(otherplayerG, otherplayerN);
    printgrid(otherplayerG);
   
    printf("press enter if you have finished placing your ships ");
    getchar();
    getchar();
    clearConsole();

    // the players' ships
    int shipOther[ShipNumber] = {5, 3, 4, 2};
    int shipCurr[ShipNumber] = {5, 3, 4, 2};
    int *other = shipOther;
    int *Curr = shipCurr;

    int counterSunkCurrent = 0;
    int counterSunkOther = 0;

    int radarSweepsCurrent = 0;
int radarSweepsOther = 0;

    int flagC = 0;
    int flagO = 0;
    //2d array to keep tarck of smoked coordinates
int **currentplayerSmoke = (int **)malloc(GridSize * sizeof(int *));
int **otherplayerSmoke = (int **)malloc(GridSize * sizeof(int *));
for (int i = 0; i < GridSize; i++) {
    currentplayerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
    otherplayerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
}

int shipsSunkCurrent = 0;
int shipsSunkOther = 0;

int smokeScreensUsedCurrent = 0;
int smokeScreensUsedOther = 0;


    printf("THE GAME WILL START!\n");
   
    while (counterSunkOther<4)
    {
        printf("\n%s this is  your opponent's current grid\n", currentplayerN);
        printgrid(currentplayerD);
        printf("The moves you can perform are:\n%4s\n%4s\n%4s\n%4s\n%4s", "1-Fire", "2-Radar", "3-Smoke", "4-Artillery", "5-Torpedo");
        printf("\nPlease %s , enter your command followed by the coordinate (e.g. Fire B3)\n", currentplayerN);

        char coordinate[4];
        char command[12];
        scanf("%s %s", command, coordinate);
        to_lowercase(command);

        int output;

        if (strcmp(command, "fire") == 0)
        {
            output = Fire(otherplayerG, currentplayerD, coordinate, mode, other);
        }
        else if (strcmp(command, "radar") == 0)
        {       output = RadarSweep(otherplayerG, currentplayerD, coordinate, radarSweepsCurrent, otherplayerSmoke);
    if (output == 1) {
        radarSweepsCurrent++;
}}
        else if (strcmp(command, "smoke") == 0)
        {
               output = SmokeScreen(otherplayerSmoke, coordinate, shipsSunkCurrent, smokeScreensUsedCurrent);
    if (output == 1) {
        smokeScreensUsedCurrent++;

        }}
        else if (strcmp(command, "artillery") == 0)
        {
             output = Artillery(otherplayerG, currentplayerD, coordinate, mode,flagC ,other);
        }
        else if (strcmp(command, "torpedo") == 0)
        {
             output=Torpedo(otherplayerG,currentplayerD,coordinate,mode,other,flagC,counterSunkCurrent);
        }
        else
        {
            continue;
        }

        if (output == 1)
        {
            printf("\nThis is the updated grid\n");
            printgrid(currentplayerD);
            int increment = ShipsSunk(other,&shipsSunkCurrent);
            // flag to check if a ship was sunk within the current turn to unlock certain moves
            if (increment == 1)
            {
                flagC = 1;
            }
            else
            {
                flagC = 0;
            }


            counterSunkCurrent += increment;
        }
        else
        {
            printf("You have lost your turn\n");
        }

        printf("press enter to pass the turn to the other player ");
        getchar();
        getchar();
        clearConsole();

        // switching grids
        char **tempGrid = otherplayerG;
        otherplayerG = currentplayerG;
        currentplayerG = tempGrid;

        // switching names
        char *tempName = currentplayerN;
        currentplayerN = otherplayerN;
        otherplayerN = tempName;

        // switching displayed grids
        char **tempDisplayed = currentplayerD;
        currentplayerD = otherplayerD;
        otherplayerD = tempDisplayed;
        // switching between ship Array

        int *tempS = other;
        other = Curr;
        Curr = tempS;
        // switching between counters
        int temp = counterSunkCurrent;
        counterSunkCurrent = counterSunkOther;
        counterSunkOther = temp;

        // switching bteween flags
        int FlagT = flagC;
        flagC = flagO;
        flagO = FlagT;

        // Switching radar sweeps counts
int tempRadar = radarSweepsCurrent;
radarSweepsCurrent = radarSweepsOther;
radarSweepsOther = tempRadar;

// Switching Sunksships counts
int tempShipsSunk = shipsSunkCurrent;
shipsSunkCurrent = shipsSunkOther;
shipsSunkOther = tempShipsSunk;

// Switching smoke screens 
int tempSmokeScreensUsed = smokeScreensUsedCurrent;
smokeScreensUsedCurrent = smokeScreensUsedOther;
smokeScreensUsedOther = tempSmokeScreensUsed;


    }
printf("The Game has ended\n");
printf("Congratulations %s ! You have WON!!",otherplayerN);

    // Free the allocated memory for the player grid

    for (int i = 0; i < GridSize; i++)
    {
        free(player1[i]);
        free(player2[i]);
    }
    free(player1);
    free(player2);

    for (int i = 0; i < GridSize; i++) {
    free(currentplayerSmoke[i]);
    free(otherplayerSmoke[i]);
}
free(currentplayerSmoke);
free(otherplayerSmoke);


    return 0;
}






}

