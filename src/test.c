#include "../include/sudoku.h"

int ** createPuzzleTest(const char* input) {
    int ** puzzle;
    int i;
    int j;
    int array[9][9];

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) { 
            array[row][col] = input[9 * row + col] - '0';
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
    int numTests = 1000000;
    if (input < 100) {
        numTests = (int) ((float) input / 100.0 * (float) numTests);
    }
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

    printf("Run the following percentage of the test suite (formatted as an integer): ");
    int input;
    scanf("%d", &input);

    read("data/tests.txt", games, /*column2,*/ &num_rows, input);

    for (int i = 0; i < num_rows; i++) {
        int** puzzle = createPuzzleTest(games[i]);
        Sudoku* sudoku = setUpPuzzle(puzzle);
        UNSOLVED = 81;
        while (UNSOLVED > 0) {
            if (!checkPuzzle(sudoku->squares, sudoku->boxes)) {
                fail++;
                printf("Test %d: FAILED\n", i);
                break;
            }
        }
        if (UNSOLVED == 0) {
            pass++;
            printf("Test %d: PASSED\n", i);
        }
        free(puzzle);
        free(sudoku);
    }

    // Print the results
    printf("Tests passed: %d\n", pass);
    printf("Tests failed: %d\n", fail);
    printf("Pass Percentage: %.2f%%\n", (float) ((float)pass / (float)(pass + fail)) * 100.0);

    return 1;
}
