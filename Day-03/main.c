// includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// defines
#define INPUT_FILE "input.txt"
#define MAX_COUNT 128
#define ITEM_TYPES 52

// function prototypes
char getItemType(char);

int main() {
    char rucksack[MAX_COUNT];
    int result = 0;

    FILE* fstream = fopen(INPUT_FILE, "r");

    if (fstream == NULL) {
        printf("Couldn't open the file %s\n", INPUT_FILE);
        return -1;
    }

    while (fgets(rucksack, MAX_COUNT, fstream)) {
        int size, compartmentSize;
        int map[ITEM_TYPES] = {0};

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
    printf("The sum of the duplicate items is %d\n", result);

    fclose(fstream);

    return 0;
}

char getItemType(char item) {
    if (item >= 'a')
        item -= 'a';
    else if (item >= 'A')
        item -= 'A' - 26; // A would be 26, B would be 27, etc.

    return item;
}