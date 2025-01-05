#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common_functions.c"
#include "player.c"
#include "bot.c"

#define ShipNumber 4
#define GridSize 10

int main()
{
    // Setting the game
    srand(time(NULL));
    printf("Welcome,to battle ship");
    printf("Choose the number of players (1 or 2) : ");
    int num;
    scanf("%d", &num);

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

    char **Player = (char **)malloc(sizeof(char *) * 10);
    gridInitialization(Player);
    char **BotOrPlayer2 = (char **)malloc(sizeof(char *) * 10);

    // the ships of the players
    int shipPlayer[ShipNumber] = {5, 3, 4, 2};
    int ShipBotOrPlayer2[ShipNumber] = {5, 3, 4, 2};
    int *other = shipPlayer;
    int *Curr = ShipBotOrPlayer2;

    // the grids that will be displayed and track the moves
    char **PlayerDisplayedGrid = (char **)malloc(sizeof(char *) * 10);
    char **BotOrPlayer2DisplayedGrid = (char **)malloc(sizeof(char *) * 10);
    gridInitialization(PlayerDisplayedGrid);
    gridInitialization(BotOrPlayer2DisplayedGrid);

    // common counters/flags between both modes(bot/players)
    int counterSunkByPlayer = 0;
    int counterSunkByBotORPlayer2 = 0;
    int flagPlayer = 0;
    int output;

    // The Bot mode was chosen
    if (num == 1)
    {
        printf("please enter your name: ");
        char name1[20];
        scanf("%19s", name1);
        int randplayer = rand() % 2;

        if (randplayer == 0)
        {
            printf("%s will start the game\n", name1);
        }
        else
        {
            printf("The bot will start the game\n");
        }

        // in the initialization process between bot and player there is no difference who starts first
        fillGrid(Player, name1);
        printgrid(Player);

        printf("press enter if you have finished placing your ships ");
        getchar();
        getchar();
        clearConsole(); // or system("clear");
        ShipPlacment(BotOrPlayer2);

        printf("THE GAME WILL START!\n");
        
        int **heatmap = (int **)malloc(sizeof(int *) * 10);
        generateHeatmap(shipPlayer, heatmap, BotOrPlayer2DisplayedGrid);

        if (randplayer == 1)
        {
            // the bot will start
            botmove(Player, heatmap, BotOrPlayer2DisplayedGrid, Curr);
        }

        while (counterSunkByBotORPlayer2 < 4 && counterSunkByPlayer < 4)
        {
            printf("\n%s this is  your opponent's current grid\n", name1);
            printgrid(PlayerDisplayedGrid);
            printf("The moves you can perform are:\n%4s\n%4s\n%4s\n", "1-Fire", "2-Artillery", "3-Torpedo");
            printf("\nPlease %s , enter your command followed by the coordinate (e.g. Fire B3)\n", name1);

            char coordinate[4];
            char command[12];
            scanf("%s %s", command, coordinate);
            to_lowercase(command);

            if (strcmp(command, "fire") == 0)
            {
                output = Fire(BotOrPlayer2, PlayerDisplayedGrid, coordinate, mode, other);
            }

            else if (strcmp(command, "artillery") == 0)
            {
                output = Artillery(BotOrPlayer2, PlayerDisplayedGrid, coordinate, mode, flagPlayer, other);
            }
            else if (strcmp(command, "torpedo") == 0)
            {
                output = Torpedo(BotOrPlayer2, PlayerDisplayedGrid, coordinate, mode, other, flagPlayer, counterSunkByPlayer);
            }
            else
            {
                continue;
            }

            // flag to check if a ship was sunk within the current turn to unlock certain moves
            flagSetter(&counterSunkByPlayer, ShipsSunk(other), &flagPlayer, PlayerDisplayedGrid, output);

            // call the bot function bot
            counterSunkByBotORPlayer2 = botmove(Player, heatmap, BotOrPlayer2DisplayedGrid, Curr);
        }
        printf("The Game has ended\n");
        if (counterSunkByPlayer >= 4)
        {
            printf("Congratulations %s ! You have WON!!", name1);
        }
        else
        {
            printf("You LOST!");
        }
        freegridsInt(heatmap);
    }

    // In Case We Have 2 Players
    else
    {

        gridInitialization(BotOrPlayer2);
        printf("player 1, please enter your name: ");
        char name1[20];
        scanf("%19s", name1);
        printf("player 2, please enter your name: ");
        char name2[20];
        scanf("%19s", name2);

        int randplayer = rand() % 2;
        // the names of each player
        char *currentplayerN;
        char *otherplayerN;
        // the grids of each player with their own ships
        char **currentplayerG;
        char **otherplayerG;

        if (randplayer == 0)
        {
            printf("%s will start the game\n", name1);
            currentplayerN = name1;
            otherplayerN = name2;
            currentplayerG = Player;
            otherplayerG = BotOrPlayer2;
        }
        else
        {
            printf("%s will start the game\n", name2);
            currentplayerN = name2;
            otherplayerN = name1;
            currentplayerG = BotOrPlayer2;
            otherplayerG = Player;
        }

        fillGrid(currentplayerG, currentplayerN);
        printgrid(currentplayerG);

        printf("press enter if you have finished placing your ships ");
        getchar();
        getchar();
        clearConsole(); // or system("clear");
        printf("Now its %s turn \n ", otherplayerN);
        fillGrid(otherplayerG, otherplayerN);
        printgrid(otherplayerG);

        printf("press enter if you have finished placing your ships ");
        getchar();
        getchar();
        clearConsole();
//flags that will help in switching between players
        int radarSweepsCurrent = 0;
        int radarSweepsOther = 0;
        int shipsSunkCurrent = 0;
        int shipsSunkOther = 0;
        int smokeScreensUsedCurrent = 0;
        int smokeScreensUsedOther = 0;
        int flagO = 0;//flage for player 1 was initilized as a common flag 

        // 2d array to keep tarck of smoked coordinates
        int **currentplayerSmoke = (int **)malloc(GridSize * sizeof(int *));
        int **otherplayerSmoke = (int **)malloc(GridSize * sizeof(int *));
        for (int i = 0; i < GridSize; i++)
        {
            currentplayerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
            otherplayerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
        }


        printf("THE GAME WILL START!\n");

        while (counterSunkByBotORPlayer2 < 4)
        {
            printf("\n%s this is  your opponent's current grid\n", currentplayerN);
            printgrid(PlayerDisplayedGrid);
            printf("The moves you can perform are:\n%4s\n%4s\n%4s\n%4s\n%4s", "1-Fire", "2-Radar", "3-Smoke", "4-Artillery", "5-Torpedo");
            printf("\nPlease %s , enter your command followed by the coordinate (e.g. Fire B3)\n", currentplayerN);

            char coordinate[4];
            char command[12];
            scanf("%s %s", command, coordinate);
            to_lowercase(command);

            if (strcmp(command, "fire") == 0)
            {
                output = Fire(otherplayerG, PlayerDisplayedGrid, coordinate, mode, other);
            }
            else if (strcmp(command, "radar") == 0)
            {
                output = RadarSweep(otherplayerG, PlayerDisplayedGrid, coordinate, radarSweepsCurrent, otherplayerSmoke);
                if (output == 1)
                {
                    radarSweepsCurrent++;
                }
            }
            else if (strcmp(command, "smoke") == 0)
            {
                output = SmokeScreen(otherplayerSmoke, coordinate, shipsSunkCurrent, smokeScreensUsedCurrent);
                if (output == 1)
                {
                    smokeScreensUsedCurrent++;
                }
            }
            else if (strcmp(command, "artillery") == 0)
            {
                output = Artillery(otherplayerG, PlayerDisplayedGrid, coordinate, mode, flagPlayer, other);
            }
            else if (strcmp(command, "torpedo") == 0)
            {
                output = Torpedo(otherplayerG, PlayerDisplayedGrid, coordinate, mode, other, flagPlayer, counterSunkByPlayer);
            }
            else
            {
                continue;
            }

            // flag to check if a ship was sunk within the current turn to unlock certain moves
            printf("flag Before:%d  counter Before: %d",flagPlayer,counterSunkByPlayer);
            flagSetter(&counterSunkByPlayer, ShipsSunk(other), &flagPlayer, PlayerDisplayedGrid, output);
                printf("\nflag After:%d  counter After: %d",flagPlayer,counterSunkByPlayer);

            // switching grids
            char **tempGrid = otherplayerG;
            otherplayerG = currentplayerG;
            currentplayerG = tempGrid;

            // switching names
            char *tempName = currentplayerN;
            currentplayerN = otherplayerN;
            otherplayerN = tempName;

            // switching displayed grids
            char **tempDisplayed = PlayerDisplayedGrid;
            PlayerDisplayedGrid = BotOrPlayer2DisplayedGrid;
            BotOrPlayer2DisplayedGrid = tempDisplayed;
            // switching between ship Array

            int *tempS = other;
            other = Curr;
            Curr = tempS;
            // switching between counters
            int temp = counterSunkByPlayer;
            counterSunkByPlayer = counterSunkByBotORPlayer2;
            counterSunkByBotORPlayer2 = temp;

            // switching bteween flags
            int FlagT = flagPlayer;
            flagPlayer = flagO;
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
        printf("Congratulations %s ! You have WON!!", otherplayerN);

        // Free the allocated memory for the player grid
        freegridsInt(currentplayerSmoke);
        freegridsInt(otherplayerSmoke);
        freegrids(currentplayerG,otherplayerG);
    }

    freegrids(Player, BotOrPlayer2);
    freegrids(PlayerDisplayedGrid,BotOrPlayer2DisplayedGrid);

    return 0;
}
