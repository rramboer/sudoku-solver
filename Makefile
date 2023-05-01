CC = gcc
CFLAGS = -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: sudoku run clean

demo: sudoku demo_run clean

test: sudoku run clean

sudoku:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./sudoku

demo_run:
	./sudoku -d

test_run:
	./sudoku -t

clean:
	rm sudoku