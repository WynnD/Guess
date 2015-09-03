#include <stdio.h>

/* ------------------------------------------------
 * Basic Calculator with + - / *
 *
 * Class: CS 141, Fall 2015.  Tuesday 9am lab.
 * System: Windows 10, Qt Creator
 * Author: Wynn Drahorad
 *
 * ToDo: Store previous guesses in an arrays
 * -------------------------------------------------
 */



int main(void)
{
    // print header
    printf("Author: Wynn Drahorad\nLab: Tues 9am\nProgram #1: Guess01\n");

    // variable declarations
    int userGuess; int forecast; int score; int last; int last1; int last2;
    int move_table[2][2][2][2] = {{{{0}}}}; // FOUR DIMENSIONAL ARRAY OMG

    /*
     * int when0[2] = {0};
     * int when1[2] = {0};
    */

    score = 0;
    userGuess = 0;
    last = 0; // most recent
    last1 = 0; // second most recent
    last2 = 0; // third most recent
    forecast = getRand();


    /* start game */

    // start game loop
    while (score < 10 && score > -10) {

        // set forecast to most probable
        forecast = mostProb(move_table, last, last1, last2);

        // display score to user
        displayScore(score);

        // prompt user to guess 0 or 1
        do {
            userGuess = getUserGuess();
        } while (userGuess == -1); // handle inputs other than 1 or 0

        // print total table (used for debugging)
        print_table(move_table);

        if (userGuess == forecast) {
            --score;
        } else {
            ++score;
        }

        // add userGuess data to prediction table
        move_table[last][last1][last2][userGuess]++;

        // store last user guesses, shift older guesses
        last2 = last1;
        last1 = last;
        last = userGuess;
    }
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


int mostProb(int array[][2][2][2], int last, int last1, int last2) {
    // finds most probable prediction

    int guess;

    int zeroCount = array[last][last1][last2][0];
    int oneCount = array[last][last1][last2][1];

    if (zeroCount > oneCount) {
        guess =  0;
    } else if (zeroCount < oneCount) {
        guess = 1;
    } else {
        guess = (int) !last; // return opposite of user input if counts are equal
    }

    return guess;
}


void print_table(int array[2][2][2][2]) {
    // prints current tally table -- useful for debugging, and proof of concept!

    int i; int j; int k; int l;

    printf("\nLast three turns       count | 0 | 1 |\n\n");

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                printf("| %d | %d | %d |     ----->     |", i,j,k);
                for (l = 0; l < 2; l++) {
                    printf(" %d |", array[i][j][k][l]);
                }
                printf("\n");
            }
        }
    }
}
