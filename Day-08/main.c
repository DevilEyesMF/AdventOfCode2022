// includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// defines
#define INPUT_FILE "input.txt"
#define MAX_COUNT 128

// function prototypes
int getNumRows(FILE*);
int calculateVisibleTrees(char**, int, int);
int calculateHighestScenicScore(char**, int, int);

// main
int main() {
    int numRows, numCols, visibleTrees, highestScenicScore;
    char** trees;
    char buf[MAX_COUNT];

    FILE* fstream = fopen(INPUT_FILE, "r");

    if (fstream == NULL) {
        printf("Couldn't open the file %s\n", INPUT_FILE);
        return -1;
    }

    // get the number of rows and allocate memory
    numRows = getNumRows(fstream);
    trees = (char**)malloc(numRows * sizeof(char*));

    // get number of rows and allocate memory for first row
    fgets(buf, MAX_COUNT, fstream);
    numCols = (int)strlen(buf) - 1;
    trees[0] = (char*)malloc(numCols * sizeof(char));
    for (int i = 0; i < numCols; i++) {
        trees[0][i] = buf[i] - 0x30; // convert to value
    }

    // fill other rows
    for (int line = 1; line < numRows; line++) {
        trees[line] = (char*)malloc(numCols * sizeof(char));
        fgets(trees[line], MAX_COUNT, fstream);
        for (int i = 0; i < numCols; i++) {
            trees[line][i] -= 0x30; // convert to value
        }
    }

    // challenge 1
    visibleTrees = calculateVisibleTrees(trees, numRows, numCols);
    printf("There are %d visible trees.\n", visibleTrees);
    // challenge 2
    highestScenicScore = calculateHighestScenicScore(trees, numRows, numCols);
    printf("The highest scenic score is %d\n", highestScenicScore);

    return 0;
}

/*
 * returns the number of lines
 */
int getNumRows(FILE* fp) {
    // local variables
    char buffer[MAX_COUNT];
    long posFp;
    int lineCount = 0;

    // get filepointer location
    posFp = ftell(fp);
    // move the filepointer to the start
    rewind(fp);
    // check the number of lines
    while (fgets(buffer, MAX_COUNT, fp)) {
        lineCount++;
    }
    // restore filepointer to its original location
    fseek(fp, posFp, SEEK_SET);

    return lineCount;
}

int calculateVisibleTrees(char** trees, int rows, int cols) {
    int visibleTrees = 0;
    char* topHighest = malloc(cols * sizeof(char));
    char leftHighest = -1;

    // initialize topHighest
    for (int i = 0; i < cols; i++) {
        topHighest[i] = -1;
    }

    for (int r = 0; r < rows; r++) {
        // reset left highest tree
        leftHighest = -1;

        for (int c = 0; c < cols; c++) {
            // check top
            if (trees[r][c] > topHighest[c]) {
                visibleTrees++;
                topHighest[c] = trees[r][c];
                if (trees[r][c] > leftHighest) leftHighest = trees[r][c];
                continue;
            }
            // check left
            if (trees[r][c] > leftHighest) {
                visibleTrees++;
                leftHighest = trees[r][c];
                continue;
            }
            // check right
            for (int right = c + 1; right < cols; right++) {
                if (trees[r][c] <= trees[r][right]) break;
                if (right == cols - 1) {
                    visibleTrees++;
                    goto nextCol;
                }
            }
            if (c == cols - 1) {
                visibleTrees++;
                break;
            }
            // check bottom
            for (int bottom = r + 1; bottom < rows; bottom++) {
                if (trees[r][c] <= trees[bottom][c]) break;
                if (bottom == rows - 1) {
                    visibleTrees++;
                }
            }
            if (r == rows - 1) {
                visibleTrees++;
            }
            nextCol:;
        }
    }
    return visibleTrees;
}

int calculateHighestScenicScore(char** trees, int rows, int cols) {
    int max = 0;
    int top, left, right, bottom;

    for (int r = 1; r < rows-1; r++) {
        for (int c = 1; c < cols-1; c++) {
            int scenicScore = 1;
            // count top
            for (top = 1; top < r; top++) {
                if (trees[r-top][c] >= trees[r][c]) break;
            }
            if ((scenicScore *= top) == 0) break;
            // count left
            for (left = 1; left < c; left++) {
                if (trees[r][c-left] >= trees[r][c]) break;
            }
            if ((scenicScore *= left) == 0) break;
            // count right
            for (right = 1; cols-1-right > c; right++) {
                if (trees[r][c+right] >= trees[r][c]) break;
            }
            if ((scenicScore *= right) == 0) break;
            // count bottom
            for (bottom = 1; rows-1-bottom > r; bottom++) {
                if (trees[r+bottom][c] >= trees[r][c]) break;
            }
            if ((scenicScore *= bottom) == 0) break;
            if (scenicScore > max) max = scenicScore;
        }
    }
    return max;
}