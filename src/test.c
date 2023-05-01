#include "../include/sudoku.h"

int ** createPuzzleTest(const int int_input) {
    int ** puzzle;
    int i;
    int j;
    int array[9][9];

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) { 
            array[row][col] = int_input; // TODO
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

void read_csv(const char* filename, int* column1, /*int* column2,*/ int* num_rows, int input) {
    int numTests = 1000000 ? input == 100 : (int)(((float)input / 100.0) * 1000000.0);
    FILE* fp = fopen(filename, "r");
    char line[82];
    char* token;
    // Check if the file was opened successfully
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    // Skip the first line (headers)
    fgets(line, 20, fp);
    // Read in the CSV file
    int i = 0;
    while (fgets(line, 82, fp) != NULL && i < numTests) {
        // Split the line into two columns using strtok()
        token = strtok(line, ",");
        column1[i] = atoi(token);
        //token = strtok(NULL, ",");
        //column2[i] = atoi(token);
        i++;
    }
    // Set the number of rows
    *num_rows = i;
    // Close the file
    fclose(fp);
}

int testSudoku() {
    int pass = 0;
    int fail = 0;
    int num_rows;
    int column1[1000000];
    // int column2[1000000];

    // Read in an integer
    printf("Run the following percent of the tests (formatted as an integer): ");
    int input;
    scanf("%d", &input);

    // Read in the CSV file
    read_csv("data/tests.csv", column1, /*column2,*/ &num_rows, input);

    // Run the tests TODO
    for (int i = 0; i < num_rows; i++) {
        Sudoku* sudoku = setUpPuzzle(createPuzzleTest(column1[i]));
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
