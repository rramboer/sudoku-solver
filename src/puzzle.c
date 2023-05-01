#include "../include/sudoku.h"

Square*** setUpPuzzle(int ** puzzle) {
    int i;
    int j;
    int x;
    Square*** sudoku;

    sudoku = (Square ***) malloc(9 * sizeof(Square **));
    for (i = 0; i < SIZE_ROWS; i++) {
        sudoku[i] = (Square **) malloc(9 * sizeof(Square *));
        for (j = 0; j < SIZE_COLUMNS; j++) {
            sudoku[i][j] = (Square *) malloc(9 * sizeof(Square));
            sudoku[i][j]->number = puzzle[i][j];
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            for (x = 0; x < 9; x++) {
                sudoku[i][j]->possible[x] = 0;
            }
        }
    }

    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->number != 0) {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return sudoku;
}

int updateSudoku(Square*** sudoku, int row, int column) {
    int x;
    int number = sudoku[row][column]->number;

    for (x = 0; x < SIZE_ROWS; x++) {
        if (sudoku[x][column]->possible[number - 1] == 0) {
            sudoku[x][column]->solvable--;
            sudoku[x][column]->possible[number - 1] = 1;
        }
    }

    for (x = 0; x < SIZE_COLUMNS; x++) {
        if (sudoku[row][x]->possible[number - 1] == 0) {
            sudoku[row][x]->solvable--;
            sudoku[row][x]->possible[number - 1] = 1;
        }
    }

    return 1;
}

int checkPuzzle(Square*** sudoku) {
    int i;
    int j;

    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->solvable == 1) {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
            }
        }
    }
    return 1;
}


int ** createPuzzle() {
    int ** puzzle;
    int i;
    int j;
    int array[9][9] = {
        { 0, 1, 9,  0, 0, 2,  0, 0, 0 },
        { 4, 7, 0,  6, 9, 0,  0, 0, 1 },
        { 0, 0, 0,  4, 0, 0,  0, 9, 0 },

        { 8, 9, 4,  5, 0, 7,  0, 0, 0 },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0 },
        { 0, 0, 0,  2, 0, 1,  9, 5, 8 },

        { 0, 5, 0,  0, 0, 6,  0, 0, 0 },
        { 6, 0, 0,  0, 2, 8,  0, 7, 9 },
        { 0, 0, 0,  1, 0, 0,  8, 6, 0 }
    };
    puzzle = (int **) malloc(9 * sizeof(int *));
    for (i = 0; i < 9; i++) {
        puzzle[i] = (int *) malloc(9 * sizeof(int));
        for (j = 0; j < 9; j++) {
            puzzle[i][j] = array[i][j];
        }
    }
    return puzzle;
}

void printPuzzle(int ** puzzle) {
    int i;
    int j;
    for (i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
        for (j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                printf("| ");
            }
            printf("%d ", puzzle[i][j]);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}

