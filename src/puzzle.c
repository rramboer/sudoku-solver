#include "../include/sudoku.h"

Sudoku* createSudoku(Square*** squares, Box** boxes) {
    Sudoku* sudoku;
    sudoku = (Sudoku *) malloc(sizeof(Sudoku));
    sudoku->boxes = boxes;
    sudoku->squares = squares;
    return sudoku;
}

Sudoku* setUpPuzzle(int ** puzzle) {
    int i;
    int j;
    int x;
    int currentBox = 0;
    Square*** sudoku;
    Box ** boxes;
    sudoku = (Square ***) malloc(9 * sizeof(Square **));
    boxes = createBoxes();

    for (i = 0; i < SIZE_ROWS; i++) {
        sudoku[i] = (Square **) malloc(9 * sizeof(Square *));
        for (j = 0; j < SIZE_COLUMNS; j++) {
            sudoku[i][j] = (Square *) malloc(9 * sizeof(Square));
            sudoku[i][j]->number = puzzle[i][j];
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            boxes[currentBox]->squares[boxes[currentBox]->numbers] = sudoku[i][j];
            sudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->numbers++;

            for (x = 0; x < 9; x++) {
                sudoku[i][j]->possible[x] = 0;
            }

            if (j == 2 || j == 5) {
                currentBox++;
            }

        }
        currentBox -= 2;
        if (i == 2) {
            currentBox = 3;
        }
        else if (i == 5) {
            currentBox = 6;
        }
    }

    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->number != 0) {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return createSudoku(sudoku, boxes);
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

int checkPuzzle(Square*** sudoku, Box** boxes) {
    int i;
    int j;

    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->solvable == 1) {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                return 1;
            }
        }
    }

    if (boxSingles(sudoku, boxes)) {
        return 1;
    }
    return checkRows(sudoku);
}


int ** createPuzzle(_Bool demo) {
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
    if (!demo) {
        printf("Enter the puzzle in a continuous string of digits with 0s for empty spaces.\n");
        char input[81];
        scanf("%s", input);
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                array[row][col] = input[row * 9 + col] - '0';
            }
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

void printPuzzle(Square*** puzzle) {
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
            printf("%d ", puzzle[i][j]->number);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}

