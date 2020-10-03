CC=g++

CFLAGS=-c -Wall

all: complex

complex: complexProgram.o Complex.o
	 $(CC) complexProgram.o Complex.o -o complex

complexProgram.o: complexProgram.cpp Complex.h
		  $(CC) $(CFLAGS) complexProgram.cpp

Complex.o: Complex.cpp Complex.h
	   $(CC) $(CFLAGS) Complex.cpp

complex.o: complex.cpp
	   $(CC) $(CFLAGS) complex.cpp

clean:
	rm -rf *o complex
