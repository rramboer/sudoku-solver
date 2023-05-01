#include "../include/sudoku.h"
#include <stdio.h>

int ** createPuzzleTest(const char* input) {
    int ** puzzle;
    int i;
    int j;
    int array[9][9];

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) { 
            array[row][col] = atoi(input); // TODO
        }
    }
    
    puzzle = (int **) malloc(9 * sizeof(int *));
    for (i = 0; i < 9; i++) {
        puzzle[i] = (int *) malloc(9 * sizeof(int));
        for (j = 0; j < 9; j++) {
            puzzle[i][j] = array[i][j];
        }
    }
    return puzzle;
}

void read(const char* filename, char* column1[], /*int* column2,*/ int* num_rows, int input) {
    int numTests = 1000000 ? input == 100 : (int)(((float)input / 100.0) * 1000000.0);
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    int i = 0;
    char line[82];
    while (fgets(line, 82, fp) && i < numTests) {
        column1[i] = line;
        i++;
    }
    *num_rows = i;
    fclose(fp);
}

int testSudoku() {
    int pass = 0;
    int fail = 0;
    int num_rows;
    char* games[1000000];
    // int column2[1000000];

    // Read in an integer
    printf("Run the following percentage of the test suite (formatted as an integer): ");
    int input;
    scanf("%d", &input);

    // Read in the CSV file
    read("data/tests.txt", games, /*column2,*/ &num_rows, input);

    // Run the tests TODO
    for (int i = 0; i < num_rows; i++) {
        Sudoku* sudoku = setUpPuzzle(createPuzzleTest(games[i]));
        while (UNSOLVED > 0) {
            if (!checkPuzzle(sudoku->squares, sudoku->boxes)) {
                break;
            }
        }
    }

    // Print the results
    printf("Tests passed: %d\n", pass);
    printf("Tests failed: %d\n", fail);
    printf("Pass Percentage: %.2f%%\n", (float) ((float)pass / (float)(pass + fail)) * 100.0);

    return 1;
}
