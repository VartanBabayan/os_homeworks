CC=g++

CFLAGS=-c -Wall

all: copy

copy: ProgramCopy.o
	  $(CC) ProgramCopy.o -o copy

ProgramCopy.0: ProgramCopy.cpp
	  $(CC) $(CFLAGS) ProgramCopy.cpp -o copy.o

clean:
	rm *.o copy