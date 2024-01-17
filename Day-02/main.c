// includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// defines
#define INPUT_FILE "input.txt"

// function prototypes
int strategy1(char, char);
int strategy2(char, char);

// main
int main() {
    // local variables
    int score1 = 0, score2 = 0;
    char opponent, player;

    FILE* fstream = fopen(INPUT_FILE, "r");

    if (fstream == NULL) {
        printf("Couldn't open the file %s\n", INPUT_FILE);
        return -1;
    }

    while (fscanf(fstream, "%c %c\n", &opponent, &player) == 2) {
        score1 += strategy1(opponent, player);
        score2 += strategy2(opponent, player);
    }

    printf("Your total score using the first strategy is %d\n", score1);
    printf("Your total score using the second strategy is %d\n", score2);

    return 0;
}

int strategy1(char opponent, char player) {
    // local variables
    int score = 0;

    // do funny thing
    opponent -= '@';
    player -= 'W';

    // check for win or draw
    if (player == (opponent % 3) + 1)
        score += 6;
    else if (player == opponent)
        score += 3;

    // add score for chosen 'weapon'
    score += player;
    return score;
}

int strategy2(char opponent, char player) {
    // local variables
    int score = 0;

    // calculate score
    switch(player) {
        // lose
        case 'X':
            score = 1 + opponent % 3; // takes previous in rotation: rock, paper, scissors
            break;
        // draw
        case 'Y':
            score = 4 + (opponent + 1) % 3; // takes same in rotation: rock, paper, scissors and adds 3
            break;
        // win
        case 'Z':
            score = 7 + (opponent + 2) % 3; // takes next in rotation: rock, paper, scissors and adds 6
            break;
        default:
            break;
    }

    return score;
}