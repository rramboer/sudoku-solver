#include "../include/sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;
int UNSOLVED = 9 * 9;

int main(int argc, char** argv) {

    _Bool demo = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--demo") == 0 || strcmp(argv[i], "-d") == 0) {
            demo = true;
        }
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
