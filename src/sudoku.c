#include "../include/sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;
int UNSOLVED = 9 * 9;

int main() {

    Sudoku* sudoku = setUpPuzzle(createPuzzle());

    printf("Original Puzzle:\n\n");

    printPuzzle(sudoku->squares);

    while (UNSOLVED > 0) {
        if (!checkPuzzle(sudoku->squares, sudoku->boxes)) {
            printf("\nFailed to solve puzzle.\n\n");
            break;
        }
    }

    printf("\n\nSolved Puzzle:\n\n");

    printPuzzle(sudoku->squares);

    return 0;

}
