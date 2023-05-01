#include "../include/sudoku.h"
#include <stdio.h>

int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;
int UNSOLVED = 9 * 9;

int main(int argc, char** argv) {

    _Bool demo = false;
    _Bool test = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--demo") == 0) {
            demo = true;
        }
        else if (strcmp(argv[i], "--test") == 0) {
            test = true;
        }
    }

    if (test) {
        testSudoku();
        return 0;
    }

    Sudoku* sudoku = setUpPuzzle(createPuzzle(demo));

    printf("Original Puzzle:\n\n");

    printPuzzle(sudoku->squares);

    _Bool solvable = true;

    while (UNSOLVED > 0) {
        if (!checkPuzzle(sudoku->squares, sudoku->boxes)) {
            printf("\nFailed to solve puzzle.\n\n");
            solvable = false;
            break;
        }
    }

    if (solvable) {
        printf("\n\nSolved puzzle:\n\n");
        printPuzzle(sudoku->squares);
    }

    return 0;

}
