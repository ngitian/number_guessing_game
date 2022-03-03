/* Yitian Huang, system programming, 02/28/2022
print menu, read and run different inputs
1-start a game
    prompt user input, if correct, go back to menu, else
    tell user too high or too low. if enter q, return to menu.
    keep track of nubmer of guesses.
2-change max number
3-quit
    thanks user for playing
    print out number of guesses required to win
    if quit game, indicate lost game
    end game
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// prototype
void endGame(int gameCounter, const bool* gameResult, const int* gameData);
int changeMaxNumber(int maxNumber);
void startGame(int maxNumber, int gameCounter, bool* gameResult, int* gameData, int *arraySize);

int main() 
{
    // initialize menu prompt
    const char MENU[] = "\nPress 1 to play a game\nPress 2 to change the max number\nPress 3 to quit\n";

    // initialize game loop condition
    bool playing = true;

    // initialize user menu input, and information and data about game
    char menuInput[5];
    int maxNumber = 10;
    int gameCounter = 0;
    bool* gameResult = malloc(50 * sizeof(bool));
    int* gameData = malloc(50 * sizeof(int));
    int arraySize = 50;

    // check whether malloc is successful
    if (gameResult == NULL || gameData == NULL)
    {
        printf("Error: unable to allocate required memory\n");
        playing = false;
    }

    // start game loop
    while (playing)
    {
        // prompt menu and user input
        printf("%s", MENU);
        printf("Enter input: ");
        scanf("%s", menuInput);
        printf("\n");

        // run different options depends on the menu input
        if (strcmp(menuInput,"1") == 0)
        {
            startGame(maxNumber, gameCounter, gameResult, gameData, &arraySize);
            ++gameCounter;
        } 
        else if (strcmp(menuInput,"2") == 0)
        {
            maxNumber = changeMaxNumber(maxNumber);
        }
        else if (strcmp(menuInput,"3") == 0)
        {
            endGame(gameCounter, gameResult, gameData);
            playing = false;
        }
        else
        {
            printf("Incorrect Input\n");
        }

    }

    // garbage collection
    free(gameResult);
    free(gameData);
    
    return 0;

}

void startGame(int maxNumber, int gameCounter, bool* gameResult, int* gameData, int *arraySize)
{
    // initialize target number
    time_t t;
    srand((unsigned) time(&t));
    int target = rand() % (maxNumber - 1) + 1;
    
    // start guessing game loop
    bool guessing = true;
    int roundsCounter = 0;
    char userGuess[5];

    while(guessing)
    {
        // increment round counter
        ++roundsCounter;

        // user input guess
        printf("Guess a number between 1 and %d: ", maxNumber);
        scanf("%s", userGuess);

        // evaluate user input with target
        // if q, game lost, and exit function
        // if correct, game win, and exit function
        // if incorrect, output either low or high
        if (strcmp(userGuess, "q") == 0)
        {
            // game lost
            guessing = false;
            gameResult[gameCounter] = false;
        }
        else if (strtol(userGuess, NULL, 10) == target)
        {
            printf("Guess is correct!\n");
            guessing = false;
            gameResult[gameCounter] = true;
        }
        else if (strtol(userGuess, NULL, 10) < target)
        {
            printf("Guess is too low\n");
        }
        else if (strtol(userGuess, NULL, 10) > target)
        {
            printf("Guess is too high\n");
        }
        else
        {
            printf("Invalid input\n");
        }


    }

    // realloc if gameData and gameResult can't hold anymore memory
    if (*arraySize <= gameCounter)
    {
        *arraySize *= 2;
        gameData = realloc(gameData, *arraySize * sizeof(int));
        gameResult = realloc(gameResult, *arraySize * sizeof(bool));

        if (gameResult == NULL || gameData == NULL)
        {
            printf("Error: unable to allocate required memory\n");
            exit(0);
        }

    }
    // process information for gameData
    gameData[gameCounter] = roundsCounter;

}

int changeMaxNumber(int maxNumber)
{
    int result = -1;
    char input[10];
    while (result <= 1 || result > maxNumber)
    {
        printf("Enter a new max number > 1 and <= %d: ", maxNumber);
        scanf("%s", input);
        if (strtol(input, NULL, 10) <= 1)
        {
            printf("Max number can not be less than min number or has to be a number\n");
        }
        else if (strtol(input, NULL, 10) > maxNumber)
        {
            printf("Max number can not exceed previous max number or has to be a number\n");
        }
        else
        {
            result = strtol(input, NULL, 10);
        }
    }
    return result;

}

void endGame(int gameCounter, const bool* gameResult, const int* gameData)
{
    // thank the player
    printf("Thanks for playing number guessing game\n");

    // output result
    for (int i = 0; i < gameCounter; ++i)
    {
        printf("game %d: ", i + 1);
        if (gameResult[i])
        {
            printf("win");
        }
        else
        {
            printf("lose");
        }
        printf(" with %d rounds\n", gameData[i]);
    }

}