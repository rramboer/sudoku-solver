#include "../include/sudoku.h"

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
