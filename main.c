#include <stdio.h>
#include "main.h"

/* ------------------------------------------------
 * Guess 01 - Beat the Computer
 *
 * Class: CS 141, Fall 2015.  Tuesday 9am lab.
 * System: Windows 10, Qt Creator
 * Author: Wynn Drahorad
 *
 * ToDo: Debug initialization, beautify variable names
 * -------------------------------------------------
 */



int main(void)
{

    // variable declarations
    int userGuess; int computerForecast; int score; int lastGuess; int secondMostRecentGuess; int thirdMostRecentGuess; int turn_counter;
    int move_table[2][2][2][2] = {{{{0}}}}; // FOUR DIMENSIONAL ARRAY OMG


    score = 0;
    userGuess = 0;
    lastGuess = 0; // most recent
    secondMostRecentGuess = 0; // second most recent
    thirdMostRecentGuess = 0; // third most recent
    turn_counter = 0;

    // print header
    printf("Program #1: 0 or 1 number guessing game \nAuthor: Wynn Drahorad\nLab: Tues 9am\nInstructions:\nFor each move the computer will forecast what it thinks you will enter.\nWhen prompted you then enter 0 or 1.  The computer forecast and your\ninput will be compared.  If the computer got it right, the score is\ndecremented.  If the computer got it wrong, the score is incremented.\nThe score starts at 0.  If it reaches -10 the computer wins.\nIf it reaches 10, the human wins!  Good luck, you'll need it!");


    /* start game */

    // start game loop
    while ( score < 10 && score > -10 ) {
        // set computerForecast to most probable, using move table after turn 2
        if (turn_counter > 2) {
            computerForecast = findMostProbable(move_table, lastGuess, secondMostRecentGuess, thirdMostRecentGuess);
        } else {
            computerForecast = getRand();
        }

        // display score to user
        displayScore(score);

        // prompt user to guess 0 or 1
        do {
            userGuess = getUserGuess();
        } while (userGuess == -1); // handle inputs other than 1 or 0

        if (turn_counter > 2) {
            // add new userGuess data to prediction table
            ++move_table[lastGuess][secondMostRecentGuess][thirdMostRecentGuess][userGuess];

            printMoveTable(move_table); // uncomment this line if you want to see the move_table
        }

        if (userGuess == computerForecast) {
            --score;
        } else {
            ++score;
        }



        // store lastGuess user guesses, shift older guesses
        thirdMostRecentGuess = secondMostRecentGuess;
        secondMostRecentGuess = lastGuess;
        lastGuess = userGuess;
        ++turn_counter;
    }

    if (score > 10) {
        printf("How did you win? Congratulations! (... But seriously how?)\n");
    } else {
        printf("Sorry, you lost!\n");
    }

    return 0; // to appease the C gods
}


/* HELPER METHODS */


void displayScore(int score) {
    // Explains game, and displays score
    printf("\nOut-fox the computer! \nComputer wins if score reaches -10. \nUser wins if score reaches 10.\nCurrent score: %d\n\n", score);
}



int getUserGuess() {
    // prompts user for guess

    int guess;

    printf("Please guess 0 or 1: ");
    scanf("%d", &guess);
    if (guess != 0 && guess != 1) {
        guess = -1;
    }
    return guess;
}


int getRand() {
    // get random number 0 or 1

    int random;

    random = rand() % 2;
    return random;
}


int findMostProbable(int array[][2][2][2], int lastGuess, int secondMostRecentGuess, int thirdMostRecentGuess) {
    // finds most probable prediction

    int guess;

    int zeroCount = array[lastGuess][secondMostRecentGuess][thirdMostRecentGuess][0];
    int oneCount = array[lastGuess][secondMostRecentGuess][thirdMostRecentGuess][1];

    if (zeroCount > oneCount) {
        guess =  0;
    } else if (zeroCount < oneCount) {
        guess = 1;
    } else {
        guess = (int) !lastGuess; // return opposite of user input if counts are equal
    }

    return guess;
}


void printMoveTable(int array[2][2][2][2]) {
    // prints current tally table -- useful for debugging, and proof of concept!

    int i; int j; int k; int l;

    printf("\nLast three turns       count | 0 | 1 |\n\n");

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                printf("| %d | %d | %d |     ----->     |", k,j,i);
                for (l = 0; l < 2; l++) {
                    printf(" %d |", array[i][j][k][l]);
                }
                printf("\n");
            }
        }
    }
}
