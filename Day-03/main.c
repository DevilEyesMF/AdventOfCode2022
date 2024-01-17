// includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// defines
#define INPUT_FILE "input.txt"
#define MAX_COUNT 128
#define ITEM_TYPES 52
#define LINE_COUNT 3

// function prototypes
int partOne(FILE*);
int partTwo(FILE*);
char getItemType(char);

int main() {
    FILE* fstream = fopen(INPUT_FILE, "r");

    if (fstream == NULL) {
        printf("Couldn't open the file %s\n", INPUT_FILE);
        return -1;
    }

    printf("The sum of the duplicate items is %d\n", partOne(fstream));
    rewind(fstream);
    printf("The sum of duplicate items in each Elf group is %d\n", partTwo(fstream));

    fclose(fstream);

    return 0;
}

int partOne(FILE* fstream) {
    // local variables
    char rucksack[MAX_COUNT];
    int result = 0;

    while (fgets(rucksack, MAX_COUNT, fstream)) {
        int size, compartmentSize;
        int map[ITEM_TYPES];

        // reset the map for each rucksack
        memset(map, 0, ITEM_TYPES * sizeof(int));
        // get the size of the rucksack
        size = ((int)strlen(rucksack) - 1);
        compartmentSize = size / 2;

        // create map of the first compartment
        for (int i = 0; i < compartmentSize; i++)
            map[getItemType(rucksack[i])]++;

        // check second compartment for duplicates
        for (int i = compartmentSize; i < size; i++) {
            if (map[getItemType(rucksack[i])]) {
                result += getItemType(rucksack[i]) + 1;
                break;
            }
        }
    }
    return result;
}

int partTwo(FILE* fstream) {
    // local variables
    char rucksack[MAX_COUNT];
    int map[ITEM_TYPES] = {0};
    int result = 0;

    for (int lineCount = 0; fgets(rucksack, MAX_COUNT, fstream); lineCount++) {
        int size = (int)strlen(rucksack) - 1;

        switch(lineCount) {
            // first rucksack
            case 0:
                for (int i = 0; i < size; i++) {
                    map[getItemType(rucksack[i])] = 1;
                }
                break;
            // last rucksack
            case LINE_COUNT - 1:
                for (int i = 0; i < size; i++) {
                    if (map[getItemType(rucksack[i])] == lineCount) {
                        result += getItemType(rucksack[i]) + 1;
                        break;
                    }
                }
                // reset map
                memset(map, 0, ITEM_TYPES * sizeof(int));
                // reset counter
                lineCount = -1;
                break;
            // any other rucksack
            default:
                for (int i = 0; i < size; i++) {
                    if (map[getItemType(rucksack[i])] == lineCount) {
                        map[getItemType(rucksack[i])]++;
                    }
                }
                break;
        }
    }
    return result;
}

char getItemType(char item) {
    if (item >= 'a')
        item -= 'a';
    else if (item >= 'A')
        item -= 'A' - 26; // A would be 26, B would be 27, etc.

    return item;
}