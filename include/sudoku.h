#include <stdio.h>
#include <stdlib.h>

char POSSIBLE = (char)0x1FF;

typedef struct Box {
  struct Box *next;
} Box;

typedef struct Square {
  int number;
  /* Bool: 000000000
     Num:  987654321 */
  char code;
  Box *box;
  int row;
  int column;
} Square;

int **createPuzzle();

void printPuzzle(int **puzzle);

Square ***setUpPuzzle(int **puzzle);
