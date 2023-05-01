#include "../include/sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;
int UNSOLVED = 9 * 9;

int main() {

    int ** puzzle;

    Square*** sudoku;

    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);

    printPuzzle(sudoku);

    checkPuzzle(sudoku);

    printPuzzle(sudoku);

    return 0;

}
