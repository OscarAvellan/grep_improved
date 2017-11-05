# Created by Oscar Avellan

## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS =	-Wall -Wextra


## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =		grep_improved.c grep_helper.c grep_ranking.c
OBJ =		grep_improved.o grep_helper.o grep_ranking.o
EXE = 	grep_improved

## Top level target is executable.
$(EXE):	$(OBJ)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJ)


## Clean: Remove object files and core dump files.
clean:
		/bin/rm $(OBJ)

## Clobber: Performs Clean and removes executable file.

clobber: clean
		/bin/rm $(EXE)

## Dependencies

grep_improved.o:		grep_helper.h
grep_helper.o:	grep_helper.h
grep_ranking.o:	grep_helper.h grep_ranking.h
