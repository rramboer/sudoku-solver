#include "../include/sudoku.h"

int boxSingles(Square*** sudoku, Box** boxes) {
    int i;
    int j;
    int x;
    int count;
    int temp;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            count = 0;
            for (x = 0; x < 9; x++) {
                if (boxes[i]->squares[x]->number != 0) {
                    continue;
                }
                if (boxes[i]->squares[x]->possible[j] == 0) {
                    temp = x;
                    count++;
                }
                if (count == 2) {
                    break;
                }
            }
            if (count == 1) {
                boxes[i]->squares[temp]->number = j + 1;
                UNSOLVED--;
                boxes[i]->squares[temp]->solvable = 0;
                updateSudoku(sudoku, boxes[i]->squares[temp]->row, boxes[i]->squares[temp]->column);
                return 1;
            }
        }
    }
    return 0;
}

Box** createBoxes() {
    int x;
    int y;
    Box** boxes;

    boxes = (Box **) malloc(9 * sizeof(Box *));

    for (x = 0; x < 9; x++) {
        boxes[x] = (Box *) malloc(9 * sizeof(Box));
        boxes[x]->squares = malloc(9 * sizeof(Square *));
        boxes[x]->solvable = 9;
        boxes[x]->numbers = 0;
        for (y = 0; y < 9; y++) {
            boxes[x]->possible[y] = 0;
        }
    }

    return boxes;
}

int updateBoxes(Square ***sudoku, int row, int column) {
    int x;
    int number = sudoku[row][column]->number;
    Box* box = sudoku[row][column]->box;
    for (x = 0; x < 9; x++) {
        if (box->squares[x]->possible[number - 1] == 0) {
            box->squares[x]->solvable--;
            box->squares[x]->possible[number - 1] = 1;
        }
    }
    return 1;
}
