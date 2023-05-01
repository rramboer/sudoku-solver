#include "../include/sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;
int UNSOLVED = 9 * 9;

int main() {

    Sudoku* sudoku = setUpPuzzle(createPuzzle());

    printf("Original Puzzle:\n\n");

    printPuzzle(sudoku->squares);

    int progress;

    while (UNSOLVED > 0) {
        progress = checkPuzzle(sudoku->squares, sudoku->boxes);
        if (progress == 0) {
            printf("\nFailed to solve puzzle.\n\n");
            break;
        }
    }

    printf("\n\nSolved Puzzle:\n\n");

    printPuzzle(sudoku->squares);

    return 0;

}
