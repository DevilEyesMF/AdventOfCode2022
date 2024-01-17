// includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// defines
#define INPUT_FILE "input.txt"
#define MAX_COUNT 32

// main
int main() {
    char buffer[MAX_COUNT];
    int maxCalories[3] = {0};

    FILE* fstream = fopen(INPUT_FILE, "r");

    if (fstream == NULL) {
        printf("Couldn't open the file %s\n", INPUT_FILE);
        return -1;
    }

    while (fgets(buffer, MAX_COUNT, fstream)) {
        // local variables
        static int calories = 0;

        if (!strcmp(buffer, "\n")) {
            if (calories > maxCalories[2]) {
                maxCalories[2] = calories;
                // order the array
                for (int i = 2; i > 0; i--) {
                    if (maxCalories[i] > maxCalories[i-1]) {
                        // swap the variables
                        int temp = maxCalories[i-1];
                        maxCalories[i-1] = maxCalories[i];
                        maxCalories[i] = temp;
                    }
                }
            }
            // reset counter
            calories = 0;
        }

        if (strlen(buffer) > 1)
            calories += atoi(buffer);
    }

    printf("The Elf carrying the most calories is carrying no less than %d calories!\n", maxCalories[0]);
    printf("The three strongest Elves are carrying a whopping %d calories!\nThat's a lot of Big Macs\n",
           maxCalories[0] + maxCalories[1] + maxCalories[2]);

    return 0;
}